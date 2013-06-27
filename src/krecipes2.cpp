#include <QApplication>
#include <iostream>
#include <klocalizedstring.h>
#include <QAction>
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <qicon.h>
#include <QDebug>

#include "krecipes2.h"
#include "backends/recipedb.h"

Krecipes2::Krecipes2(QWidget *parent) : KXmlGuiWindow(parent)
{
    qDebug() << "test";
    setupActions();
//     RecipeDB* db = RecipeDB::createDatabase("SQLite");
//     db->connect();
    
//     createButton = new QPushButton(tr("Create Database"));
//     createButton->setDefault(true);
//     
//     quitButton = new QPushButton(tr("Quit"));
// 
//     buttonBox = new QDialogButtonBox(Qt::Vertical);
//     buttonBox->addButton(createButton, QDialogButtonBox::AcceptRole);
//     buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
// 
//     connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
//     connect(createButton, SIGNAL(clicked()), this, SLOT(create_tables()));

//     QHBoxLayout *mainLayout = new QHBoxLayout;
//     mainLayout->addWidget(buttonBox);
//     setLayout(mainLayout);

//     setWindowTitle(tr("Cached Table"));
}

void Krecipes2::setupActions()
{
    qDebug() << "test2";

    showRecipeAction = new QAction( this );
    showRecipeAction->setText( i18n( "Show Recipe(s)" ) );
    showRecipeAction->setIcon( QIcon::fromTheme( "system-search" ) );
    showRecipeAction->setShortcut( Qt::CTRL + Qt::Key_L );
    actionCollection()->addAction( "show_recipe_action", showRecipeAction );
    connect( showRecipeAction, SIGNAL(triggered(bool)), this, SLOT( showCurrentRecipes() ) );
    
//     
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());
//     
    createGUI();
}

void Krecipes2::showCurrentRecipes()
{
    qDebug() << "show recipe";
}

