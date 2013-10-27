#include "view.h"

#include <QMouseEvent>
#include <QRect>
#include "scene.h"

View::View(QGraphicsScene *scene) : QGraphicsView(scene)
{
    setRenderHint(QPainter::Antialiasing, true);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::mousePressEvent ( QMouseEvent * e )
{
    if (e->button() == Qt::MidButton)
    {
        QRectF newRect = rect();
        newRect.moveCenter(sceneRect().center());
        setSceneRect(newRect);
        qobject_cast<Scene *>(scene())->fitInto(newRect);
    }

    QGraphicsView::mousePressEvent(e);
}

void View::wheelEvent ( QWheelEvent * e )
{
    QGraphicsView::wheelEvent(e);
}
