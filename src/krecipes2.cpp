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
#include "krecipes2view.h"

Krecipes2::Krecipes2(QWidget *parent) : KXmlGuiWindow(parent)
{
    qApp->setQuitOnLastWindowClosed(true); //FIXME why is this necessary?
    
    m_view = new Krecipes2View( this );
    setObjectName( "Krecipes2" );
    // accept dnd
    setAcceptDrops( true );

    // tell the KMainWindow that this is indeed the main widget
    setCentralWidget( m_view );
    
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
    qDebug();

    showRecipeAction = new QAction( this );
    showRecipeAction->setText( i18n( "Show Recipe(s)" ) );
    showRecipeAction->setIcon( QIcon::fromTheme( "system-search" ) );
    showRecipeAction->setShortcut( Qt::CTRL + Qt::Key_L );
    actionCollection()->addAction( "show_recipe_action", showRecipeAction );
    connect( showRecipeAction, SIGNAL(triggered(bool)), this, SLOT( showCurrentRecipes() ) );
    qApp->quitOnLastWindowClosed();
    
//     
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());
//     
    createGUI();
}

void Krecipes2::showCurrentRecipes()
{
    qDebug() << "show recipe";
}

Krecipes2::~Krecipes2()
{
    qDebug() << "good bye";
}

