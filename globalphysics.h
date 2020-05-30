#ifndef GLOBALPHYSICS_H
#define GLOBALPHYSICS_H

#include "osginclude.h"
#include "component.h"

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

class GlobalPhysicsCallback : public osg::NodeCallback
{
public:
    GlobalPhysicsCallback(){}

    virtual void operator ()(osg::Node* node,osg::NodeVisitor* nv);
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

#endif // GLOBALPHYSICS_H
