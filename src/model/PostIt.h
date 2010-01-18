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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef POSTIT_H
#define POSTIT_H

#include "BaseObject.h"


/** the PostIt class is where the level hints are.
 *  the player can click on them to get the hints.
 *
 *  PostIts do not have a body or shape in simulation
 */
class PostIt : public BaseObject
{
public:
    PostIt();

	virtual ~PostIt();

	// Public attribute accessor methods
	//

	/// returns the Name of the object.
	virtual const QString getName ( ) const
	{
		return QObject::tr("PostIt");
	}

	/// returns the Tooltip of the object.
	virtual const QString getToolTip ( ) const
	{
		return QObject::tr("Someone left notes all over the place.\n"
						   "You know, those yellow 3x3 inch pieces of paper.\n"
						   "You might want to read them - it may help!");
	}

	/// returns true if the object can be rotated by the user
	/// PostIts cannot be adjusted by the player
	virtual bool isRotatable ( ) const
	{	return false; }

	/// returns whether the object can be resized by the user
	/// PostIts cannot be adjusted by the player
	virtual SizeDirections isResizable ( ) const
	{	return NORESIZING;	}

	virtual DrawObject* createDrawObject();

};

#endif // POSTIT_H