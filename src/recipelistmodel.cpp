#include <klocalizedstring.h>
#include "recipelistmodel.h"
#include <qlocale.h>
#include <QDebug>

RecipeListModel::RecipeListModel(RecipeDB* db, QObject *parent): QAbstractItemModel(parent)
{
    category_list = db->getCategories();
    rootItem = new CategoryItem(0, i18n("Recipe"));
    setupModelData();
}

RecipeListModel::~RecipeListModel()
{
    delete rootItem;
}

QModelIndex RecipeListModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CategoryItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CategoryItem*>(parent.internalPointer());

    CategoryItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex RecipeListModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    CategoryItem *childItem = static_cast<CategoryItem*>(index.internalPointer());
    CategoryItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int RecipeListModel::rowCount(const QModelIndex& parent) const
{
    CategoryItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CategoryItem*>(parent.internalPointer());
    return parentItem->childCount();
}

int RecipeListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant RecipeListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    CategoryItem *category = static_cast<CategoryItem*>(index.internalPointer());
    return category->name();
}

QVariant RecipeListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->name();

    return QVariant();
}

Qt::ItemFlags RecipeListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    if (!index.isValid())
        return 0;

//     return QAbstractListModel::flags(index);
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

void RecipeListModel::setupModelData()
{
    for (auto category : category_list) {
        int id = std::get<0>(category);
        QString name = std::get<1>(category);
        int parent_id = std::get<2>(category);

        if (parent_id == -1) {
            rootItem->appendChild(new CategoryItem(id, name, rootItem));
        } else {
            for (auto & top_category : rootItem->childItems) {
                if (top_category->id() == parent_id) {
                    top_category->appendChild(new CategoryItem(id, name, top_category));
                }
            }
        }
    }
}

