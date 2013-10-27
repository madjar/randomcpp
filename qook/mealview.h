#ifndef MEALVIEW_H
#define MEALVIEW_H

#include <QListView>
#include <QDropEvent>
#include "mealmodel.h"

class MealView : public QListView
{
    Q_OBJECT
public:
    MealView(int meal, QWidget *parent = 0);

protected:
    void dropEvent ( QDropEvent * event );

private:
    MealModel *model;
};

#endif // MEALVIEW_H
