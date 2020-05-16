#ifndef QTOSGWIDGET_H
#define QTOSGWIDGET_H

#include <QApplication>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDesktopWidget>
#include <QScreen>
#include <QtGlobal>
#include <QWindow>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>
#include <osg/Camera>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osg/Material>
#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include <osg/LineWidth>
#include <osg/Point>
#include <osg/BlendFunc>

#include<vector>
#include <osg/Uniform>
#include <osg/Camera>
#include <osg/NodeVisitor>


#include <iostream>
#include <osgText/Text>

class QtOSGWidget : public QOpenGLWidget
{
private:

  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;
  osg::ref_ptr<osgViewer::Viewer> _mViewer;
  osg::ref_ptr<osg::Camera> _mHud;
  qreal m_scaleX, m_scaleY;

public:
  QtOSGWidget(qreal scaleX = 1, qreal scaleY = 1, QWidget* parent = 0);

  void setScene(osg::ref_ptr<osg::Group> root);
  osg::ref_ptr<osg::Group> getScene();

  virtual ~QtOSGWidget(){}
  void setHud(osg::ref_ptr<osg::Camera> hCamera){
      _mHud = hCamera;
  }
  osg::ref_ptr<osg::Camera> getHud(){return _mHud;}
  void setScale(qreal X, qreal Y);
  osg::ref_ptr<osgViewer::Viewer> getView()
  {
      return _mViewer;
  }
//  Q_OBJECT
//public slots:
//    void changedColor(QColor color);
//    void openScene(std::string path);
//signals:
//    void orientationChanged(std::vector<double>);


protected:

  virtual void paintGL();

  virtual void resizeGL( int width, int height );

  virtual void initializeGL();

  virtual void mouseMoveEvent(QMouseEvent* event);

  virtual void mousePressEvent(QMouseEvent* event);

  virtual void mouseReleaseEvent(QMouseEvent* event);

  virtual void wheelEvent(QWheelEvent* event);

  virtual void keyPressEvent(QKeyEvent *event);

  virtual bool event(QEvent* event);

};
#endif // QTOSGWIDGET_H
