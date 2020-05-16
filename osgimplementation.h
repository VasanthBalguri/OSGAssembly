#ifndef OSGIMPLEMENTATION_H
#define OSGIMPLEMENTATION_H
/* Has teh classses required for this project
 * will be refactored later*/

#include<vector>
#include <iostream>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>
#include <osg/Camera>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/AnimationPath>
#include <osgAnimation/EaseMotion>
#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <osg/LineWidth>
#include <osg/Point>
#include <osg/BlendFunc>
#include <osg/Uniform>
#include <osg/Camera>
#include <osg/NodeVisitor>
#include <osg/MatrixTransform>
#include <osgText/Text>
#include <osgGA/EventHandler>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgGA/EventVisitor>

#include <bullet/btBulletDynamicsCommon.h>



enum OBJSHAPE
{
    SURFACE = 0,
    BOX = 1,
    SPHERE = 2
};
enum OBJCOLLISION
{
    NO_COLLISION = 0,
    STATIC = 1,
    RIGIDBODY = 2
};

enum VISITOROPERATION
{
    LIST = 0,
    FIND = 1,
    REMOVE = 2
};

osg::Geode* createAxis(osg::Matrix matrix,float scale);
osg::AnimationPath* createAnimationPath( float radius, float time);


//will write in seperate file
class ComponentCallback : public osg::NodeCallback
{
public:
    ComponentCallback(){}

    virtual void operator ()(osg::Node* node,osg::NodeVisitor* nv);
};

class GlobalPhysicsCallback : public osg::NodeCallback
{
public:
    GlobalPhysicsCallback(){}

    virtual void operator ()(osg::Node* node,osg::NodeVisitor* nv);
};

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

class GlobalPhysics : public osg::Group
{
public:
    GlobalPhysics();
    btDynamicsWorld* getWorld()
    {
        return world;
    }
    void addComponent(Component* component);
    void removeComponent(std::string componentID);
   ~GlobalPhysics()
    {
      delete collisionConfig;
      delete solver;
      delete broadphase;
      delete dispatcher;
      delete world;
    }

    bool pause = false;
protected:
    btDynamicsWorld* world;
    btDispatcher* dispatcher;
    btCollisionConfiguration* collisionConfig;
    btBroadphaseInterface* broadphase;
    btConstraintSolver* solver;

};

class ActionVisitor : public osg::NodeVisitor
{
  public:
    ActionVisitor(int operation,std::string componentID = ""):_operation(operation),_componentID(componentID){setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);}
   // virtual void apply(osg::Node& node);
    //virtual void apply(osg::Geode& geode);
    int getNumberofInstances();
    int getInstanceIndex(int position = 0);

    virtual void apply(osg::Node& node);
    virtual void apply(osg::Transform &component);

        std::vector<osg::Transform*> _components;
  private:
    int _operation;
    std::string _componentID;
    int _instances = 0;

};

class PhysicsJoint : public osg::Transform
{
public:
PhysicsJoint(osg::ref_ptr<Component> parent,osg::ref_ptr<Component> child,osg::ref_ptr<GlobalPhysics> world)
{
    btVector3 pivot1(0.0,10.0,0.0),pivot2(0.0,20.0,0.0), axis1(1.0,0.0,0.0), axis2(1.0,0.0,0.0);
    std::cout<<"bp1"<<std::endl;
    btRigidBody* body1 = parent->getRigidBody();
    btRigidBody* body2 = child->getRigidBody();
    hinge = new btHingeConstraint(*body1,*body2,pivot1,pivot2,axis1,axis2);

    //fixed = new btFixedConstraint(*body1,*body2);
    world->getWorld()->addConstraint(hinge);
    world->addChild(this);
    hinge->enableAngularMotor(true,3,30);
}
private:
btHingeConstraint* hinge;
btFixedConstraint* fixed;
osg::ref_ptr<osg::Geode> displayGeom;
};

GlobalPhysics *createScene();
#endif // OSGIMPLEMENTATION_H
