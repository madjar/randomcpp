#ifndef GARBAGE_H
#define GARBAGE_H

#include "libgarbage_global.h"

#include <QWidget>
#include <QGraphicsView>
#include <QProgressBar>
#include <QPixmap>
#include "garbagescene.h"

class LIBGARBAGESHARED_EXPORT Garbage : public QWidget
{
    Q_OBJECT
public:
    Garbage(QWidget *parent = 0);

public slots:
    void setRange(int min, int max);
    void setValue(int progress);

    void entry(const QPixmap &photo);
    void match(const QPixmap &photo, const QString &name, const QString &passwd);

private:
    QGraphicsView *view;
    QProgressBar *progressBar;
    GarbageScene *scene;
};

#endif // GARBAGE_H
