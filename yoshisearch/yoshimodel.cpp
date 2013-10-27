#include "yoshimodel.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <qjson/parser.h>
#include <QApplication>
#include <QStyle>
#include <QVariant>
#include <QList>
#include <QMap>

#include <QtDebug>

YoshiModel::YoshiModel(QObject * parent) : QAbstractTableModel(parent)
{
    connect(&network, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(requestFinished(QNetworkReply*)));
}

int YoshiModel::rowCount ( const QModelIndex & parent ) const
{
    if (!parent.isValid())
        return searchResult["results"].toList().size();
    else
        return 0;
}

int YoshiModel::columnCount ( const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant YoshiModel::data ( const QModelIndex & index, int role ) const
{
    if (role == Qt::DecorationRole && index.column() == 0)
    {
        if (searchResult["results"].toList().at(index.row()).toMap()["Folder"].toInt() == 1)
            return QApplication::style()->standardIcon(QStyle::SP_DirIcon);
        else
            return QVariant();
    }


    if (role == Qt::TextAlignmentRole && index.column() == 1)
        return Qt::AlignRight;

    if (role != Qt::DisplayRole && role != Qt::ToolTipRole)
        return QVariant();

    switch (index.column())
    {
    case 0:
        return searchResult["results"].toList().at(index.row()).toMap()["Name"];
    case 1:
        return humanReadableSize(searchResult["results"].toList().at(index.row()).toMap()["Size"].toInt());
    case 2:
        return searchResult["results"].toList().at(index.row()).toMap()["URL"];
    }

    return QVariant();
}

QModelIndex YoshiModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if (!parent.isValid())
        return createIndex(row, column);
    else
        return QModelIndex();
}

QModelIndex YoshiModel::parent ( const QModelIndex & /*index*/ ) const
{
    return QModelIndex();
}

QVariant YoshiModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    switch (section)
    {
    case 0:
        return tr("Name");
    case 1:
        return tr("Size");
    case 2:
        return tr("Url");
    }
    return QVariant();
}

void YoshiModel::setSearch(const QString &search)
{
    searchResult.clear();
    reset();
    qDebug() << "searching" << search;
    QString url = "http://yoshi.rez-gif.supelec.fr/index.php?a=search&recherche=%1&json=1";
    search_ = search;
    network.get(QNetworkRequest(url.arg(search)));

}

void YoshiModel::requestFinished (QNetworkReply *reply)
{
    qDebug() << "answer recieved";
    QJson::Parser parser;
    bool ok;

    searchResult = parser.parse(reply, &ok).toMap();
    reply->deleteLater();
    if (!ok)
        qDebug() << "not ok";
    reset();
}

QString humanReadableSize(qint64 intSize)
{
    static const QStringList prefix= QStringList() << "" << "K" << "M" << "G" << "T" << "P" << "E" << "Z" << "Y";
    double size=intSize;
    int exponent=0;
    while (size>1024)
    {
        size /= 1024;
        exponent +=1;
    }
    if (exponent > 8)
        return "Forty two";

    return QString::number(size, 'f', 1) + " " + prefix.at(exponent) + "o";
}
