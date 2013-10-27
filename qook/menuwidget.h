#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QStackedWidget>
#include <QDate>



class MenuWidget : public QStackedWidget
{
Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = 0);

signals:

private slots:
    void loadPlanning(QDate from, QDate to);
    void unloadPlanning();
};

#endif // MENUWIDGET_H
