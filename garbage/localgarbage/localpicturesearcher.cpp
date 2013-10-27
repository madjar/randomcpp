#include "localpicturesearcher.h"

#include <QApplication>

LocalPictureSearcher::LocalPictureSearcher(const QString &dirname, QObject *parent) :
    QObject(parent)
{
    QStringList filters;
    filters << "*.png" << "*.jpg";
    dir.setNameFilters(filters);
    dir.cd(dirname);

    QTimer *timer = new QTimer(this);
    connect (timer, SIGNAL(timeout()),
             SLOT(findPhotos()));
    timer->setInterval(0);
    timer->setSingleShot(true);
    timer->start();
}

void LocalPictureSearcher::findPhotos()
{
    foreach(QFileInfo photoInfo, dir.entryInfoList(QDir::Files))
    {
        qApp->processEvents();
        QPixmap photo(photoInfo.absoluteFilePath());
        qApp->processEvents();
        emit photoFound(photo);
        qApp->processEvents();
        if (qrand() % 2 == 0)
            emit matchFound(photo, photoInfo.fileName(), "tagada");
    }
}
