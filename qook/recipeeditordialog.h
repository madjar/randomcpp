#ifndef RECIPEEDITORDIALOG_H
#define RECIPEEDITORDIALOG_H

#include <QDialog>
#include "recipesmodel.h"

namespace Ui {
    class RecipeEditorDialog;
}

class RecipeEditorDialog : public QDialog {
    Q_OBJECT
public:
    RecipeEditorDialog(RecipesModel * model, int line, QWidget *parent = 0);
    ~RecipeEditorDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RecipeEditorDialog *ui;

    RecipesModel * model;
};

#endif // RECIPEEDITORDIALOG_H
