#ifndef WIKICRAWLER_H
#define WIKICRAWLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class WikiCrawler : public QObject
{
    Q_OBJECT
public:
    WikiCrawler(QUrl host, QString from, QString to, QObject *parent = 0);

private slots:
    void replyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QUrl host;
    QString from;
    QString to;
    bool done;

    QHash<QString, QString> previous;

    void found();
};

#endif // WIKICRAWLER_H
