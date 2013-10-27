#include "entry.h"

#include "networkaccessmanager.h"
#include <QTextStream>
#include <QRegExp>
#include <QTextDocument>

Entry::Entry(int id, QObject *parent) :
    QObject(parent)
{
    QString entryUrl = "http://www.rez-gif.supelec.fr/trombi/show.php?id=%0";
    entryUrl = entryUrl.arg(id);
    reply = NetworkAccessManager::getInstance()->get(QNetworkRequest(QUrl(entryUrl)));
    connect (reply, SIGNAL(finished()),
             SLOT(pageDownloadFinished()));
}

QString Entry::getLogin () const
{
    QString first, last;
    if (email.isEmpty())
    {
        first = remove_accents(firstName);
        last = remove_accents(lastName);
    }
    else
    {
        QString s = email.split("@")[0];
        QStringList sl = s.split(".");
        first = sl[0];
        last = sl[0];
    }
    return QString("%1_%2").arg(last.left(8), first.left(3)).toLower();
}

QString Entry::getPasswd () const
{
    if (!birth.isEmpty())
    {
        QStringList date = birth.split('/');
        return date.join("");
    }
    return QString();
}

void Entry::pageDownloadFinished()
{
    QString page = QTextStream(reply).readAll();
    reply->deleteLater();

    if (page.right(9) != "</html>\n\n")
    {
        valid = false;
        emit ready();
        return;
    }

    valid = true;

    QRegExp rx("<!-- Nom, pr&eacute;nom, surnom &eacute;ventuel -->\n<h1>\n(\\S*) ([^\\( ]*).*</h1>"); //TODO regex improvable, but who cares
    rx.setMinimal(true);
    if (rx.indexIn(page) != -1)
    {
        firstName = unescape(rx.cap(1));
        lastName = unescape(rx.cap(2));
    }
    rx.setPattern("  <td class=\"label\">Date de naissance&nbsp;:</td>\n  <td>(.*)</td>");
    if (rx.indexIn(page) != -1)
        birth = unescape(rx.cap(1));

    rx.setPattern("<ul class='noindent'>\n<li><a href=\"mailto:(\\S*@supelec\\.fr)\">");
    if (rx.indexIn(page) != -1)
        email = unescape(rx.cap(1));

    QString photo;
    rx.setPattern("<!-- Photo -->\n<a href=\"(http://www.rez-gif.supelec.fr/trombi/photos/.*.jpg)\">");
    if (rx.indexIn(page) != -1)
        photo = rx.cap(1);

    if (!photo.isEmpty())
    {
        reply = NetworkAccessManager::getInstance()->get(QNetworkRequest(QUrl(photo)));
        connect (reply, SIGNAL(finished()),
                 SLOT(photoDownloadFinished()));
    }
    else
    {
        emit ready();
    }
}

void Entry::photoDownloadFinished()
{
    pixmap.loadFromData(reply->readAll());
    reply->deleteLater();
    emit ready();
}

QString Entry::unescape(const QString &s) const
{
    QTextDocument textDocument;
    textDocument.setHtml(s);
    return textDocument.toPlainText();
}

QString Entry::remove_accents(const QString &s) const
{
    QString norm = s.normalized(QString::NormalizationForm_KD);
    int i = 0;
    while (i< norm.size())
    {
        if (norm[i].category() == QChar::Letter_Modifier)
            norm.remove(i, 1);
        else
            ++i;
    }

    return norm;
}
