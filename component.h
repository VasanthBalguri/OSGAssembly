#ifndef COMPONENT_H
#define COMPONENT_H

#include "osginclude.h"

class CollisionShape : public osg::ShapeDrawable
{
public:
    CollisionShape(int objshape,float length = 0.0,float breadth = 0.0,float thickness = 0.0);

    btCollisionShape* getbtCollisionShape()
    {
        return collisionShape;
    }

    virtual const char* className() const {return "CollisionShape";}

protected:
    btCollisionShape* collisionShape;
};

class Component : public osg::MatrixTransform
{
public:
    Component(CollisionShape* shape,
              std::string componentID,
              osg::Vec3 position,
              osg::Quat orientation, int type,
              float mass);

    void updateTransform();
    virtual const char* className() const {return "Component";}
    btRigidBody* getRigidBody(){return body;}
    ~Component()
    {
       // delete body;
       // delete motion;
    }

protected:
    osg::ref_ptr<CollisionShape> shape;
    float mass;
    btRigidBody* body;
    btMotionState* motion;
    btVector3 momentOfInertia;

};

class ComponentCallback : public osg::NodeCallback
{
public:
    ComponentCallback(){}

    virtual void operator ()(osg::Node* node,osg::NodeVisitor* nv);
};

#endif // COMPONENT_H
