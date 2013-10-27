#include "configurationreader.h"


#include <QDomDocument>
#include <QIODevice>
#include <QString>
#include <QDomElement>
#include <QHash>

#include <QtDebug>

ConfigurationReader::ConfigurationReader(QObject *parent) : QObject(parent)
{
}

ConfigurationReader::ConfigurationReader(QString fileName, QObject *parent) : QObject(parent)
{
    parse(fileName);
}

void ConfigurationReader::parse(QString fileName)
{
    QFile file(fileName);
    // Read the file
    QDomDocument doc;
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file);
    file.close();

    // Parse the DOM
    QDomElement root = doc.documentElement();
    QHash<QString, QDomElement> servicesHash;

    // Services definitions
    QDomElement services = root.firstChildElement("services");
    while (!services.isNull())
    {
        QDomElement service = services.firstChildElement("service");
        while (!service.isNull())
        {
            servicesHash[service.attribute("name")] = service;
            service = service.nextSiblingElement("service");
        }
        services = services.nextSiblingElement("services");
    }

    // Hosts list
    QDomElement hosts = root.firstChildElement("hosts");
    while (!hosts.isNull())
    {
        QDomElement host = hosts.firstChildElement("host");
        while (!host.isNull())
        {
            QString name = host.attribute("name");
            Host *h = new Host(name, host.attribute("label", name));
            // Service list for this host :
            QDomElement service = host.firstChildElement("service");
            while(!service.isNull())
            {
                QDomElement serviceDescription = servicesHash.value(service.attribute("name"));
                if (serviceDescription.isNull())
                    qDebug() << tr("%1 is not a valid service").arg(service.attribute("name"));
                else
                {
                    Service *s = Service::serviceFromHE(h,servicesHash.value(service.attribute("name")));
                    h->addService(s);
                    connect (s, SIGNAL(updated(Host*, Service*)),
                             this, SIGNAL(updated(Host*, Service*)));
                }
                service = service.nextSiblingElement("service");
            }
            h->generateServicesList();
            hostsList.append(h);
            host = host.nextSiblingElement("host");
        }
        hosts = hosts.nextSiblingElement("hosts");
    }
}
