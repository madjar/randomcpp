#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

class NetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    static NetworkAccessManager *getInstance();

private:
    explicit NetworkAccessManager(QObject *parent = 0);
    static NetworkAccessManager* instance;
};

#endif // NETWORKACCESSMANAGER_H
