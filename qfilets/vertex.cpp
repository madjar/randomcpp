#include "vertex.h"

#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "scene.h"

Vertex::Vertex() : QGraphicsEllipseItem()
{
    setRect(-15, -15, 30, 30);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setHighlighted(false);
    QPen pen;
    pen.setWidth(3);
    setPen(pen);
}

Vertex::~Vertex()
{
    qDeleteAll(arcs);
}

QVariant Vertex::itemChange ( GraphicsItemChange change, const QVariant & value )
{
    if (change == QGraphicsItem::ItemPositionHasChanged)
    {
        foreach (Arc *a, arcs)
        {
            a->updateDisplay();
        }
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void Vertex::mousePressEvent  ( QGraphicsSceneMouseEvent * event )
{
    if (event->button() == Qt::LeftButton)
    {
        foreach (Arc *a, arcs)
        {
            a->other(this)->setHighlighted(true);
        }
    }
    QGraphicsItem::mousePressEvent (event);
}

void Vertex::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    if (event->button() == Qt::LeftButton)
    {
        foreach (Arc *a, arcs)
        {
            a->other(this)->setHighlighted(false);
        }
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void Vertex::setHighlighted(bool highlighted)
{
    if (scene() && qobject_cast<Scene *>(scene())->won())
        return;
    if (highlighted)
        setBrush(QBrush(Qt::blue));
    else
        setBrush(QBrush(Qt::red));
}
