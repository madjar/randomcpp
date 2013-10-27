#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QStringList>
#include "indexer.h"

class Scanner : public QObject
{
Q_OBJECT
public:
    explicit Scanner(QStringList adresses, QObject *parent = 0);

public slots:
    void start();

private slots:
    void indexerDone();

private:
    QStringList adresses;
    Indexer *indexer;
};

#endif // SCANNER_H
