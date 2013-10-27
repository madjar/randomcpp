#include "photoitem.h"

PhotoItem::PhotoItem()
{
}

void PhotoItem::setPhoto(const QPixmap &photo)
{
    QPixmap scaled = photo.scaled(480, 640, Qt::KeepAspectRatio);
    setPixmap(scaled);
    setOffset( (480 - scaled.width()) / 2, (640 - scaled.height()) /2) ;
}
