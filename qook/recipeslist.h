#ifndef RECIPESLIST_H
#define RECIPESLIST_H

#include <QListView>
#include "recipesmodel.h"

class RecipesList : public QListView
{
    Q_OBJECT
public:
    RecipesList(QWidget *parent = 0);

private slots:
    void itemDoubleClicked (const QModelIndex &index);

private:
    RecipesModel *model;

    //TODO c'est sale, virer ça dès que ce sera plus besoin
    friend class QookWindow;
};

#endif // RECIPESLIST_H
