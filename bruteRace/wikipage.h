#ifndef WIKIPAGE_H
#define WIKIPAGE_H

#include <QString>
#include <QStringList>
#include <QUrl>

const QStringList toExclude = QStringList() << "Wikipedia" << "Portal" << "Special" << "Images" << "Main_Page" << "Talk";


class WikiPage
{;
public:
    WikiPage(QString content);
    QStringList linksList();
    QString canonicalUrl();

private:
    QString _content;
    QString _url;

};

#endif // WIKIPAGE_H
