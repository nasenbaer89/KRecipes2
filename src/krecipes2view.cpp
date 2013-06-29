#include <klocalizedstring.h>
#include <QTreeWidgetItem>
#include <tuple>

#include "backends/recipedb.h"

#include "krecipes2view.h"
#include "../build/ui_krecipes2view.h"
#include "recipelistmodel.h"


Krecipes2View::Krecipes2View(QWidget *parent)
{
    
    ui = new Ui::Krecipes2View;
    ui->setupUi ( this );
    
    RecipeDB* db = RecipeDB::createDatabase("SQLite");
    db->connect();
    
    RecipeListModel *model = new RecipeListModel(db, this);
    ui->treeView->setModel(model);
//     ui->treeView->setHeaderLabel(i18n("Recipe"));
//     for (auto iter = category_list.begin(); iter != category_list.end(); ++iter)
//     {
//         if (std::get<2>(*iter) < 0) {
//             QTreeWidgetItem *category = new QTreeWidgetItem(ui->treeWidget);
//             category->setText(0, std::get<1>(*iter));
//         }
//     }
//     QTreeWidgetItem *test2 = new QTreeWidgetItem(test);
//     test2->setText(0, tr("hallo2"));
}

Krecipes2View::~Krecipes2View()
{
    delete ui;
}
