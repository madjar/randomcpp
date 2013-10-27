#ifndef RECIPESMODEL_H
#define RECIPESMODEL_H

#include <QSqlTableModel>
#include <QMimeData>
#include <QStringList>

class RecipesModel : public QSqlTableModel
{
    Q_OBJECT
public:
    RecipesModel(QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
};

#endif // RECIPESMODEL_H
