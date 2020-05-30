#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "osgimplementation.h"
#include "osglogger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    osg::setNotifyLevel(osg::INFO);
    osg::setNotifyHandler(new OsgLogger("mylog.txt"));
    qOsg = new QtOSGWidget(1,1,this);
    osg::ref_ptr<GlobalPhysics> scene = createScene();
  //  qOsg->getView()->getEventQueue()->getCurrentEventState()->get == osgGA::GUIEventAdapter::KEY_Space;
   // qOsg->getView()->addEventHandler(new KeyHandler(scene.get()));
    qOsg->setScene(scene);
    ActionVisitor myinfo(LIST);
    scene->accept(myinfo);
//    OsgTreeView* g = new OsgTreeView(this);
//    for(int i=0;i<5;i++)
//    {
//        for(int j=0;j<5;j++)
//        {
//            g->createNode(i*10,j*10,"first","node");
//        }
//    }

//g->createNode(0,0,"first","node");
    ui->setupUi(this);
    this->setCentralWidget(qOsg);
    qOsg->setFocus();
   // qOsg->setScene(createScene());
}

MainWindow::~MainWindow()
{
    delete ui;
}
