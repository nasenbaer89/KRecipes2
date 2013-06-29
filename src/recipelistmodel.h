#ifndef RECIPELISTMODEL_H
#define RECIPELISTMODEL_H

#include <tuple>
#include <QAbstractListModel>
#include "backends/recipedb.h"

class RecipeListModel: public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit RecipeListModel(RecipeDB* db, QObject *parent = 0);
    
    ~RecipeListModel();
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//     int columnCount(const QModelIndex& parent) const;
    int rowCount(const QModelIndex& parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
//     QModelIndex parent(const QModelIndex& child);
//     QModelIndex index(int row, int column, const QModelIndex& parent);
    
private:
    std::vector< std::tuple<int, QString, int> > category_list;
    int rows;

};

#endif // RECIPELISTMODEL_H
