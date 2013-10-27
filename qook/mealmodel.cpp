#include "mealmodel.h"

#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QtDebug>

MealModel::MealModel(int meal, QObject *parent) : QSqlRelationalTableModel(parent), meal(meal)
{
    setTable("menu");
    setRelation(2, QSqlRelation("recipes", "id", "name"));
    setFilter(QString("meal='%1'").arg(meal));
    sort(2, Qt::AscendingOrder);
    select();

    setSupportedDragActions(Qt::MoveAction);
}

Qt::DropActions MealModel::supportedDropActions () const
{
    return Qt::CopyAction| Qt::MoveAction;
}

Qt::ItemFlags MealModel::flags(const QModelIndex &index) const
 {
     if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
     else
         return QSqlTableModel::flags(index) | Qt::ItemIsDropEnabled ;
 }

QStringList MealModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.qook.recipe" << "application/vnd.qook.menuitem";
    return types;
}

QMimeData *MealModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            stream << data(index.sibling(index.row(), 0), Qt::DisplayRole).toInt();
        }
    }

    mimeData->setData("application/vnd.qook.menuitem", encodedData);

    return mimeData;
}

bool MealModel::dropMimeData ( const QMimeData * data, Qt::DropAction action, int /*row*/, int /*column*/, const QModelIndex & /*parent*/ )
{
    if (action == Qt::IgnoreAction)
        return true;
    if (data->hasFormat("application/vnd.qook.menuitem"))
    {
        QByteArray encodedData = data->data("application/vnd.qook.menuitem");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        while (!stream.atEnd()) {
            int id;
            stream >> id;
            QSqlQuery query;
            query.prepare("update menu set meal = :meal where id = :id");
            query.bindValue(":meal", meal);
            query.bindValue(":id", id);
            query.exec();
            select();
            //TODO use the model, luke
        }

        return true;
    }
    else if (data->hasFormat("application/vnd.qook.recipe"))
    {
        QByteArray encodedData = data->data("application/vnd.qook.recipe");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        while (!stream.atEnd()) {
            int recipe;
            stream >> recipe;
            QSqlRecord record;
            QSqlField f0("id", QVariant::Int);
            QSqlField f1("meal", QVariant::Int);
            QSqlField f2("recipe", QVariant::Int);
            f0.setValue(QVariant(QVariant::Int));
            f1.setValue(meal);
            f2.setValue(recipe);
            record.append(f0);
            record.append(f1);
            record.append(f2);
            insertRecord(-1, record);
        }
        return true;
    }
    return false;
}
