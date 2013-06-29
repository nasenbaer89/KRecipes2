#ifndef RECIPELISTMODEL_H
#define RECIPELISTMODEL_H

#include <tuple>
#include <../../home/stefanie/Programmieren/Qt/Qt5/qt5-dev/qtbase/include/QtCore/qabstractitemmodel.h>

class RecipeListModel: public QAbstractItemModel
{
    Q_OBJECT
    
public:
    explicit RecipeListModel(QObject *parent = 0);
    
    ~RecipeListModel();
    QVariant data(const QModelIndex& index, int role);
    int columnCount(const QModelIndex& parent);
    int rowCount(const QModelIndex& parent);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex parent(const QModelIndex& child);
    QModelIndex index(int row, int column, const QModelIndex& parent);
    
private:
    std::vector< std::tuple<int, QString, int> > category_list;
    const static int COLS = 1;
    int rows, cols;

};

#endif // RECIPELISTMODEL_H
