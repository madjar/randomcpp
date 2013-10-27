#include "daterangeselectorwidget.h"
#include "ui_daterangeselectorwidget.h"

DateRangeSelectorWidget::DateRangeSelectorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateRangeSelectorWidget)
{
    ui->setupUi(this);
    on_from_selectionChanged();
    on_to_selectionChanged();
}

DateRangeSelectorWidget::~DateRangeSelectorWidget()
{
    delete ui;
}

void DateRangeSelectorWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DateRangeSelectorWidget::on_buttonBox_accepted()
{
    emit planningRequested(ui->from->selectedDate(), ui->to->selectedDate());
}

void DateRangeSelectorWidget::on_from_selectionChanged()
{
    ui->to->setMinimumDate(ui->from->selectedDate());
}

void DateRangeSelectorWidget::on_to_selectionChanged()
{
    ui->from->setMaximumDate(ui->to->selectedDate());
}
