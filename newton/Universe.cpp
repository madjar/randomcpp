#include "Universe.h"
#include "Particle.h"

#include <QGraphicsSceneMouseEvent>

Universe::Universe()
{
	startTimer(1000/33);
}

void Universe::timerEvent (QTimerEvent *)
{
	advance();
}

void Universe::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
	if (mouseEvent->button()==Qt::LeftButton)
	{
		Particle *part = new Particle;
		part->setPos(mouseEvent->scenePos());
		this->addItem(part);
	}
}

