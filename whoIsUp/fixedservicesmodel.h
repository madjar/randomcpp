#ifndef FIXEDSERVICESMODEL_H
#define FIXEDSERVICESMODEL_H

#include <QStringList>
#include "servicesmodel.h"

class FixedServicesModel : public ServicesModel
{
    Q_OBJECT
public:
    FixedServicesModel(ConfigurationReader *configurationReader, QObject *parent = 0);

    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

protected slots:
    void servicesStatusChanged(Host *host, Service *service);

private:
    QStringList services;
};

#endif // FIXEDSERVICESMODEL_H
