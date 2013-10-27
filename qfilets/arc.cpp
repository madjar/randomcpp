#include "arc.h"

#include <QPen>
#include <QGraphicsScene>

Arc::Arc(Vertex *from, Vertex *to) :
        QGraphicsLineItem(), from(from), to(to), colliding(false)
{
    updateTimer.setSingleShot(true);
    setZValue(-1);
    QPen pen;
    pen.setWidth(3);
    setPen(pen);
    from->arcs.append(this);
    to->arcs.append(this);
    updateDisplay();
}

Arc::~Arc ()
{
    from->arcs.removeAll(this);
    to->arcs.removeAll(this);
}

void Arc::updateDisplay()
{
    QList <Arc *> toUpdate;
    if (!updateTimer.isActive())
    {
        if (scene())
        {
            setColliding(false);
            foreach (QGraphicsItem *item, scene()->items())
            {
                Arc *arc = qgraphicsitem_cast<Arc*>(item);
                if (arc && collidesWithItem(arc))
                {
                    toUpdate.append(arc);
                }
            }
        }
    }
    setLine(QLineF(from->pos(), to->pos()));
    if (!updateTimer.isActive())
    {
        foreach (Arc *arc, toUpdate)
            arc->updateColliding();

        foreach (Arc *arc, collidingArcs)
            arc->updateColliding();

        if (scene())
        {
            foreach (QGraphicsItem *item, scene()->items())
            {
                Arc *arc = qgraphicsitem_cast<Arc*>(item);
                if (arc)
                {
                    if (collidesWithItem(arc))
                    {
                        arc->setColliding(true);
                        setColliding(true);
                        if (!collidingArcs.contains(arc))
                            collidingArcs.append(arc);
                    }
                    else
                    {
                        collidingArcs.removeAll(arc);
                    }
                }
            }
        }
        updateTimer.start(50);
    }
}

void Arc::setColliding(bool colliding)
{
    this->colliding = colliding;
    QPen currentPen = pen();
    if (colliding)
        currentPen.setColor(Qt::red);
    else
        currentPen.setColor(Qt::black);
    setPen(currentPen);
}

void Arc::updateColliding(Arc* first)
{
    if (scene())
    {
        setColliding(false);
        if (first && collidesWithItem(first))
        {
            setColliding(true);
            return;
        }
        foreach (QGraphicsItem *item, scene()->items())
        {
            Arc *arc = qgraphicsitem_cast<Arc*>(item);
            if (arc && collidesWithItem(arc))
            {
                setColliding(true);
                return;
            }
        }
    }
}

bool Arc::collidesWithItem ( const QGraphicsItem * other,
                             Qt::ItemSelectionMode mode) const
{
    if (mode == Qt::IntersectsItemShape)
    {
        const Arc *arc = qgraphicsitem_cast<const Arc*>(other);
        if (arc && (
                this->from == arc->from ||
                this->from == arc->to ||
                this->to == arc->from ||
                this->to == arc->to )
            )
            return false;
    }

    return QGraphicsItem::collidesWithItem(other, mode);
}

Vertex *Arc::other(Vertex *one) const
{
    if (one == from)
        return to;
    if (one == to)
        return from;
    return 0;
}

QVariant Arc::itemChange ( GraphicsItemChange change, const QVariant & value )
{
    if (QGraphicsItem::ItemSceneChange)
    {
        if (scene())
        {
            foreach (QGraphicsItem *item, scene()->items())
            {
                Arc *arc = qgraphicsitem_cast<Arc*>(item);
                if (arc && collidesWithItem(arc))
                {
                    arc->setColliding(true);
                    setColliding(true);
                }
            }
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
