#ifndef SERVICESTABWIDGET_H
#define SERVICESTABWIDGET_H

#include <QTabWidget>

class ServicesTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    ServicesTabWidget(QWidget *parent = 0);

    void addServicesWidget(QString fileName);

public slots:
    void open();
};

#endif // SERVICESTABWIDGET_H
