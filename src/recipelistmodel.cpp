#include <klocalizedstring.h>
#include "recipelistmodel.h"

RecipeListModel::RecipeListModel(RecipeDB* db, QObject *parent):QAbstractListModel(parent)
{
    category_list = db->getCategories();
    rows = category_list.size();
}

RecipeListModel::~RecipeListModel()
{
}

QVariant RecipeListModel::data(const QModelIndex& index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        return std::get<1>(category_list[index.row()]);
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignLeft + Qt::AlignVCenter;
    }
    return QVariant();
}

QVariant RecipeListModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        return i18n("Recipe");
    }
    if (orientation == Qt::Vertical)
    {
        return " ";
    }
    return QVariant();
 }


int RecipeListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return rows;
}

Qt::ItemFlags RecipeListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

// QModelIndex RecipeListModel::parent(const QModelIndex& child)
// {
// 
// }
// 
// QModelIndex RecipeListModel::index(int row, int column, const QModelIndex& parent)
// {
// 
// }
