#ifndef YOSHIMODEL_H
#define YOSHIMODEL_H

#include <QAbstractTableModel>
#include <QNetworkAccessManager>
#include <QModelIndex>

class QNetworkReply;

class YoshiModel  : public QAbstractTableModel
{
    Q_OBJECT
public:
    YoshiModel(QObject * parent = 0);

    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

    QString search () const {return search_;}

public slots:
    void setSearch(const QString &search);

private slots:
    void requestFinished (QNetworkReply *reply);

private:
    QString search_;
    QVariantMap searchResult;
    QNetworkAccessManager network;
};

QString humanReadableSize(qint64 intSize);

#endif // YOSHIMODEL_H
