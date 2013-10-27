#include "scene.h"

#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include "arc.h"
#include "vertex.h"
#include <cmath>

#include <QtDebug>

static const double pi = 3.141592654;

Scene::Scene() : QGraphicsScene(), number_(10), won_(false)
{
    newGame();
}

void Scene::fitInto(QRectF newRect)
{
    const qreal margin = 15;//SETTING
    newRect.adjust(margin, margin, -margin, -margin); //Margins are better-looking
    QRectF current = itemsBoundingRect();
    QTimeLine *timeLine = new QTimeLine(200, this);
    timeLine->setFrameRange(0, 100);
    connect (timeLine, SIGNAL(finished()),
             timeLine, SLOT(deleteLater()));
    foreach (QGraphicsItem *item, items())
        {
            Vertex *v = qgraphicsitem_cast<Vertex*>(item);
            if (v)
            {
                QGraphicsItemAnimation *animation = new QGraphicsItemAnimation(timeLine);
                animation->setItem(v);
                animation->setTimeLine(timeLine);
                qreal relX = (v->x() - current.left()) / current.width();
                qreal relY = (v->y() - current.top()) / current.height();
                qreal x = newRect.left() + relX * newRect.width();
                qreal y = newRect.top() + relY * newRect.height();
                animation->setPosAt(0, v->pos());
                animation->setPosAt(1, QPointF(x, y));
            }
        }
    timeLine->start();
}

void Scene::newGame()
{
    qDeleteAll(items());
    for (int i = 0; i < number(); i++)
    {
        Vertex *v = new Vertex();
        addItem(v);
        double angle = (2 * pi * i) / number();
        const double rayon = 200;
        v->setPos( rayon * cos(angle), rayon * sin(angle) );
    }
    for (int i = 0; i < number(); i++)
    {
        for (int j = 0; j < 2; j++)
        {
            Vertex *from = qgraphicsitem_cast<Vertex*>(items().at(i));
            int pos = qrand()%(number()-1);
            if (pos >= i)
                pos++;
            Vertex *to = qgraphicsitem_cast<Vertex*>( items().at(pos) );
            Arc *a = new Arc(from, to);
            addItem(a);
        }
    }
}

void Scene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    checkWin();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void Scene::checkWin()
{
    foreach (QGraphicsItem *item, items())
    {
        Arc *arc = qgraphicsitem_cast<Arc*>(item);
        if (arc && arc->isColliding())
        {
            return;
        }
    }
    emit win();
    won_=true;
    foreach (QGraphicsItem *item, items())
    {
        Vertex *vertex = qgraphicsitem_cast<Vertex*>(item);
        if (vertex)
            vertex->setWon();
    }
}
