#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QList>

#include "arc.h"

class Arc;

class Vertex : public QGraphicsEllipseItem
{
public:
    Vertex();
    ~Vertex();

    enum { Type = UserType + 2 };

    int type() const { return Type; }

    void setWon() {setBrush(QBrush(Qt::green));}
    
protected:
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

private:
    void setHighlighted(bool highlighted);

    QList<Arc *> arcs;

    friend class Arc;
};

#endif // VERTEX_H
