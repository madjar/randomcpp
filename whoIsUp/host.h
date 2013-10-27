#ifndef HOST_H
#define HOST_H

#include <QHostAddress>
#include <QHash>
#include <QString>
#include <QHostInfo>

#include "service.h"

class Host : public QObject
{
    Q_OBJECT
public:
    Host(QString name, QString label, QObject *parent = 0);

    inline QString label() const { return _label; }
    inline QHostAddress address() const { return _address; }
    inline QMap<QString, Service*> services() const {return _services;}
    inline QList<Service*> servicesList() const {return _servicesList;}

    void addService (Service *service);
    void generateServicesList();

private slots:
    void setAddress (const QHostInfo &hostInfo);

private:
    QString _label;
    QHostAddress _address;
    QMap<QString, Service*> _services;
    QList<Service*> _servicesList;
};

#endif // HOST_H
