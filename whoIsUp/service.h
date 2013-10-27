#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDomElement>

#include "porttester.h"

#define DEFAULT_TIME_REFRESH 3000

class Host;

class Service : public QObject
{
    Q_OBJECT
public:
    Service(QString name,PortTester *portTester,Host *host,int timeRefresh = DEFAULT_TIME_REFRESH);

    inline QString name() const { return _name;}
    bool available() const;
    QVariant data(int role);

    static Service *serviceFromHE(Host* h,QDomElement e);

public slots:
    void update();
    void emitUpdated();

signals:
    void updated(Host*, Service*);

private:
    QString _name;
    QTimer timer;
    PortTester *portTester;
    Host* host;
    int timeRefresh;

    static PortTester* portTesterFromHE(Host *h, QDomElement e);
};

#endif // SERVICE_H
