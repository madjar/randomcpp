#include "servicestabwidget.h"

#include <QPushButton>
#include <QFileDialog>
#include <QFileInfo>

#include "serviceswidget.h"
#include <QtDebug>

ServicesTabWidget::ServicesTabWidget(QWidget *parent)
        : QTabWidget(parent)
{
    QPushButton *button = new QPushButton();
    button->setText(tr("&Open"));
    connect(button, SIGNAL(clicked()),
            this, SLOT(open()));
    this->setCornerWidget(button, Qt::TopRightCorner);
    this->resize(sizeHint());
}

void ServicesTabWidget::addServicesWidget(QString fileName)
{
    this->addTab(new ServicesWidget(fileName),QFileInfo(fileName).fileName());
    this->resize(sizeHint());
}

void ServicesTabWidget::open()
{
    addServicesWidget(QFileDialog::getOpenFileName(this,
                                                   tr("Open a file")
                                                   , "",
                                                   tr("XML files (*.xml)")
                                                   )
                      );
    this->resize(sizeHint());
}
