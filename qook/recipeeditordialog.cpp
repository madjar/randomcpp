#include "recipeeditordialog.h"
#include "ui_recipeeditordialog.h"

#include <QDataWidgetMapper>

RecipeEditorDialog::RecipeEditorDialog(RecipesModel * model, int line,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeEditorDialog),
    model(model)
{
    ui->setupUi(this);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->nameLineEdit, model->fieldIndex("name"));
    mapper->addMapping(ui->descriptionPlainTextEdit, model->fieldIndex("description"));
    mapper->setCurrentIndex(line);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    connect(this, SIGNAL(accepted()),
            mapper, SLOT(submit()));
    connect(this, SIGNAL(rejected()),
            mapper, SLOT(revert()));
}

RecipeEditorDialog::~RecipeEditorDialog()
{
    delete ui;
}

void RecipeEditorDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
