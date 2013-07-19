#ifndef RECIPELISTMODEL_H
#define RECIPELISTMODEL_H

#include <tuple>
#include <QAbstractItemModel>
#include "backends/recipedb.h"
#include "categoryitem.h"

class RecipeListModel: public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit RecipeListModel(RecipeDB* db, QObject *parent = 0);
    ~RecipeListModel();

    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column = 0, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;

private:
    std::vector< std::tuple<int, QString, int> > category_list;
    std::vector< std::tuple<int, QString, int> > recipe_list;
    void setupModelData();
    CategoryItem *rootItem;

};

#endif // RECIPELISTMODEL_H
