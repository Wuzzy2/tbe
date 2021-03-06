/* The Butterfly Effect
 * This file copyright (C) 2009  Klaas van Gend
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

#ifndef POSTIT_H
#define POSTIT_H

#include "AbstractObject.h"


/** the PostIt class is where the level hints are.
 *  the player can click on them to get the hints.
 *
 *  PostIts do not have a body or shape in simulation
 */
class PostIt : public AbstractObject
{
public:
    PostIt();

    virtual ~PostIt();

    // Public attribute accessor methods
    //

    /// @returns Pointer to the B2Body for the relative position asked for.
    /// @note    because this object has no body, always returns nullptr
//  virtual b2Body* getB2BodyPtrForPosition(UNUSED_ARG const Position& aRelPosition)
//  { assert(false); return nullptr; }

    /// returns the Name of the object.
    virtual const QString getName ( ) const override
    {
        return QObject::tr("PostIt");
    }

    /// Post-its have no mass. But no b2Body will be created either :-)
    virtual b2BodyType getObjectType(void) const override
    {
        return b2_staticBody;
    }

    /// returns true if the object can be rotated by the user
    /// PostIts cannot be adjusted by the player
    virtual bool isRotatable ( ) const override
    {
        return false;
    }

    /// overridden because we have our own ViewObject that displays
    /// the PostIt
    /// @param   aDefaultDepth, ZValue depth in view if not set as property,
    ///          the higher the value the more likely it is drawn on top
    ViewObjectPtr createViewObject(float aDefaultDepth = 10.0) override;

};

#endif // POSTIT_H
