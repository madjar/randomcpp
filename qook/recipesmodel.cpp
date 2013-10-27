#include "recipesmodel.h"

#include <QtDebug>

RecipesModel::RecipesModel(QObject *parent) : QSqlTableModel(parent)
{
    setTable("recipes");
    select();
}

Qt::ItemFlags RecipesModel::flags(const QModelIndex &index) const
 {
     if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
     else
         return QSqlTableModel::flags(index);
 }

QStringList RecipesModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.qook.recipe";
    return types;
}

QMimeData *RecipesModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            stream << data(index.sibling(index.row(), 0), Qt::DisplayRole).toInt();
        }
    }

    mimeData->setData("application/vnd.qook.recipe", encodedData);

    return mimeData;
}
