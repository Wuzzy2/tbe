/* The Butterfly Effect
 * This file copyright (C) 2011,2012  Klaas van Gend
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

#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

namespace Ui {
class GameResources;
}

#include "animateddialog.h"
class Level;
class QAction;
class ViewWorld;

/// This class holds the toolbox, the game info and (in the future)
/// the button for hints. It is displayed when you click on the appropriate
/// action in the menu bar and/or at the start of a level.
///
/// Usually this class is owned by the ResizingsGraphicsView,
/// which this class is drawn on top of (like an overlay).
class GameResources : public AnimatedDialog
{
    Q_OBJECT

public:
    explicit GameResources(ResizingGraphicsView *aRSGVPtr);
    ~GameResources();

    /// Set the Level where we're going to get our info from:
    /// i.e. level name, author but also the contents of the Toolbox view.
    void setLevelPtr(Level *aLevelPtr);

    /// Hooks up the two actions of the Game Resources dialog into
    /// the menu bar.
    void setup(QMenu *aMenuPtr);

protected:
    /// ill-named standard Qt member to change the i18n of the dialog
    virtual void changeEvent(QEvent *e) override;

signals:
    /// Emitted when the player wants to restart the level.
    void signalReloadLevel(void);

private slots:
    void on_theOKButton_clicked();
    void on_theResetButton_clicked();

private:
    Ui::GameResources *ui;

    /// pointer to Level instance, which contains level names and such
    Level *theLevelPtr;

    /// GraphicsView holding the ViewWorld, we are an overlay to that View
    ResizingGraphicsView *theParentPtr;

public:
};

#endif // GAMERESOURCES_H
