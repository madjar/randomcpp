#ifndef ENTRYITEM_H
#define ENTRYITEM_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include "photoitem.h"

class EntryItem : public QObject, public PhotoItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)

public:
    explicit EntryItem(const QPixmap &photo, const QString &login, const QString &passwd, QObject *parent = 0);

public slots:
    void startText();

private slots:
    void updateText();

private:
    QString login;
    QString passwd;
    QGraphicsTextItem textItem;
    QGraphicsRectItem blackRect;
    int ticks;


    static inline QTimer *timer ();
    static QTimer *_timer;
};

QTimer *EntryItem::timer()
{
    if (_timer == 0)
    {
        _timer = new QTimer;
        _timer->setInterval(100);
        _timer->setSingleShot(false);
        _timer->start();
    }
    return _timer;
}

#endif // ENTRYITEM_H
