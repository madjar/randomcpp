#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QRectF>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();

    int number () const { return number_; }
    void fitInto(QRectF newRect);
    bool won() const {return won_;}

public slots:
    void setNumber (int number) {number_ = number;}
    void newGame ();

signals:
    void win();

protected:
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );

private:
    int number_;
    bool won_;

    void checkWin();
};

#endif // SCENE_H
