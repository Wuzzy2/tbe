/* The Butterfly Effect
 * This file copyright (C) 2011,2012,2016 Klaas van Gend
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

#ifndef VIEWOBJECT_H
#define VIEWOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointer>
#include "Position.h"

// forward declarations
#include "AbstractObject.h"
class AbstractUndoCommand;
#include "ViewObjectActionDectorator.h"


/** class ViewObject
  *
  * This class abstracts the actual drawing of objects
  *
  */
class ViewObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;

protected:
    /// simple constructor, do not use directly - use factoryMethod instead
    explicit ViewObject(AbstractObjectPtr anAbstractObjectPtr);

    /// image name constructor
    ViewObject(AbstractObjectPtr anAbstractObjectPtr, const QString &anImageName);

public:
    /// Static factory method member for ViewObjects and all children.
    /// Usage: ViewObjectPtr ChildPtr = ViewObject::factoryMethod<ViewPingus>(usual constructor arguments);
    /// @param _Tp  is ChildObjectName - class name of the child object
    /// @param __args  are the arguments to be forwarded to the constructor of the child object
    /// @returns a QSharedPointer pointing to the ViewObject (child) instance.
    template<typename _Tp, typename... _Args>
    static ViewObjectPtr factoryMethod(_Args &&... __args)
    {
        QSharedPointer<_Tp> p(new _Tp(std::forward<_Args>(__args)...));
        p->theThisPtr = p;
        return p;
    }

    /**
     * Empty Destructor
     */
    virtual ~ViewObject ( );

    AbstractObjectPtr getAbstractObjectPtr(void) const
    {
        return theAbstractObjectPtr->getThisPtr();
    }

    ViewObjectPtr getThisPtr() const
    {
        return ViewObjectPtr(theThisPtr);
    }

    const QString &getBaseImageName() const
    {
        return theBaseImageName;
    }

    /// @returns Aspect ratio (width/height) of the (first) image,
    ///          before it was scaled to width and height dimensions.
//  qreal getOrigImageAspectRatio(void)
//    { return thePixmapWidth / thePixmapHeight; }

    /// Sets new geometry for this object.
    /// @note This member should only be called by UndoCommands
    /// @note It will set the geometry in the AbstractObject and
    /// then update itself.
    /// @param aNewPosition
    /// @param aNewWidth
    /// @param aNewHeight
    void setNewGeometry(const Position &aNewPosition,
                        qreal aNewWidth,
                        qreal aNewHeight);
    void setNewGeometry(const Position &aNewPosition);

    /// Sets the image to be displayed to the image pointed to by anIndex.
    /// @note Supposed to be only used by AbstractObject::updateViewObject().
    /// @note New images are only loaded upon creation of the object.
    virtual void setNewImageIndex(unsigned int anIndex);

    /// based on changes in the underlying AbstractObject, adjust the image
    /// by resizing and/or rotation. This is overkill for just moving...
    virtual void adjustObjectDrawing(qreal aWidth, qreal aHeight, const Position &aCenter);

signals:
    /// SIGNAL
    /// Emitted whenever properties of the object change.
    /// Used by the Level creator to adjust the EditObjectDialog.
    /// @param anAOPtr std::shared_ptr to the AbstractObject underneath.
    void updateEditObjectDialog(AbstractObjectPtr anAOPtr);

protected:
    void adjustObjectDrawing(void);

    /// overridden to allow detection of mouse button presses & moves
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent *anEvent );
    /// overridden to allow detection of mouse button presses & moves
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent *anEvent);
    /// overridden to allow detection of mouse button presses & moves
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *anEventPtr);

    /// overridden to allow object highlighting
    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent *event );
    /// overridden to allow highlighting
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent *event );

    void realHoverEnterEvent(void);
protected slots:
    void realMousePressEvent(void);

protected:
    // Protected attributes
    //

    /// because of the symbiosis between AbstractObject and ViewObject,
    /// we're not storing the shared_ptr, but the real pointer
    /// (otherwise, no AbstractObject would ever be cleaned away)
    AbstractObject *theAbstractObjectPtr;

    typedef QList<QPixmap> ImageList;
    ImageList thePixmapList;

    ViewObjectActionDecorator theDecorator;

    friend class AbstractUndoCommand;
    friend class EditObjectDialog;
    AbstractUndoCommand *theMUCPtr;
    QPointF theClickedScenePos;
    const static int thePieMenuDelay = 225;

    qreal thePixmapWidth;
    qreal thePixmapHeight;

private:
    void initViewObjectAttributes(void);

    QString theBaseImageName;

    qreal theOldWidth;
    qreal theOldHeight;
    Position theOldPos;

    ViewObjectWeakPtr theThisPtr;

    // no copy constructor or assignment operators here!
    Q_DISABLE_COPY ( ViewObject )
};

#include "ViewObjectPtr.h"

#endif // VIEWOBJECT_H
