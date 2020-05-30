#ifndef OSGIMPLEMENTATION_H
#define OSGIMPLEMENTATION_H
/* Has teh classses required for this project
 * will be refactored later*/

#include <vector>
#include <iostream>

#include "osginclude.h"
#include "globalphysics.h"
#include "physicsjoints.h"

osg::Geode* createAxis(osg::Matrix matrix,float scale);
osg::AnimationPath* createAnimationPath( float radius, float time);


//will write in seperate file
GlobalPhysics *createScene();
#endif // OSGIMPLEMENTATION_H
