#include <QtCore/QCoreApplication>
#include <QUrl>

#include "wikicrawler.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    WikiCrawler w(QUrl("http://en.wikipedia.org/"),
                  "/wiki/Watermelon",
                  "/wiki/Christmas_tree");

    return a.exec();
}
