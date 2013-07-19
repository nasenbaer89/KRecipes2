#ifndef CATEGORYITEM_H
#define CATEGORYITEM_H

#include <QList>
#include <QVariant>

class CategoryItem
{
public:
    enum Type {Category = 0, Recipe};

    explicit CategoryItem(const int id_, const QString name_, Type type_, CategoryItem *parent = 0); //FIXME wrong name
    ~CategoryItem();

    void appendSubCategory(CategoryItem *child);
    void appendRecipe(CategoryItem *recipe);

    CategoryItem *child(int row);
    int childCount() const;
    int row() const;
    QList<CategoryItem*> subCategories;
    QList<CategoryItem*> recipes;
    CategoryItem *parent();
    QString name();
    int id();
    Type type;


private:
    CategoryItem *parentItem;
    QString Name;
    int Id;
};

#endif // CATEGORYITEM_H
