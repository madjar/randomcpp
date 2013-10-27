#include "servicesmodel.h"

ServicesModel::ServicesModel(ConfigurationReader *configurationReader, QObject * parent)
        : QAbstractTableModel(parent), configurationReader(configurationReader)
{
    connect(configurationReader, SIGNAL(updated(Host*,Service*)),
            this, SLOT(servicesStatusChanged(Host*,Service*)));
}

ServicesModel::~ServicesModel()
{
}

int ServicesModel::rowCount(const QModelIndex &/*parent*/) const
{
    return configurationReader->hosts().size();
}

QVariant ServicesModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
        return QVariant(); // Don't care about columns

    if (role == Qt::DisplayRole)
    {
        return configurationReader->hosts().at(section)->label();
    }

    return QVariant();
}

Qt::ItemFlags ServicesModel::flags ( const QModelIndex & /*index*/ ) const
{
    return Qt::ItemIsEnabled;
}
