/*Has most of the implemetation
 * need to move it to seperate files*/

#include "osgimplementation.h"

using namespace osg;

//This must be handled externally..
GlobalPhysics* createScene()
{
    //standard startup setup
    ref_ptr<GlobalPhysics> world = new GlobalPhysics();

    osg::ref_ptr<osg::StateSet> stateSet = world->getOrCreateStateSet();
    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    //adding objects(at mass = 0.0 the object is static)
    world->addUpdateCallback(new GlobalPhysicsCallback());
    ref_ptr<CollisionShape> plane = new CollisionShape(SURFACE);
    plane->setColor(osg::Vec4( 0.8f, 0.5f, 0.2f, 0.5f ));
    ref_ptr<CollisionShape> box1 = new CollisionShape(BOX,5.0,5.0,5.0);
    box1->setColor(osg::Vec4( 0.0f, 0.9f, 0.1f, 1.f ));
    ref_ptr<CollisionShape> box2 = new CollisionShape(BOX,8.0,8.0,2.0);
    box2->setColor(osg::Vec4( 0.0f, 0.9f, 0.1f, 1.f ));
    ref_ptr<CollisionShape> box3 = new CollisionShape(BOX,100.0,30.0,3.0);
    box3->setColor(osg::Vec4( 0.8f, 0.5f, 0.2f, 0.5f ));
    ref_ptr<Component> base = new Component(plane.get(),"base",Vec3(0.0,0.0,0.0),Quat(0.0,Vec3(1.0,0.0,0.0)),STATIC,0.0);
    world->addComponent(base.get());
    ref_ptr<Component> comp1 = new Component(box1.get(),"box1",Vec3(0.0,15.0,0.0),Quat(0.0,Vec3(1.0,0.0,0.0)),RIGIDBODY,10.0);
    world->addComponent(comp1.get());
    ref_ptr<Component> comp2 = new Component(box2.get(),"box2",Vec3(0.0,20.0,0.0),Quat(0.0,Vec3(1.0,0.0,0.0)),RIGIDBODY,10.0);
    world->addComponent(comp2.get());
    ref_ptr<Component> borderN = new Component(box3.get(),"borderN",Vec3(-50.0,0.0,0.0),Quat(osg::PI/2.0,Vec3(0.0,1.0,0.0)),RIGIDBODY,0.0);
    world->addComponent(borderN.get());
    ref_ptr<Component> borderS = new Component(box3.get(),"borderS",Vec3(50.0,0.0,0.0),Quat(osg::PI/2.0,Vec3(0.0,1.0,0.0)),RIGIDBODY,0.0);
    world->addComponent(borderS.get());
    ref_ptr<Component> borderE = new Component(box3.get(),"borderE",Vec3(0.0,0.0,50.0),Quat(0.0,Vec3(1.0,0.0,0.0)),RIGIDBODY,0.0);
    world->addComponent(borderE.get());
    ref_ptr<Component> borderW = new Component(box3.get(),"borderW",Vec3(0.0,0.0,-50.0),Quat(0.0,Vec3(1.0,0.0,0.0)),RIGIDBODY,0.0);
    world->addComponent(borderW.get());

    ref_ptr<PhysicsJoint> hinge1 = new PhysicsJoint(comp1,comp2,world);

    //for displaying global axes
    osg::Matrix m;
    m.setTrans(0.0,0.0,0.0);
    m.setRotate(Quat(0.0,Vec3(1.0,0.0,0.0)));
    ref_ptr<Geode> axes = createAxis(m,10);
    world->addChild(axes);

    return world.release();
}

//improve on this
Geode* createAxis(osg::Matrix matrix,float scale)
{
    ref_ptr<osg::Geode> geode  = new osg::Geode;
    osg::ref_ptr<osg::Geometry> geometry (new osg::Geometry());

    osg::ref_ptr<osg::Vec3Array> vertices (new osg::Vec3Array());
    vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
    vertices->push_back (osg::Vec3 ( scale*matrix(0,0), scale*matrix(0,1), scale*matrix(0,2)));
    vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
    vertices->push_back (osg::Vec3 ( scale*matrix(1,0), scale*matrix(1,1), scale*matrix(1,2)));
    vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
    vertices->push_back (osg::Vec3 ( scale*matrix(2,0), scale*matrix(2,1), scale*matrix(2,2)));
    geometry->setVertexArray (vertices.get());

    osg::ref_ptr<osg::Vec4Array> colors (new osg::Vec4Array());
    colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
    colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
    geometry->setColorArray (colors.get(), osg::Array::BIND_PER_VERTEX);
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,6));

    geode->addDrawable( geometry.get() );
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, false);
    return geode.release();
}

//from here and below needs to be moved to seperate file

