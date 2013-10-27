#ifndef FLOATINGSERVICESMODEL_H
#define FLOATINGSERVICESMODEL_H

#include "servicesmodel.h"

class FloatingServicesModel : public ServicesModel
{
    Q_OBJECT
public:
    FloatingServicesModel(ConfigurationReader* configurationReader,QObject *parent = 0);

    int columnCount( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

protected slots:
    void servicesStatusChanged(Host *host, Service *service);

private:
    void initColumnCount();
    int _columnCount;
};

#endif // FLOATINGSERVICESMODEL_H
