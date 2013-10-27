#include "service.h"
#include "oneporttester.h"
#include "andporttester.h"
#include "orporttester.h"

#include <QVariant>
#include <QtDebug>

Service::Service(QString name,PortTester *portTester,Host *host,int timeRefresh)
        : QObject((QObject*) host),_name(name),portTester(portTester),host(host),timeRefresh(timeRefresh)
        //Cast toi, pauv' con
{
    portTester->setParent(this);
    connect(portTester,SIGNAL(updated()),this,SLOT(emitUpdated()));
    if(timeRefresh == 0)
    {
        timeRefresh = DEFAULT_TIME_REFRESH;
    }
    timer.setInterval(timeRefresh);
    connect(&timer, SIGNAL(timeout()),
            this, SLOT(update()));
    connect(this, SIGNAL(updated(Host*, Service*)),
            &timer, SLOT(start()));
    timer.start();
}

bool Service::available() const
{
    return portTester->available();
}

void Service::update()
{
    portTester->update();
}

Service *Service::serviceFromHE(Host* h,QDomElement e)
{

    Service * service = new Service(e.attribute("name"),
                                    portTesterFromHE(h, e.firstChildElement()),
                                    h,
                                    e.attribute("timeRefresh").toInt());
    return service;
}

void Service::emitUpdated()
{
    emit updated(this->host, this);
}

PortTester* Service::portTesterFromHE(Host *h, QDomElement e)
{
    QString tagName = e.tagName();
    if(tagName == "port")
    {
        return new OnePortTester(h, e.attribute("number").toULong());
    }

    PortTesterSet *portTester;
    if(tagName == "or-port")
    {
        portTester = new OrPortTester(h);
    }
    else if (tagName == "and-port")
    {
        portTester = new AndPortTester(h);
    } else {
        qDebug() << "Boum !";
    }
    QDomElement child = e.firstChildElement();
    while (!child.isNull())
    {
        portTester->addPortTester(portTesterFromHE(h, child));
        child = child.nextSiblingElement();
    }
    return portTester;
}

QVariant Service::data(int role)
{
    if (role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::StatusTipRole)
        return name();

    if (role == Qt::BackgroundRole)
        return available() ? Qt::green : Qt::red;

    return QVariant();
}
