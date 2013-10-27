#include "mealview.h"

MealView::MealView(int meal, QWidget *parent) : QListView(parent)
{
    model = new MealModel(meal, this);

    setModel(model);
    setModelColumn(2);

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void MealView::dropEvent ( QDropEvent * event )
{
    QListView::dropEvent(event);

    MealView *source = qobject_cast<MealView *>(event->source());
    if (source && source != this)
    {
        source->model->select();
        source->reset();
    }
}
