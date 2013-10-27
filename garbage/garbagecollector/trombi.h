#ifndef TROMBI_H
#define TROMBI_H

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QMap>
#include "popchecker.h"
#include "entry.h"

class Trombi : public QObject
{
    Q_OBJECT
public:
    explicit Trombi(const QString &host, quint16 port, bool dump = false, int firstId = 0, int lastId = 2000, QObject *parent = 0);
    void searchEntries();

signals:
    void matchFound(QPixmap, QString, QString);
    void entryFound(QPixmap);
    void progressChanged(int);
    void minMaxChanged(int, int);

private slots:
    void startNextDownload();
    void entryReady();
    void popCheckFinished(bool valid);

private:
    QString host;
    quint16 port;
    bool dump;
    int firstId;
    int lastId;
    int currentId;
    QMap<PopChecker*, Entry*> currentChecks;
};

#endif // TROMBI_H
