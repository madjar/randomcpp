#include <QApplication>

#include <QtGui>

#include <cstdlib>
#include <time.h>

#include "arc.h"
#include "vertex.h"
#include "scene.h"
#include "view.h"

int main(int argc, char *argv[])
{
    time_t sec;
    time(&sec);
    qsrand((unsigned int) sec);

    QApplication app(argc, argv);
    app.setApplicationName("QFilets");

    Scene s;

    View v(&s);
    v.show();

    app.exec();
}
