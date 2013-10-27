#include "serviceswidget.h"
#include "ui_serviceswidget.h"

ServicesWidget::ServicesWidget(QString fileName, QWidget *parent) :
    QWidget(parent),
    fileName(fileName),
    configurationReader(fileName),
    fixedServicesModel(&configurationReader),
    floatingServicesModel(&configurationReader),
    m_ui(new Ui::ServicesWidget)
{
    m_ui->setupUi(this);
    m_ui->checkFloat->click();
    m_ui->servicesTable->resizeRowsToContents();
}

ServicesWidget::~ServicesWidget()
{
    delete m_ui;
}

void ServicesWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ServicesWidget::on_checkFloat_toggled(bool checked)
{
    if(checked)
    {
        m_ui->servicesTable->setModel(&floatingServicesModel);
        m_ui->servicesTable->reset();
        m_ui->servicesTable->resizeColumnsToContents();
    }
}

void ServicesWidget::on_checkFixed_toggled(bool checked)
{
    if(checked)
    {
        m_ui->servicesTable->setModel(&fixedServicesModel);
        m_ui->servicesTable->reset();
        m_ui->servicesTable->resizeColumnsToContents();
    }
}
