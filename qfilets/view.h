#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QGraphicsScene *scene);

protected:
    void mousePressEvent ( QMouseEvent * e );
    void wheelEvent ( QWheelEvent * e );
};

#endif // VIEW_H
