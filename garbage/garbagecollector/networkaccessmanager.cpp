#include "networkaccessmanager.h"

NetworkAccessManager *NetworkAccessManager::instance = 0;

NetworkAccessManager::NetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
}

NetworkAccessManager *NetworkAccessManager::getInstance()
{
    if (instance == 0)
        instance = new NetworkAccessManager;
    return instance;
}
