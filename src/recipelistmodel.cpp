/*
 *
 */

#include "recipelistmodel.h"

RecipeListModel::RecipeListModel(QObject *parent):QAbstractItemModel(parent)
{
    cols = COLS;
    rows = 5;
}

RecipeListModel::~RecipeListModel()
{

}

QVariant RecipeListModel::data(const QModelIndex& index, int role)
{
    if(index.row() < 0 || index.row() >= rows || index.column() < 0 || index.column() >= cols)
        return QVariant();
    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.row())
        {
        case 0:
            return "a";
        case 1:
            return "b";
        case 2:
            return "c";
        case 3:
            return "d";
        case 4:
            return "e";
        }
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignRight + Qt::AlignVCenter;
    }
    return QVariant();
}

int RecipeListModel::columnCount(const QModelIndex& parent)
{
    Q_UNUSED(parent);
    return cols;
}

int RecipeListModel::rowCount(const QModelIndex& parent)
{
    Q_UNUSED(parent);
    return rows;
}

Qt::ItemFlags RecipeListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

QModelIndex RecipeListModel::parent(const QModelIndex& child)
{

}

QModelIndex RecipeListModel::index(int row, int column, const QModelIndex& parent)
{

}
