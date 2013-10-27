#include "wikipage.h"
#include <QtDebug>


WikiPage::WikiPage(QString content)
{
    _content = content;
}


QStringList WikiPage::linksList()
{
    QRegExp pattern("<a href=\\\"/wiki/([a-zA-Z0-9-_:]*)\\\" title=\\\".*\\\">.*</a>");
    pattern.setMinimal(true);
    int pos = 0;
    int matchLength = 0;
    QString match;
    QStringList oneMatch, result;
    while((pos = pattern.indexIn(_content,pos+matchLength)) > -1)
    {
        oneMatch = pattern.capturedTexts();
        match = oneMatch.at(1);
//        qDebug() << "Match : " << match << " at position : " << pos;
        matchLength = match.size();
        bool isCorrect = true;
        QStringListIterator it(toExclude);
        while(isCorrect && it.hasNext())
        {
            isCorrect = !match.startsWith(it.next());
        }
        if(isCorrect)
        {
            result += QString("/wiki/") + oneMatch.at(1);
        }
    }
//    qDebug() << result.size() << " liens trouves ";
    return result;
}

QString WikiPage::canonicalUrl()
{
        QRegExp pattern("<link rel=\\\"canonical\\\" href=\\\"(.*)\\\" />");
        pattern.setMinimal(true);
        if(pattern.indexIn(_content) > -1){
            return pattern.capturedTexts().at(1);
        }
        else return "";
}
