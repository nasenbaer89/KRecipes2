#include <QtWidgets>
#include <iostream>
#include <qdebug.h>

#include "krecipes2.h"
#include "backends/recipedb.h"

Krecipes2::Krecipes2(QWidget* parent): KXmlGuiWindow(parent)
{
    qDebug();
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
// //     connect(createButton, SIGNAL(clicked()), this, SLOT(create_tables()));
// 
//     QHBoxLayout *mainLayout = new QHBoxLayout;
//     mainLayout->addWidget(buttonBox);
//     setLayout(mainLayout);

//     setWindowTitle(tr("Cached Table"));
}