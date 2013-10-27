#include "fixedservicesmodel.h"
#include "host.h"
#include "service.h"

FixedServicesModel::FixedServicesModel(ConfigurationReader *configurationReader, QObject *parent)
        : ServicesModel(configurationReader, parent)
{
    foreach(Host *host, configurationReader->hosts())
        foreach (QString service, host->services().keys())
            if (!services.contains(service))
                services << service;

    services.sort();
}

int FixedServicesModel::columnCount(const QModelIndex &/*parent*/) const
{
    return services.size();
}

QVariant FixedServicesModel::data ( const QModelIndex & index, int role ) const
{
    if (role == Qt::DisplayRole)
        return QVariant();

    Service *service = configurationReader->hosts().at(index.row())->services().value(services.at(index.column()));

    if (!service) //Pas de service
    {
        if (role == Qt::BackgroundRole)
            return Qt::transparent;

        return QVariant();
    }

    return service->data(role);
}

QVariant FixedServicesModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if (orientation == Qt::Vertical)
        return ServicesModel::headerData(section, orientation, role);

    if (role == Qt::DisplayRole)
        return services.at(section);

    return QVariant();
}

void FixedServicesModel::servicesStatusChanged(Host *host, Service *service)
{
    QModelIndex modelIndex = index(configurationReader->hosts().indexOf(host), services.indexOf(service->name()));
    emit dataChanged(modelIndex, modelIndex);
}
