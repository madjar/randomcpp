#ifndef CONFIGURATIONREADER_H
#define CONFIGURATIONREADER_H

#include <QFile>
#include <QList>

#include "host.h"
#include "service.h"

class ConfigurationReader : public QObject
{
    Q_OBJECT
public:
    ConfigurationReader(QObject *parent = 0);
    ConfigurationReader(QString fileName, QObject *parent = 0);
    void parse(QString fileName);

    QList <Host*> hosts() const { return hostsList; }

signals:
    void updated(Host*, Service*);

private:
    QList<Host*> hostsList;
};

#endif // CONFIGURATIONREADER_H
