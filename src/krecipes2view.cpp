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

}

Krecipes2View::~Krecipes2View()
{
    delete ui;
}
