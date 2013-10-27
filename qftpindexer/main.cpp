
#include <QCoreApplication>
#include <QUrl>
#include "scanner.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Scanner s (app.arguments().mid(1));
    s.start();

    return app.exec();
}
