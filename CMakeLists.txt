cmake_minimum_required(VERSION 3.1.0)

project(Qtworkbench)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
find_package(OCE REQUIRED)
find_package(Boost COMPONENTS chrono REQUIRED)
FIND_PACKAGE( OpenSceneGraph COMPONENTS osgDB osgGA osgViewer osgAnimation osg)
find_package(Bullet REQUIRED)

include_directories(${OCE_INCLUDE_DIRS})
include_directories(${BULLET_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Qtworkbench
    mainwindow.ui
    qtosgwidget.cpp
    mainwindow.cpp
    component.cpp
    globalphysics.cpp
    osglogger.cpp
    physicsjoints.cpp
    osgimplementation.cpp
    main.cpp
)

target_link_libraries(Qtworkbench Qt5::Widgets ${OPENSCENEGRAPH_LIBRARIES}  ${BULLET_LIBRARIES} ${Boost_LIBRARIES} FWOSPlugin PTKernel TKBinL TKBin TKBinTObj TKBinXCAF TKBool TKBO TKBRep TKCAF TKCDF TKernel TKFeat TKFillet TKGeomAlgo TKGeomBase TKG2d TKG3d TKHLR TKIGES TKLCAF TKMath TKMesh TKMeshVS TKNIS TKOffset TKOpenGl TKPCAF TKPLCAF TKPrim TKPShape TKService TKShapeSchema TKShHealing TKStdLSchema TKStdSchema TKSTEPAttr TKSTEPBase TKSTEP TKSTEP209 TKSTL TKTObj TKTopAlgo TKVoxel TKVRML TKV3d TKXCAFSchema TKXCAF TKXDEIGES TKXDESTEP TKXMesh TKXmlL TKXml TKXmlTObj TKXmlXCAF TKXSBase)
