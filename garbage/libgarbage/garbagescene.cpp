#include "garbagescene.h"

#include "entryitem.h"
#include <QPropertyAnimation>
#include <QPointF>

GarbageScene::GarbageScene(QObject *parent) :
    QGraphicsScene(parent), matchesIndex(0)
{
    setSceneRect(0, 0, 1160, 660);
    currentPhoto = new PhotoItem;
    this->addItem(currentPhoto);
    currentPhoto->setPos(10, 10);
}

void GarbageScene::entry(const QPixmap &photo)
{
    currentPhoto->setPhoto(photo);
}

void GarbageScene::match(const QPixmap &photo, const QString &name, const QString passwd)
{
    int x = matchesIndex % 5;
    int y = matchesIndex / 5;
    matchesIndex++;

    EntryItem *entryItem = new EntryItem(photo, name, passwd, this);
    this->addItem(entryItem);
    entryItem->setPos(10,10);
    QPropertyAnimation *posAnim = new QPropertyAnimation(entryItem, "pos");
    posAnim->setDuration(2000);
    posAnim->setEndValue(QPointF(510 + 130*x, 10 + 170*y));
    posAnim->setEasingCurve(QEasingCurve::OutCubic);
    posAnim->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *scaleAnim = new QPropertyAnimation(entryItem, "scale");
    scaleAnim->setDuration(2000);
    scaleAnim->setEndValue(0.25);
    scaleAnim->setEasingCurve(QEasingCurve::OutCubic);
    scaleAnim->start(QAbstractAnimation::DeleteWhenStopped);

    connect(posAnim, SIGNAL(finished()),
            entryItem, SLOT(startText()));

}
