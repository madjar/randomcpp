#include "garbage.h"

#include <QVBoxLayout>

Garbage::Garbage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    view = new QGraphicsView;
    scene = new GarbageScene(this);
    view->setScene(scene);
    layout->addWidget(view);

    progressBar = new QProgressBar;
    progressBar->setMaximum(0);
    layout->addWidget(progressBar);

    this->resize(sizeHint());
}

void Garbage::setRange(int min, int max)
{
    progressBar->setRange(min, max);
}

void Garbage::setValue(int progress)
{
    progressBar->setValue(progress);
}

void Garbage::entry(const QPixmap &photo)
{
    scene->entry(photo);
}

void Garbage::match(const QPixmap &photo, const QString &name, const QString &passwd)
{
    scene->match(photo, name, passwd);
}
