#ifndef OSGINCLUDE_H
#define OSGINCLUDE_H

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
    SPHERE = 2,
    CYLINDER = 3
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

#endif // OSGINCLUDE_H
