#include <QtGui/QApplication>
#include "servicestabwidget.h"

#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServicesTabWidget s;

    QList<QString>::const_iterator i;
    QStringList args = a.arguments();

    s.show();

    for (i = ++args.begin(); i != args.end(); i++)
        s.addServicesWidget(*i);

    if (args.size() == 1)
        s.open();

    return a.exec();
}
