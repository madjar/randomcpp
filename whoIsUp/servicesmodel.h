#ifndef SERVICESMODEL_H
#define SERVICESMODEL_H

#include <QAbstractTableModel>
#include "configurationreader.h"

class ServicesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ServicesModel(ConfigurationReader *configurationReader, QObject * parent = 0);
    virtual ~ServicesModel();

    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    Qt::ItemFlags flags ( const QModelIndex & index ) const;

protected slots:
    virtual void servicesStatusChanged(Host *host, Service *service) = 0;

protected:
    ConfigurationReader *configurationReader;
};

#endif // SERVICESMODEL_H
