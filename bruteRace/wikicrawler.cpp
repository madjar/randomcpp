#include "wikicrawler.h"
#include "wikipage.h"

#include <QTextStream>
#include <QNetworkRequest>

#include <QtDebug>

WikiCrawler::WikiCrawler(QUrl host, QString from, QString to, QObject *parent) :
        QObject(parent),
        manager(new QNetworkAccessManager(this)),
        host(host), from(from), to(to), done(false)
{
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url = host;
    url.setPath(from);
    manager->get(QNetworkRequest(url));
}

void WikiCrawler::replyFinished(QNetworkReply *reply)
{
    qDebug() << "testing" << reply->url();
    QString page = QTextStream(reply).readAll();
    WikiPage wp(page);
    if (reply->url().path() == to || wp.canonicalUrl()== to )
    {
        done = true;
        qDebug() << "trouvé";
        found();
    }
    else if (!done)
    {
        foreach (QString link, wp.linksList())
        {
            QUrl url = host;
            url.setPath(link);
            previous[link] = reply->url().path();
            manager->get(QNetworkRequest(url));
        }
    }
    reply->deleteLater();
}

void WikiCrawler::found()
{
    QString page = to;
    qDebug() << page;
    while (page != from)
    {
        page = previous.value(page);
        qDebug() << page;
    }
}
