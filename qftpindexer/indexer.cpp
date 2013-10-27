#include "indexer.h"

#include <QtDebug>
#include <iostream>
#include <QDateTime>


Indexer::Indexer(QUrl url, QObject *parent) : QObject(parent), url(url)
{
    connect (&ftp, SIGNAL(done(bool)),
             this, SLOT(ftpDone(bool)));
    connect (&ftp, SIGNAL(listInfo(const QUrlInfo &)),
             this, SLOT(ftpListInfo(const QUrlInfo &)));
}

void Indexer::start()
{
    ftp.connectToHost(url.host(), url.port(21));
    ftp.login("anonymous","");

    pendingDirs.append("/");
    processNextDirectory();
}

void Indexer::processNextDirectory()
{
    if (!pendingDirs.isEmpty()) {
        currentDir = pendingDirs.takeFirst();

        ftp.cd(currentDir);
        ftp.list();
    } else {
        emit done();
    }
}

void Indexer::ftpListInfo(const QUrlInfo &urlInfo)
{
    if (urlInfo.lastModified() > QDateTime::currentDateTime().addDays(-7))
    {
        std::cout << qPrintable(url.toString() + sanitize(currentDir + "/" + urlInfo.name())) << std::endl;
    }

    if (urlInfo.isDir() && !urlInfo.isSymLink())
    {
        pendingDirs.append(currentDir + "/" + urlInfo.name());
    }
}

void Indexer::ftpDone(bool error)
{
    if (error)
    {
        std::cerr<<qPrintable(ftp.errorString()) << std::endl;
    }
    processNextDirectory();
}

QString Indexer::sanitize(const QString &string)
{
    // Nettoie les chaînes obtenues par listInfo
    // Problème vient du fait que QFtp récupère les noms de fichier en utf8 et les interprète comme de l'utf16.
    if (string.toLatin1()!=string.toUtf8()) //Basiquement, ça veut dire "si on a un accent"
    {
        const ushort *in = string.utf16();
        char *out = new char[string.length()];
        char *ret = out;
        while (*in)
        {
            if ((*in & 0xC0) == 0xC0 && (*(in+1) & 0xC0) != 0x80)
            {
                // This ain't not utf8, ma'am, this is fracking latin9
                // See http://en.wikipedia.org/wiki/Utf8#Description for details
                return string;
            }
            if(*in>=256)
                qWarning()<<tr("\"%1\" is not a utf8 string, behavior is not guaranteed.").arg(string);
            *out++=(char)*in++;
        }
        QString sanitized = QString::fromUtf8(ret,string.length());
        delete[] ret;
        return sanitized;
    }
    return string;
}
