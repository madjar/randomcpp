#include "recipeslist.h"

#include <QSqlTableModel>

#include "recipeeditordialog.h"

RecipesList::RecipesList(QWidget *parent) : QListView(parent)
{
    model = new RecipesModel(this);

    setModel(model);
    setModelColumn(1);

    setDragEnabled(true);

    connect(this, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(itemDoubleClicked(QModelIndex)));
}

void RecipesList::itemDoubleClicked (const QModelIndex &index)
{
    RecipeEditorDialog *recipeEditor = new RecipeEditorDialog(model, index.row(), this);
    recipeEditor->show();
    recipeEditor->raise();
    recipeEditor->activateWindow();
}
