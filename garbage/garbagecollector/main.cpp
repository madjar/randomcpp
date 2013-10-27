#include <QApplication>

#include "../libgarbage/garbage.h"
#include "trombi.h"

#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool dumpResults = false;
    QString host;
    quint16 port = 995;

    QStringList args = a.arguments();
    QStringListIterator i (args);
    while(i.hasNext())
    {
        QString arg = i.next();
        if (arg == "-d")
            dumpResults = true;
        if (arg == "-h")
            host = i.next();
        if (arg == "-p")
            port = i.next().toUShort();
    }

    if (host.isEmpty())
    {
        QTextStream(stdout) << "USAGE : garbagecollector -h host [-p port=995 -d (to dump result in addition to the interface)]" << endl;
        return 1;
    }

    Trombi trombi(host, port, dumpResults);
    Garbage garbage;

    QObject::connect(&trombi, SIGNAL(progressChanged(int)),
                     &garbage, SLOT(setValue(int)));
    QObject::connect(&trombi, SIGNAL(minMaxChanged(int,int)),
                     &garbage, SLOT(setRange(int,int)));
    QObject::connect(&trombi, SIGNAL(entryFound(QPixmap)),
                     &garbage, SLOT(entry(QPixmap)));
    QObject::connect(&trombi, SIGNAL(matchFound(QPixmap,QString,QString)),
                     &garbage, SLOT(match(QPixmap,QString,QString)));

    garbage.show();
    trombi.searchEntries();

    return a.exec();
}
