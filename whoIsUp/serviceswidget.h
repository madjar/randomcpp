#ifndef SERVICESWIDGET_H
#define SERVICESWIDGET_H

#include <QtGui/QWidget>
#include "configurationreader.h"
#include "fixedservicesmodel.h"
#include "floatingservicesmodel.h"

namespace Ui {
    class ServicesWidget;
}

class ServicesWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(ServicesWidget)
public:
    explicit ServicesWidget(QString fileName, QWidget *parent = 0);
    virtual ~ServicesWidget();

protected:
    virtual void changeEvent(QEvent *e);

private:
    QString fileName;
    ConfigurationReader configurationReader;
    FixedServicesModel fixedServicesModel;
    FloatingServicesModel floatingServicesModel;
    Ui::ServicesWidget *m_ui;

private slots:
    void on_checkFixed_toggled(bool checked);
    void on_checkFloat_toggled(bool checked);
};

#endif // SERVICESWIDGET_H
