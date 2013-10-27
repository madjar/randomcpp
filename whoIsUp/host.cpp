#include "host.h"

Host::Host(QString name, QString label, QObject *parent) : QObject(parent), _label(label), _address(name)
{
    QHostInfo::lookupHost(name, this, SLOT(setAddress(QHostInfo)));
}

void Host::addService(Service *service)
{
    _services[service->name()] = service;
    service->setParent(this);
}

void Host::setAddress (const QHostInfo &hostInfo)
{
    if (!hostInfo.addresses().isEmpty())
    {
        _address = hostInfo.addresses().first();
        foreach (Service *s, servicesList())
            s->update();
    }
}

void Host::generateServicesList()
{
    _servicesList = _services.values();
}

