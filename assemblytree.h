#ifndef ASSEMBLYTREE_H
#define ASSEMBLYTREE_H

#include <QFrame>
#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QColor>
#include <QGraphicsItem>
#include <QString>

class NodeRep : public QGraphicsItem
{
    //Q_OBJECT
public:
    NodeRep(){}
    NodeRep(const NodeRep&){}
    NodeRep& operator =(const NodeRep&){}

    NodeRep(double x,double y,std::string name,std::string className);
    double getPosX(){return position.x();}
    double getPosY(){return position.y();}
    QPointF getPos(){return position;}
    std::string getName(){return nodeName.toStdString();}
    std::string getCalssName(){return nodeClassName.toStdString();}
    void setPosX(double x){position.setX(x);update(); }
    void setPosY(double y){position.setY(y);update(); }
    void setName(std::string name){nodeName = QString::fromUtf8(name.c_str());}
    void setClassName(std::string name){nodeClassName = QString::fromUtf8(name.c_str());}
    QRectF boundingRect() const override;
//    QPainterPath shape();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *) override;

//signals:
//    SourcePositionChanged(QPointF position);
//    DestinationPositionChanged(QPointF position);

//protected:
//    virtual void wheelEvent(QWheelEvent *);
//    virtual void mouseMoveEvent(QMouseEvent* event);
//    virtual void mousePressEvent(QMouseEvent* event);
//    virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    QString nodeName;
    QString nodeClassName;
    QPointF position;
};

class Edge : public QGraphicsItem
{
   // Q_OBJECT
public:
    Edge(NodeRep *source,NodeRep *destination);
    Edge(){}
    Edge(const Edge&){}
    Edge& operator =(const Edge&){}

//public slots:
//    void ChangedSourcePosition(QPointF position);
//    void ChangedDestinationPosition(QPointF position);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *) override;

private:
    QPointF sourcePos;
    QPointF destPos;
};

class OsgTreeView : public QGraphicsView
{
    //Q_OBJECT
public:
    OsgTreeView(QWidget *parent = 0);
    void createNode(double x,double y,std::string name,std::string className);
    int addNode(NodeRep& node){return 0;}
    bool removeNode(int i){return false;}
    void attach(NodeRep &parent,NodeRep &child);
protected:
    //virtual void wheelEvent(QWheelEvent *);
    //virtual void mouseMoveEvent(QMouseEvent* event);
    //virtual void mousePressEvent(QMouseEvent* event);
    //virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    QGraphicsScene *scene = new QGraphicsScene(this);
};


#endif // ASSEMBLYTREE_H
