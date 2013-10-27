#include "Particle.h"

#include <QGraphicsScene>
#include <QPainter>
//#include <QStyleOption>

Particle::Particle() : color(qrand() % 256, qrand() % 256, qrand() % 256), vx(1), vy(0), r(10)
{
}

QRectF Particle::boundingRect() const
{
	return QRectF(-r,-r,2*r,2*r);
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setBrush(color);
	painter->drawEllipse(-r,-r,2*r,2*r);
}

void Particle::advance(int phase)
{
	if (phase==0)
	{
		
		qreal x = scenePos().x();
		qreal y = scenePos().y();
		if (x<r)
		{
			x=r;
			vx=-vx;
		}
		else if (x>scene()->width() - r)
		{
			x=scene()->width() - r;
			vx=-vx;
		}
		if (y<r)
		{
			y=r;
			vy=-vy;
		}
		else if (y>scene()->height() - r)
		{
			y=scene()->height() - r;
			vy=-vy;
		}
		setPos(x,y);
		
		vy+=0.1;
	}
	if (phase==1)
	{
		setPos(mapToParent(vx, vy));
	}
}
