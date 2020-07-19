#include "physicsjoints.h"

PhysicsJoint::PhysicsJoint(Component* parent,Component* child,osg::Vec3 pivot1,osg::Vec3 pivot2,osg::Vec3 axis1,osg::Vec3 axis2)
{
    btVector3 btpivot1,btpivot2, btaxis1, btaxis2;
    btpivot1.setX(pivot1.x());
    btpivot1.setY(pivot1.y());
    btpivot1.setZ(pivot1.z());
    btpivot2.setX(pivot2.x());
    btpivot2.setY(pivot2.y());
    btpivot2.setZ(pivot2.z());
    btaxis1.setX(axis1.x());
    btaxis1.setY(axis1.y());
    btaxis1.setZ(axis1.z());
    btaxis2.setX(axis2.x());
    btaxis2.setY(axis2.y());
    btaxis2.setZ(axis2.z());

    btRigidBody* body1 = parent->getRigidBody();
    btRigidBody* body2 = child->getRigidBody();
    btHingeConstraint* hinge = new btHingeConstraint(*body1,*body2,btpivot1,btpivot2,btaxis1,btaxis2);

    //fixed = new btFixedConstraint(*body1,*body2);

    hinge->enableAngularMotor(true,3,30);
}
