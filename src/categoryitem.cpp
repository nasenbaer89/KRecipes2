#include "categoryitem.h"

CategoryItem::CategoryItem(const int id_, const QString name_, Type type_, CategoryItem *parent)
{
    Id = id_;
    Name = name_;
    type = type_;
    parentItem = parent;
}

CategoryItem::~CategoryItem()
{
    qDeleteAll(subCategories);
    qDeleteAll(recipes);
}

void CategoryItem::appendSubCategory(CategoryItem* child)
{
    subCategories.append(child);
}

void CategoryItem::appendRecipe(CategoryItem* recipe)
{
    recipes.append(recipe);
}

CategoryItem* CategoryItem::child(int row)
{
    if (row < subCategories.count())
        return subCategories.value(row);
    else
        return recipes.value(row - subCategories.count());
}

int CategoryItem::childCount() const
{
    return subCategories.count() + recipes.count();
}

int CategoryItem::row() const
{
    if (type == Category) {
        if (parentItem)
            return parentItem->subCategories.indexOf(const_cast<CategoryItem*>(this));
    }
    if (type == Recipe)
        return parentItem->recipes.indexOf(const_cast<CategoryItem*>(this)) + subCategories.count();
    return 0;
}

CategoryItem* CategoryItem::parent()
{
    return parentItem;
}

int CategoryItem::id()
{
    return Id;
}

QString CategoryItem::name()
{
    return Name;
}

