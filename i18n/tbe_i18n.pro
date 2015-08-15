TEMPLATE = app
TARGET = release
DEPENDPATH +=.
INCLUDEPATH +=.
SOURCES += \
../src/loadsave/ToolboxGroupSerializer.h \
../src/loadsave/LocalString.h \
../src/loadsave/BackgroundSerializer.h \
../src/loadsave/GoalSerializer.h \
../src/loadsave/AbstractObjectSerializer.h \
../src/loadsave/ObjectFactory.h \
../src/loadsave/Level.h \
../src/tbe_global.h \
../src/tbe_paths.h \
../src/Box2D/Box2D.h \
../src/Box2D/Rope/b2Rope.h \
../src/Box2D/Dynamics/Joints/b2WeldJoint.h \
../src/Box2D/Dynamics/Joints/b2RopeJoint.h \
../src/Box2D/Dynamics/Joints/b2WheelJoint.h \
../src/Box2D/Dynamics/Joints/b2Joint.h \
../src/Box2D/Dynamics/Joints/b2RevoluteJoint.h \
../src/Box2D/Dynamics/Joints/b2MouseJoint.h \
../src/Box2D/Dynamics/Joints/b2FrictionJoint.h \
../src/Box2D/Dynamics/Joints/b2DistanceJoint.h \
../src/Box2D/Dynamics/Joints/b2PulleyJoint.h \
../src/Box2D/Dynamics/Joints/b2GearJoint.h \
../src/Box2D/Dynamics/Joints/b2PrismaticJoint.h \
../src/Box2D/Dynamics/Joints/b2MotorJoint.h \
../src/Box2D/Dynamics/b2ContactManager.h \
../src/Box2D/Dynamics/b2World.h \
../src/Box2D/Dynamics/b2Island.h \
../src/Box2D/Dynamics/b2Body.h \
../src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
../src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
../src/Box2D/Dynamics/Contacts/b2PolygonContact.h \
../src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
../src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
../src/Box2D/Dynamics/Contacts/b2CircleContact.h \
../src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
../src/Box2D/Dynamics/Contacts/b2Contact.h \
../src/Box2D/Dynamics/Contacts/b2ContactSolver.h \
../src/Box2D/Dynamics/b2TimeStep.h \
../src/Box2D/Dynamics/b2WorldCallbacks.h \
../src/Box2D/Dynamics/b2Fixture.h \
../src/Box2D/Collision/b2Collision.h \
../src/Box2D/Collision/b2TimeOfImpact.h \
../src/Box2D/Collision/b2BroadPhase.h \
../src/Box2D/Collision/Shapes/b2Shape.h \
../src/Box2D/Collision/Shapes/b2EdgeShape.h \
../src/Box2D/Collision/Shapes/b2CircleShape.h \
../src/Box2D/Collision/Shapes/b2PolygonShape.h \
../src/Box2D/Collision/Shapes/b2ChainShape.h \
../src/Box2D/Collision/b2Distance.h \
../src/Box2D/Collision/b2DynamicTree.h \
../src/Box2D/Common/b2StackAllocator.h \
../src/Box2D/Common/b2Math.h \
../src/Box2D/Common/b2Settings.h \
../src/Box2D/Common/b2Draw.h \
../src/Box2D/Common/b2GrowableStack.h \
../src/Box2D/Common/b2Timer.h \
../src/Box2D/Common/b2BlockAllocator.h \
../src/model/World.h \
../src/model/AbstractObject.h \
../src/model/TriggerExplosion.h \
../src/model/Glue.h \
../src/model/PivotPointPtr.h \
../src/model/TranslationGuide.h \
../src/model/AbstractJoint.h \
../src/model/PivotPoint.h \
../src/model/BalloonCactus.h \
../src/model/CircleObjects.h \
../src/model/Goal.h \
../src/model/Link.h \
../src/model/Spring.h \
../src/model/Scenery.h \
../src/model/Property.h \
../src/model/AbstractObjectPtr.h \
../src/model/PolyObject.h \
../src/model/RectObject.h \
../src/model/Position.h \
../src/model/Butterfly.h \
../src/model/PostIt.h \
../src/model/TranslationGuidePtr.h \
../src/model/ColaMintBottle.h \
../src/control/InsertUndoCommand.h \
../src/control/ViewObjectActionDectorator.h \
../src/control/RotateUndoCommand.h \
../src/control/ToolboxGroup.h \
../src/control/AbstractUndoCommand.h \
../src/control/ChoosePhoneUndoCommand.h \
../src/control/DeleteUndoCommand.h \
../src/control/DummyUndoCommand.h \
../src/control/ResizeUndoCommand.h \
../src/control/MoveUndoCommand.h \
../src/control/UndoSingleton.h \
../src/view/EditObjectDialog.h \
../src/view/ImageCache.h \
../src/view/SimulationControls.h \
../src/view/WinFailDialog.h \
../src/view/MainWindow.h \
../src/view/ViewLink.h \
../src/view/ViewObject.h \
../src/view/Background.h \
../src/view/GoalEditor.h \
../src/view/SaveLevelInfo.h \
../src/view/ToolboxListWidgetItem.h \
../src/view/ViewPostIt.h \
../src/view/ChooseLevel.h \
../src/view/PieMenu.h \
../src/view/resizinggraphicsview.h \
../src/view/EditLevelProperties.h \
../src/view/ChoosePhoneNumber.h \
../src/view/animateddialog.h \
../src/view/ViewDetonatorBox.h \
../src/view/ViewWorld.h \
../src/view/Popup.h \
../src/view/ListViewItemTooltip.h \
../src/view/GameResources.h \
../src/loadsave/ObjectFactory.cpp \
../src/loadsave/AbstractObjectSerializer.cpp \
../src/loadsave/ToolboxGroupSerializer.cpp \
../src/loadsave/BackgroundSerializer.cpp \
../src/loadsave/GoalSerializer.cpp \
../src/loadsave/Level.cpp \
../src/loadsave/LocalString.cpp \
../src/Box2D/Rope/b2Rope.cpp \
../src/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
../src/Box2D/Dynamics/Joints/b2Joint.cpp \
../src/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
../src/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
../src/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
../src/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
../src/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
../src/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
../src/Box2D/Dynamics/Joints/b2GearJoint.cpp \
../src/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
../src/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
../src/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
../src/Box2D/Dynamics/b2World.cpp \
../src/Box2D/Dynamics/b2ContactManager.cpp \
../src/Box2D/Dynamics/b2Fixture.cpp \
../src/Box2D/Dynamics/b2Body.cpp \
../src/Box2D/Dynamics/b2Island.cpp \
../src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
../src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
../src/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
../src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
../src/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
../src/Box2D/Dynamics/Contacts/b2Contact.cpp \
../src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
../src/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
../src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
../src/Box2D/Dynamics/b2WorldCallbacks.cpp \
../src/Box2D/Collision/b2DynamicTree.cpp \
../src/Box2D/Collision/b2CollideEdge.cpp \
../src/Box2D/Collision/b2TimeOfImpact.cpp \
../src/Box2D/Collision/b2Collision.cpp \
../src/Box2D/Collision/b2CollideCircle.cpp \
../src/Box2D/Collision/Shapes/b2ChainShape.cpp \
../src/Box2D/Collision/Shapes/b2CircleShape.cpp \
../src/Box2D/Collision/Shapes/b2PolygonShape.cpp \
../src/Box2D/Collision/Shapes/b2EdgeShape.cpp \
../src/Box2D/Collision/b2BroadPhase.cpp \
../src/Box2D/Collision/b2Distance.cpp \
../src/Box2D/Collision/b2CollidePolygon.cpp \
../src/Box2D/Common/b2Timer.cpp \
../src/Box2D/Common/b2BlockAllocator.cpp \
../src/Box2D/Common/b2Math.cpp \
../src/Box2D/Common/b2Settings.cpp \
../src/Box2D/Common/b2StackAllocator.cpp \
../src/Box2D/Common/b2Draw.cpp \
../src/main.cpp \
../src/model/World.cpp \
../src/model/AbstractJoint.cpp \
../src/model/Link.cpp \
../src/model/Butterfly.cpp \
../src/model/PivotPoint.cpp \
../src/model/Spring.cpp \
../src/model/PolyObject.cpp \
../src/model/ColaMintBottle.cpp \
../src/model/Scenery.cpp \
../src/model/Property.cpp \
../src/model/AbstractObject.cpp \
../src/model/BalloonCactus.cpp \
../src/model/RectObject.cpp \
../src/model/Goal.cpp \
../src/model/Glue.cpp \
../src/model/TranslationGuide.cpp \
../src/model/PostIt.cpp \
../src/model/TriggerExplosion.cpp \
../src/model/CircleObjects.cpp \
../src/model/Position.cpp \
../src/backtrace.cpp \
../src/control/AbstractUndoCommand.cpp \
../src/control/InsertUndoCommand.cpp \
../src/control/ChoosePhoneUndoCommand.cpp \
../src/control/MoveUndoCommand.cpp \
../src/control/ResizeUndoCommand.cpp \
../src/control/ToolboxGroup.cpp \
../src/control/RotateUndoCommand.cpp \
../src/control/DummyUndoCommand.cpp \
../src/control/ViewObjectActionDectorator.cpp \
../src/control/UndoSingleton.cpp \
../src/control/DeleteUndoCommand.cpp \
../src/view/MainWindow.cpp \
../src/view/ViewToolboxGroup.cpp \
../src/view/resizinggraphicsview.cpp \
../src/view/GameResources.cpp \
../src/view/SaveLevelInfo.cpp \
../src/view/PieMenu.cpp \
../src/view/ChooseLevel.cpp \
../src/view/ViewLink.cpp \
../src/view/ViewPostIt.cpp \
../src/view/ToolboxListWidgetItem.cpp \
../src/view/ViewWorld.cpp \
../src/view/animateddialog.cpp \
../src/view/SimulationControls.cpp \
../src/view/GoalEditor.cpp \
../src/view/EditObjectDialog.cpp \
../src/view/EditLevelProperties.cpp \
../src/view/ChoosePhoneNumber.cpp \
../src/view/ViewObject.cpp \
../src/view/ViewDetonatorBox.cpp \
../src/view/ListViewItemTooltip.cpp \
../src/view/ImageCache.cpp \
../src/view/WinFailDialog.cpp \
../src/view/ListViewItemTooltip.ui \
../src/view/ChoosePhoneNumber.ui \
../src/view/ViewPostIt.ui \
../src/view/WinFailDialog.ui \
../src/view/ChooseLevel.ui \
../src/view/SimulationControls.ui \
../src/view/SaveLevelInfo.ui \
../src/view/EditObjectDialog.ui \
../src/view/EditLevelProperties.ui \
../src/view/MainWindow.ui \
../src/view/GoalEditor.ui \
../src/view/GameResources.ui
TRANSLATIONS += tbe_en.ts \
                tbe_es.ts \
                tbe_nl.ts \
                tbe_ms.ts \
                tbe_uk.ts \
                tbe_lt.ts \
                tbe_be.ts \
                tbe_sv.ts \
                tbe_ru.ts