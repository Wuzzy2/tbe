/* The Butterfly Effect
 * This file copyright (C) 2011  Klaas van Gend
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

#include "BackgroundSerializer.h"
#include <QDomElement>
#include <QStringList>

#include "tbe_global.h"
#include <cstdio>

// this one is declared in Level.cpp
extern const char *theBackgroundString;

static const char *theGradientString   = "gradientstop";
static const char *theImageString      = "image";
static const char *theImgHRepeatString = "hrepeatdist";
static const char *theImgVRepeatString = "vrepeatdist";
static const char *theNameString       = "name";
static const char *thePositionString   = "pos";


QString
BackgroundSerializer::createObjectFromDom(const QDomNode &q, Background *aBGPtr)
{
    QString myValue;

    /// simple sanity checks first...
    if (q.nodeName().isEmpty())
        return "";   // no background section - that's allowed
    if (q.nodeName() != theBackgroundString)
        return QString("expected <%1> but got <%2>.").arg(theBackgroundString).arg(q.nodeName());

    if (q.hasChildNodes() == true) {
        // to parse:   <image name="texture" hrepeatdist="0.0" vrepeatdist="1.5"/>
        // to parse:   <gradientstop pos="0.0"> 1.0;1.0;1.0;1.0 </gradientstop>
        QDomElement i;
        for (i = q.firstChildElement(); !i.isNull(); i = i.nextSiblingElement()) {
            if (i.nodeName() == theImageString) {
                aBGPtr->theImageName =
                    i.attributes().namedItem(theNameString).nodeValue();
                aBGPtr->theImageHRepeat =
                    i.attributes().namedItem(theImgHRepeatString).nodeValue().toFloat();
                aBGPtr->theImageVRepeat =
                    i.attributes().namedItem(theImgVRepeatString).nodeValue().toFloat();
            }

            if (i.nodeName() == theGradientString) {
                QStringList myColors = i.text().split(";");
                if (myColors.size() != 4)
                    return QString("gradientstop does not have expected format.");
                bool isOKPos, isOK0, isOK1, isOK2, isOK3;
                Background::GradientStop myStop(
                    i.attributes().namedItem(thePositionString).nodeValue().toFloat(&isOKPos),
                    myColors[0].toFloat(&isOK0),
                    myColors[1].toFloat(&isOK1),
                    myColors[2].toFloat(&isOK2),
                    myColors[3].toFloat(&isOK3));
                if (isOKPos == false)
                    return "Parsing position value in gradientstop failed\n";
                if (isOK0 == false || isOK1 == false || isOK2 == false || isOK3 == false)
                    return "Parsing color values in gradientstop failed\n";
                aBGPtr->theBackgroundGradient.push_back(myStop);
            }
        }
    }

    DEBUG4("createObjectFromDom for background successful");
    return "";
}


void
BackgroundSerializer::serialize(QDomElement *aParent, Background *aBackgroundPtr)
{
    QDomElement myBackground = aParent->ownerDocument().createElement(theBackgroundString);

    if (aBackgroundPtr->theImageName.isEmpty() == false) {
        QDomElement myImageName = aParent->ownerDocument().createElement(theImageString);
        myImageName.setAttribute(theNameString, aBackgroundPtr->theImageName);
        myImageName.setAttribute(theImgHRepeatString, QString::number(aBackgroundPtr->theImageHRepeat));
        myImageName.setAttribute(theImgVRepeatString, QString::number(aBackgroundPtr->theImageVRepeat));
        myBackground.appendChild(myImageName);
    }

    // save the gradients
    if (aBackgroundPtr->theBackgroundGradient.count() > 0) {
        foreach (Background::GradientStop myGS, aBackgroundPtr->theBackgroundGradient) {
            QString myGradientValue = QString("%1;%2;%3;%4")
                                      .arg(QString::number(myGS.theR))
                                      .arg(QString::number(myGS.theG))
                                      .arg(QString::number(myGS.theB))
                                      .arg(QString::number(myGS.theAlpha));

            QDomElement myGradient = aParent->ownerDocument().createElement(theGradientString);
            myGradient.setAttribute(thePositionString, QString::number(myGS.thePosition));
            QDomText myT = aParent->ownerDocument().createTextNode(myGradientValue);
            myGradient.appendChild(myT);
            myBackground.appendChild(myGradient);
        }
    }
    aParent->appendChild(myBackground);
}
