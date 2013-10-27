#ifndef GARBAGESCENE_H
#define GARBAGESCENE_H

#include <QGraphicsScene>
#include "photoitem.h"

class GarbageScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GarbageScene(QObject *parent = 0);

public slots:
    void entry(const QPixmap &photo);
    void match(const QPixmap &photo, const QString &name, const QString passwd);

private:
    PhotoItem *currentPhoto;
    int matchesIndex;
};

#endif // GARBAGESCENE_H
