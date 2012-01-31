/* The Butterfly Effect
 * This file copyright (C) 2009,2012  Klaas van Gend
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "RectObject.h"
#include "tbe_global.h"
#include "Box2D.h"
#include "ViewObject.h"
#include "Property.h"
#include "ObjectFactory.h"

static const char* DEFAULT_RECTOBJECT_NAME = "RectObject";

const qreal RectObject::ASPECT_RATIO = 10.0;


//// this class' ObjectFactory
class RectObjectFactory : public ObjectFactory
{
public:
	RectObjectFactory(void)
	{	announceObjectType(DEFAULT_RECTOBJECT_NAME, this); }
	virtual AbstractObject* createObject(void) const
	{	return fixObject(new RectObject()); }
};
static RectObjectFactory theRectObjectFactory;


/** the AbstractRectObjectFactory
 *  note that it is slightly more complex than usual, because it is generalised
 *  to create any type of rectobject. Below the declaration, there will be several
 *  global instances each identifying one rectobject type
 */
class AbstractRectObjectFactory : public ObjectFactory
{
public:
	AbstractRectObjectFactory(
		const QString& anInternalName,
		const QString& aDisplayName,
		const QString& aTooltip,
		const QString& anImageName,
		qreal aWidth,
		qreal aHeight,
		qreal aMass,
		qreal aBounciness)
			: theDisplayName(aDisplayName),	theTooltip(aTooltip),
			  theImageName(anImageName), theWidth(aWidth), theHeight(aHeight),
			  theMass(aMass), theBounciness(aBounciness)
	{	announceObjectType(anInternalName, this); }

	virtual AbstractObject* createObject(void) const
	{	return fixObject(new RectObject(theDisplayName, theTooltip,
										theImageName, theWidth, theHeight,
										theMass, theBounciness)); }
private:
		QString theDisplayName;
		QString theTooltip;
		QString theImageName;
		qreal theWidth;
		qreal theHeight;
		qreal theMass;
		qreal theBounciness;
};


// ---------------------------------predefined rectangular objects:
// order of the arguments below:
//              anInternalName, (do not translate)
//              aDisplayName,
//              aTooltip,
// anImageName,   aWidth,aHeight,  aMass,  aBounciness

static AbstractRectObjectFactory theDomRedFactory("DominoRed",
	QObject::tr("Domino (Red)"),
	QObject::tr("The famous plastic red domino stone"),
	"DominoRed", 0.1, 0.5, 2.5, 0.1 );

static AbstractRectObjectFactory theDomBlueFactory("DominoBlue",
	QObject::tr("Domino (Blue)"),
	QObject::tr("The famous plastic blue domino stone"),
	"DominoBlue", 0.1, 0.5, 2.5, 0.1 );

static AbstractRectObjectFactory theDomGreenFactory("DominoGreen",
	QObject::tr("Domino (Green)"),
	QObject::tr("The famous plastic green domino stone"),
	"DominoGreen", 0.1, 0.5, 2.5, 0.1 );

static AbstractRectObjectFactory theFloorFactory("Floor",
	QObject::tr("Floor"),
	"",
	"used_wood_bar", 1.0, 0.1, 0.0, 0.1 );

static AbstractRectObjectFactory theWallFactory("Wall",
	QObject::tr("Wall"),
	"",
	"oldbrick", 0.2, 1.0, 0.0, 0.05 );


// Constructors/Destructors
//

RectObject::RectObject ( ) : AbstractObject(), theNameString(DEFAULT_RECTOBJECT_NAME)
{
	DEBUG5("RectObject::RectObject\n");

	// because this object is very flexible and many parameters can be set through
	// the Properties, do not assume too much here...

	// also: keep in mind that child objects may set some things automatically
	initRectAttributes();
}

RectObject::RectObject( const QString& aDisplayName,
				const QString& aTooltip,
				const QString& aImageName,
				qreal aWidth, qreal aHeight, qreal aMass, qreal aBounciness )
	: theNameString(aDisplayName), theToolTipString(aTooltip)
{
	theProps.setProperty(Property::IMAGE_NAME_STRING, aImageName);
	setTheWidth(aWidth);
	setTheHeight(aHeight);

	if (aMass > 0.001)
		theProps.setDefaultPropertiesString(
			QString("%1:%2/").arg(Property::MASS_STRING).arg(QString::number(aMass)));
	else
		theProps.removeProperty(Property::MASS_STRING);
	setTheBounciness(aBounciness);
	initRectAttributes();
}

RectObject::~RectObject ( )
{
}

//
// Methods
//


// Accessor methods
//


// Other methods
//

b2BodyType RectObject::getObjectType(void) const
{
	float myMass;
	if (theProps.property2Float(Property::MASS_STRING, &myMass))
		return b2_dynamicBody;
	return b2_staticBody;
}

void RectObject::initRectAttributes ( )
{
	theProps.setDefaultPropertiesString(
		Property::FRICTION_STRING    + QString(":/") +
		Property::RESIZABLE_STRING   + QString(":") + Property::NONE_STRING + "/" +
		Property::DESCRIPTION_STRING + QString(":/") );
	resizableInfo = NORESIZING;
}


void  RectObject::parseProperties(void)
{
	// first parse everything that AbstractObject already knows about
	AbstractObject::parseProperties();

	theProps.property2String(Property::OBJECT_NAME_STRING,&theNameString);

	QString myString;
	if (theProps.property2String(Property::RESIZABLE_STRING, &myString))
	{
		// we do not check for none, that's the default
		resizableInfo = NORESIZING;
		if (myString == Property::HORIZONTAL_STRING)
			resizableInfo = HORIZONTALRESIZE;
		if (myString == Property::VERTICAL_STRING)
			resizableInfo = VERTICALRESIZE;
		if (myString == Property::TOTALRESIZE_STRING)
			resizableInfo = TOTALRESIZE;
	}
	theProps.property2String(Property::DESCRIPTION_STRING, &theToolTipString);

	clearShapeList();
	b2PolygonShape* myBoxShape = new b2PolygonShape();
	myBoxShape->SetAsBox(getTheWidth()/2.0, getTheHeight()/2.0);

	// get mass:  if no mass set, we'll make this a b2_staticBody
	b2FixtureDef* myBoxDef = new b2FixtureDef();
	float myMass;
	if (theProps.property2Float(Property::MASS_STRING, &myMass))
		myBoxDef->density = myMass / (getTheWidth()*getTheHeight());
	myBoxDef->shape   = myBoxShape;
	myBoxDef->userData = this;
	setFriction(myBoxDef);
	theShapeList.push_back(myBoxDef);
}

void  RectObject::setFriction(b2FixtureDef* aFixtureDef)
{
	// only set friction if it is special
	if (theProps.getPropertyNoDefault(Property::FRICTION_STRING).isEmpty())
		return;

	float myFriction = 0;
	if (theProps.property2Float(Property::FRICTION_STRING, &myFriction))
		aFixtureDef->friction = myFriction;
	else
		assert(false);
}
