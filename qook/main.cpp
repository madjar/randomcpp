#include <QtGui/QApplication>
#include "qookwindow.h"
#include "dbconnexionwizard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Dubus");
    QApplication::setApplicationName("Qook");

    if (!DBConnexionWizard::connectToDb())
        return 1;

    QookWindow w;
    w.show();

    return a.exec();
}
