#include "floatingservicesmodel.h"

FloatingServicesModel::FloatingServicesModel(ConfigurationReader* configurationReader,QObject *parent)
        :ServicesModel(configurationReader, parent),_columnCount(0)
{
    initColumnCount();
}
void FloatingServicesModel::initColumnCount()
{
       foreach(Host *h, configurationReader->hosts())
        {
            _columnCount = qMax(_columnCount,h->services().size());
        }
}
int FloatingServicesModel::columnCount( const QModelIndex & /*parent*/) const
{
    return _columnCount;
}

QVariant FloatingServicesModel::data ( const QModelIndex & index, int role) const
{
    Host* host = configurationReader->hosts().at(index.row());
    if(index.column() >= host->services().size())
    {
        if (role == Qt::BackgroundRole)
            return Qt::transparent;
        else
            return QVariant();
    }
    else return host->servicesList().at(index.column())->data(role);
}

void FloatingServicesModel::servicesStatusChanged(Host *host, Service *service)
{
    QModelIndex modelIndex = index(configurationReader->hosts().indexOf(host), host->servicesList().indexOf(service));
    emit dataChanged(modelIndex, modelIndex);
}
