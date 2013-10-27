#ifndef INDEXER_H
#define INDEXER_H

#include <QObject>
#include <QUrlInfo>
#include <QUrl>
#include <QFtp>
#include <QString>
#include <QStringList>

class Indexer : public QObject
{
    Q_OBJECT
public:
    Indexer(QUrl url, QObject *parent = 0);

public slots:
    void start();

signals:
    void done();

private slots:
    void ftpDone(bool error);
    void ftpListInfo(const QUrlInfo &urlInfo);

private:
    void processNextDirectory();

    static QString sanitize(const QString &string);

    QFtp ftp;
    QUrl url;
    QString currentDir;
    QStringList pendingDirs;
};

#endif // INDEXER_H
