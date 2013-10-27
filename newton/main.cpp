#include "Particle.h"
#include "Universe.h"

#include <QtGui>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	Universe scene;
	scene.setSceneRect(0, 0, 300, 300);
	//scene.setItemIndexMethod(QGraphicsScene::NoIndex);
	
	Particle *part = new Particle;
	part->setPos(100, 100);
	scene.addItem(part);
	

	QGraphicsView view(&scene);
	view.setWindowTitle(Universe::tr("Universe"));
	
	view.show();

	return app.exec();
}
