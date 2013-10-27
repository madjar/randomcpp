#ifndef ARC_H
#define ARC_H

#include <QGraphicsLineItem>
#include <QTimer>
#include <QList>
#include "vertex.h"

class Vertex;

class Arc : public QGraphicsLineItem
{
public:
    Arc(Vertex *from, Vertex *to);
    ~Arc();
    void updateDisplay();

    enum { Type = UserType + 1 };

    int type() const { return Type; }

    bool isColliding() const { return colliding; }
    void updateColliding(Arc* first = 0);

    bool collidesWithItem ( const QGraphicsItem * other,
                            Qt::ItemSelectionMode mode = Qt::IntersectsItemShape ) const;

    Vertex *other(Vertex *one) const;

protected:
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );

private:
    Vertex *from;
    Vertex *to;

    void setColliding(bool colliding);
    bool colliding;

    QTimer updateTimer;
    QList <Arc *> collidingArcs;
};

#endif // ARC_H
