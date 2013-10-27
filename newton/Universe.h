#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <QGraphicsScene>

class Universe : public QGraphicsScene
{
	Q_OBJECT

public:
	Universe();
	
public slots:
	//void advance();

protected:
	void timerEvent(QTimerEvent *event);
	void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
};

#endif
