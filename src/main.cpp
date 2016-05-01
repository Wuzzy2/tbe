/* The Butterfly Effect
 * This file copyright (C) 2009,2011,2016  Klaas van Gend
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation
 * applicable version is GPL version 2 only.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA.
 */

#include "tbe_global.h"
#include "tbe_paths.h"
#include "MainWindow.h"
#include "Translator.h"
#include <QSettings>
#include <QApplication>
#include <QSplashScreen>

// the verbosity for all logging - by default defined at 4
// accepted values are 0 (no logging) - 6 (most logging)
// note that levels 5 and 6 affect playing
#ifdef QT_DEBUG
int theVerbosity = 4;
#else
int theVerbosity = 2;
#endif

// This variable defines whether we are playing or the level creator is on
// switching to LevelCreator is possible through the "File" menu
// or from the command line.
std::atomic<bool> theIsLevelCreator(false);

// this variable defines whether in the level editor we are expecting collision
// detection to work or not - you want this on to align certain things
std::atomic<bool> theIsCollisionOn(false);

// this variable defines whether we are showing Box2D debugging info or not
// switching this option is possible through the theDrawDebugActionPtr in MainWindow
// NOTE: enabling this variable will also add position information to tooltips
std::atomic<bool> theDrawDebug(false);

// this variable defines whether DrawPolyOutline draws the polygons
// over the image
// switching this option is possible through the theDrawOutlineActionPtr in MainWindow
std::atomic<bool> theDrawPolyOutline(false);

// True if application is supposed to only load a level, apply hints (or not) and
// run it automatically - returning a value depending on success.
// Used for automated regression tests.
std::atomic<bool> theIsTesting(false);

// This variable defines whether TBE displays a frame refresh counter or not
// TODO/FIXME: this should go into preferences or so at some point
// (enabled in debug builds/disabled in release builds)
#ifdef QT_DEBUG
std::atomic<bool> theDisplayFramerate(true);
#else
std::atomic<bool> theDisplayFramerate(false);
#endif

QString theStartFileName;


// -----------------------------------------------------------------------
// ------------------------- Command Line Parsing ------------------------
// -----------------------------------------------------------------------


static bool displayHelp(QString /*anArgument*/ )
{
	printf("The Butterfly Effect" " " APPRELEASE "" APPFLAVOUR "\n\nhelp text\n\n");
	printf(" --draw-debug        debug draw (draw outlines on physical boundaries of all objects)");
	printf(" --help              gives this help text\n");
	printf(" -h                  gives this help text\n");
	printf(" --level-creator     start in level creator mode\n");
	printf(" -L                  start in level creator mode\n");
	printf(" --verbosity <lvl>   set verbosity, 1=little (default), %d=all\n", MAX_VERBOSITY);
	printf(" -v <lvl>            set verbosity\n");
    printf("--regression <lvl:time,[lvl:time]>  levels to run in automated regression\n");
    printf("                     (comma-separated list, time is level runtime in seconds)\n");
	printf(" --windowed          display in a window (default is fullscreen)\n");
	printf(" -W                  display in a window (default is fullscreen)\n");
	printf("\n");
	exit(1);
}

static bool goLevelCreator( QString /*anArgument*/ )
{
    theIsLevelCreator = true;
	return true;
}

static bool setDrawDebug(QString /*anArgument*/ )
{
	theDrawDebug = true;
	return true;
}

static bool setVerbosity(QString anArgument)
{
	// the argument should be a number. Let's parse.
	int myNumber = anArgument.toInt();
	if (myNumber < 1 || myNumber > MAX_VERBOSITY)
	{
		printf("ERROR: verbosity argument should be between 1 and %d\n", MAX_VERBOSITY);
		return false;
	}
	theVerbosity = myNumber;
	DEBUG2("set verbosity level to %d", theVerbosity);
	return true;
}

// local variable
static bool theIsMaximized = true;
static bool setWindowed( QString /*anArgument*/ )
{
	theIsMaximized = false;
	return true;
}

std::atomic<bool> theIsRunAsRegression(false);
static bool runRegression( QString aListOfLevels )
{
	theStartFileName += aListOfLevels;
	theIsRunAsRegression = true;
	return true;
}

// this struct is used to list all long and short arguments
// it also contains a function pointer to a static function below
// that actually acts on the argument
struct s_args
{
	QString theFullCommand;
	QString theShortCommand;
	bool needsArgument;
	bool (*theFunctionPtr)(QString anArgument);
};


static struct s_args theArgsTable[] =
{
// keep sorted alphabetically, please
	{ "draw-debug",    "",  false, setDrawDebug, },
	{ "help",          "h", false, displayHelp, },
	{ "level-creator", "L", false, goLevelCreator, },
	{ "regression",    "",  true,  runRegression, },
    { "verbosity",     "v", true,  setVerbosity, },
	{ "windowed",      "W", false, setWindowed, },
//	keep this one last:
	{ "\0", "\0", false, nullptr, },
};



#ifdef QT_DEBUG
 extern void setupBacktrace(void);
#endif


int main(int argc, char *argv[])
{
	//** init Qt (graphics toolkit) - www.qtsoftware.com
	QApplication app(argc, argv);
    char* myHashSeedString = strdup("QT_HASH_SEED=1");
    putenv (myHashSeedString);

	//** set the names to our website
	QCoreApplication::setOrganizationName("the-butterfly-effect.org");
	QCoreApplication::setOrganizationDomain("the-butterfly-effect.org");
	QCoreApplication::setApplicationName(APPNAME);

	//** parse the command line arguments
	QStringList myCmdLineList = app.arguments();
	bool isParsingSuccess=true;
	// we can skip argument zero - that's the tbe executable itself
	for (int i=1; i<myCmdLineList.size() && isParsingSuccess; i++)
	{
		QString myArg = myCmdLineList[i];
		if (myArg.startsWith("-"))
		{
			// remove one or two dashes - we're slightly more flexible than usual
			myArg.remove(0,1);
			if (myArg.startsWith("-"))
				myArg.remove(0,1);

			// extract value with = if there is one
			QStringList myExp = myArg.split("=");

			// is it matching with short or long?
			int j=0;
			bool isMatch=false;
			while(theArgsTable[j].theFunctionPtr != nullptr)
			{
				if (myExp[0] == theArgsTable[j].theFullCommand
					|| myExp[0] == theArgsTable[j].theShortCommand)
				{
					isMatch=true;
					QString myVal;
					if (theArgsTable[j].needsArgument == true)
					{
						// was it '='?
						if (myExp.count()==2)
							myVal = myExp[1];
						else
						{
							// or is it ' ' -> which means we need to grab next arg
							if (i+1<myCmdLineList.size())
							{
								myVal = myCmdLineList[i+1];
								i++;
							}
							else
							{
								isParsingSuccess=false;
								break;
							}
						}
					}
					if (theArgsTable[j].theFunctionPtr(myVal)==false)
						isParsingSuccess=false;
				}
				++j;
			}
			if (isMatch==false)
			{
				isParsingSuccess=false;
				break;
			}
		}
		else
		{
			// if it is a single string, it probably is a file name
			theStartFileName = myArg;
		}

	}

	if (isParsingSuccess==false)
		displayHelp("");

#ifdef QT_DEBUG
	setupBacktrace();
#endif

	//** read the locale from the environment and set the output language
	if (theIsRunAsRegression)
	{
		DEBUG1("Regression: not loading any translators!");
	}
	else
        TheTranslator.init();

    //** init splash screen, do it as early in program start as possible
    QSplashScreen mySplash(QPixmap(":/title_page.png"));
    mySplash.showMessage(MainWindow::getWelcomeMessage());
    mySplash.show();
    app.processEvents();

	DEBUG3("SUMMARY:");
	DEBUG3("  Verbosity is: %d / Fullscreen is %d", theVerbosity, theIsMaximized);
    if (theIsRunAsRegression)
    {
		DEBUG3("  Regression levels: '%s'", ASCII(theStartFileName));
    }
    else
    {
		DEBUG3("  Start file name is: '%s'", ASCII(theStartFileName));
    }

	QSettings mySettings;
	DEBUG3("  using settings from: '%s'", ASCII(mySettings.fileName()));

	//** setup main window, shut down splash screen
	MainWindow myMain(theIsMaximized);
	myMain.show();
	mySplash.finish(&myMain);

	//** run the main display loop until oblivion
	return app.exec();
}


const char* ASCII(const QString& aQString)
{
    static char myString[256];
    strncpy(myString, aQString.toLatin1().constData(), 255);
    return myString;
}
