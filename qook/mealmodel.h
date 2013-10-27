#ifndef MEALMODEL_H
#define MEALMODEL_H

#include <QSqlRelationalTableModel>
#include <QMimeData>
#include <QStringList>

class MealModel : public QSqlRelationalTableModel
{
public:
    MealModel(int meal, QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    Qt::DropActions supportedDropActions () const;
    bool dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent );

private:
    int meal;
};

#endif // MEALMODEL_H
