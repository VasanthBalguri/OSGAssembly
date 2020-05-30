#include "globalphysics.h"

using namespace osg;

void ActionVisitor::apply(osg::Node &node)
{
    traverse(node);
}

void ActionVisitor::apply(osg::Transform &component)
{
    switch(_operation)
    {
    case LIST:
        std::cout<<component.className()<<"::"<<component.getName()<<std::endl;;
        break;
    case FIND:
        if(_componentID != "" &&
                std::string(component.getName()) == _componentID &&
                std::string(component.className()) == "Component")
        {
            _instances++;
            _components.push_back(&component);
        }
        break;
    }
    traverse(component);
}

GlobalPhysics::GlobalPhysics()
{
    collisionConfig=new btDefaultCollisionConfiguration();
    dispatcher=new btCollisionDispatcher(collisionConfig);
    broadphase=new btDbvtBroadphase();
    solver=new btSequentialImpulseConstraintSolver();
    world=new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfig);
    world->setGravity(btVector3(0,-10,0));
    //gContactAddedCallback=this->collisionCallback;
}

void GlobalPhysics::addComponent(Component *component)
{
    component->addUpdateCallback(new ComponentCallback());
    world->addRigidBody(component->getRigidBody());
    this->addChild(component);
}
void GlobalPhysics::removeComponent(std::string componentID)
{
    ActionVisitor removal(FIND,componentID);
    this->accept(removal);
    this->removeChild(removal._components[0]);
}
void GlobalPhysicsCallback::operator ()(osg::Node* node,osg::NodeVisitor* nv)
{
    GlobalPhysics* globalPhysics = dynamic_cast<GlobalPhysics*>(node);
    if(!globalPhysics->pause)
        globalPhysics->getWorld()->stepSimulation(1/60.0,20);
    traverse(node,nv);
}


