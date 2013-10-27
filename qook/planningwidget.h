#ifndef PLANNINGWIDGET_H
#define PLANNINGWIDGET_H

#include <QWidget>
#include <QDate>

class PlanningWidget : public QWidget
{
    Q_OBJECT
public:
    PlanningWidget(QWidget *parent = 0);
    PlanningWidget(QDate from, QDate to, QWidget *parent = 0);

    QDate getFrom() const {return from;}
    void setFrom( const QDate & from ) {this->from = from;}
    QDate getTo() const {return to;}
    void setTo( const QDate & to ) {this->to = to;}

signals:
    void close();

private:
    void init();
    QDate from;
    QDate to;
};

#endif // PLANNINGWIDGET_H
