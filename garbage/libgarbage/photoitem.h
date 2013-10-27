#ifndef PHOTOITEM_H
#define PHOTOITEM_H

#include <QGraphicsPixmapItem>

class PhotoItem : public QGraphicsPixmapItem
{
public:
    explicit PhotoItem();
    void setPhoto(const QPixmap &photo);
};

#endif // PHOTOITEM_H
