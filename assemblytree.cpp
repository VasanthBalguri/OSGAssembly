#include "assemblytree.h"

OsgTreeView::OsgTreeView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);

}

void OsgTreeView::createNode(double x,double y,std::string name,std::string className)
{
    NodeRep* node = new NodeRep(x,y,name,className);
    scene->addItem(node);

    //return node;
}


NodeRep::NodeRep(double x, double y, std::string name, std::string className)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);

    position.setX(x);
    position.setY(y);
    nodeName = QString::fromUtf8(name.c_str());
    nodeClassName = QString::fromUtf8(className.c_str());

}

void NodeRep::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawEllipse(10,10 , 40, 20);
    //painter->drawRect(-40,-20,40,60);
    setPos(position);
}

//void NodeRep::attach(NodeRep& child)
//{
//    Edge e(this,&child);
//}

QRectF NodeRep::boundingRect() const
{
    return QRectF(-40,-20,40,20);
}

//QPainterPath NodeRep::shape()
//{
//    QPainterPath path;
//    path.addEllipse(position , 40, 20);
//    return path;
//}

Edge::Edge(NodeRep *source, NodeRep *destination)
{
    sourcePos.setX(source->getPosX());
    sourcePos.setY(source->getPosY() - 10);


    destPos.setX(destination->getPosX());
    destPos.setY(destination->getPosY() - 10);
}
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *)
{
    painter->setPen(QPen(Qt::black, 0));
    painter->drawLine(sourcePos,destPos);
}

QRectF Edge::boundingRect() const
{
    return QRectF(sourcePos.x(),sourcePos.y(),destPos.x(),destPos.y());
}
