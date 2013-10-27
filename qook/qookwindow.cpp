#include "qookwindow.h"
#include "ui_qookwindow.h"
#include "mealmodel.h"

#include <QListView>
#include <QSettings>
#include "recipesmodel.h"
#include "recipeeditordialog.h"

QookWindow::QookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QookWindow)
{
    ui->setupUi(this);
}

QookWindow::~QookWindow()
{
    delete ui;
}

void QookWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QookWindow::on_action_Change_Database_triggered()
{
    QSettings settings;
    settings.setValue("db/keepInfo", false);
    statusBar()->showMessage(tr("The database will be change the next time you restart Qook."), 2000);
}

void QookWindow::on_action_Add_Recipe_triggered()
{
    // TODO Temporaire, le temps de refaire l'interface
    RecipesModel *model = ui->listView->model;
    int row = model->rowCount();
    model->insertRow(row);
    RecipeEditorDialog *recipeEditor = new RecipeEditorDialog(model, row, this);
    connect(recipeEditor, SIGNAL(finished(int)),
            recipeEditor, SLOT(deleteLater()));
    recipeEditor->show();
    recipeEditor->raise();
    recipeEditor->activateWindow();
}
