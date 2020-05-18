#include "osgimplementation.h"

using namespace osg;

Component::Component(CollisionShape *shape,
                     std::string componentID,
                     Vec3 position,
                     Quat orientation,
                     int type,float mass):mass(mass)
{
    this->setName(componentID.c_str());
    osg::Matrix m;
    m.setTrans(position);
    m.setRotate(orientation);
    this->setMatrix(m);

    btVector3 pos(position.x(),position.y(),position.z());
    btQuaternion quat(orientation.x(),orientation.y(),orientation.z(),orientation.w());
    btTransform t;
    t.setOrigin(pos);
    t.setRotation(quat);

    if(mass!=0)
        shape->getbtCollisionShape()->calculateLocalInertia(mass,momentOfInertia);
    else
        momentOfInertia = btVector3(0.0,0.0,0.0);

    motion=new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,shape->getbtCollisionShape(),momentOfInertia);
    info.m_restitution = 0;
    body=new btRigidBody(info);
    this->addChild(shape);
}
void Component::updateTransform()
{
        btTransform t;
        t = body->getWorldTransform();
        osg::Vec3 v(t.getOrigin().x(),t.getOrigin().y(),t.getOrigin().z());
        osg::Quat q(t.getRotation().x(),t.getRotation().y(),t.getRotation().z(),t.getRotation().w());
        osg::Matrix m;
        m.setRotate(q);
        m.setTrans(v);
        this->setMatrix(m);
}

CollisionShape::CollisionShape(int objshape, float length, float breadth, float thickness)
{
    switch(objshape)
    {
    case SURFACE:
    {
        collisionShape = new btStaticPlaneShape(btVector3(0,1,0),0);

        osg::ref_ptr<osg::Box> plane = new osg::Box(osg::Vec3(0.0,-0.5,0.0),100.0,1.0,100.0);
        this->setShape(plane);
        break;
    }
    case BOX:
    {
        collisionShape=new btBoxShape(btVector3(length/2.0,breadth/2.0,thickness/2.0));

        osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3(0.0,0.0,0.0),length,breadth,thickness);
        this->setShape(box);
        break;
    }
    case SPHERE:
    {
        collisionShape = new btSphereShape(length/2);

        osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3(0.0,0.0,0.0),length/2.0);
        this->setShape(sphere);
        break;
    }
    case CYLINDER:
    {
       collisionShape = new btCylinderShape(btVector3(length/2,breadth/2,length/2));

       osg::ref_ptr<osg::Cylinder> cylinder = new osg::Cylinder(osg::Vec3(0.0,0.0,0.0),length/2,breadth);
       this->setShape(cylinder);
       break;
    }

    }
}

void ComponentCallback::operator ()(osg::Node* node,osg::NodeVisitor* nv)
{
    Component* component = dynamic_cast<Component*>(node);
    component->updateTransform();
    traverse(node,nv);
}
