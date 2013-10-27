#include "scanner.h"

#include <QUrl>
#include <QCoreApplication>

Scanner::Scanner(QStringList adresses, QObject *parent) :
    QObject(parent), adresses(adresses), indexer(0)
{
}


void Scanner::start()
{
    indexerDone();
}

void Scanner::indexerDone()
{
    if (indexer)
        indexer->deleteLater();
    if (!adresses.isEmpty())
    {
        indexer = new Indexer(QUrl("ftp://" + adresses.takeFirst()));
        connect(indexer, SIGNAL(done()), SLOT(indexerDone()));
        indexer->start();
    }
    else
        qApp->exit(0);
}
