#include "menuwidget.h"
#include "planningwidget.h"
#include "daterangeselectorwidget.h"

#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QtDebug>

MenuWidget::MenuWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    DateRangeSelectorWidget *dateSelector = new DateRangeSelectorWidget(this);

    this->addWidget(dateSelector);

    connect(dateSelector, SIGNAL(planningRequested(QDate,QDate)),
            this, SLOT(loadPlanning(QDate,QDate)));
}

void MenuWidget::loadPlanning(QDate from, QDate to)
{
    PlanningWidget *planningwidget = new PlanningWidget(from, to, this);;
    this->addWidget(planningwidget);
    this->setCurrentIndex(1);
    connect(planningwidget, SIGNAL(close()),
            this, SLOT(unloadPlanning()));
}

void MenuWidget::unloadPlanning()
{
    this->widget(1)->deleteLater();
}
