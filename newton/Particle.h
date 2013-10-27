#ifndef PARTICLE_H
#define PARTICLE_H

#include <QGraphicsItem>

class Particle : public QGraphicsItem
{
	
public:
	Particle();
	
	QRectF boundingRect() const;
	//QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
				QWidget *widget);
	void advance(int phase);
	
private:
	QColor color;
	qreal vx, vy;
	qreal r;
};

#endif
