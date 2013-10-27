#ifndef DATERANGESELECTORWIDGET_H
#define DATERANGESELECTORWIDGET_H

#include "ui_daterangeselectorwidget.h"

#include <QWidget>
#include <QDate>

namespace Ui {
    class DateRangeSelectorWidget;
}

class DateRangeSelectorWidget : public QWidget {
    Q_OBJECT
public:
    DateRangeSelectorWidget(QWidget *parent = 0);
    ~DateRangeSelectorWidget();
    
    QDate from() const {return ui->from->selectedDate();}
    QDate to() const {return ui->to->selectedDate();}

signals:
    void planningRequested(QDate, QDate);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DateRangeSelectorWidget *ui;

private slots:
    void on_to_selectionChanged();
    void on_from_selectionChanged();
    void on_buttonBox_accepted();
};

#endif // DATERANGESELECTORWIDGET_H
