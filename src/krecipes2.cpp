#include <QtWidgets>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>
#include <kdebug.h>

#include "krecipes2.h"
#include "backends/recipedb.h"

TableEditor::TableEditor(QWidget* parent): QWidget(parent)
{
    qDebug();
    RecipeDB* db = RecipeDB::createDatabase("SQLite");
    db->connect(true, true);

//     if (db.tables().isEmpty())
//         create_tables();
//     else {
//         db_version = getDbVersion();
//         db_version_latest = 1;
//         if (db_version < db_version_latest) {
//             portOldDatabse();
//         }
//     }
//     db_version = getDbVersion();
    //create_tables();
// 
//     query.exec("create table images (locationid int, file varchar(20))");
//     query.exec("insert into images values(0, 'images/oslo.png')");
//     query.exec("insert into images values(1, 'images/brisbane.png')");
//     query.exec("insert into images values(2, 'images/redwood.png')");
//     query.exec("insert into images values(3, 'images/berlin.png')");
//     query.exec("insert into images values(4, 'images/munich.png')");
//     query.exec("insert into images values(5, 'images/beijing.png')");
    
    createButton = new QPushButton(tr("Create Database"));
    createButton->setDefault(true);
    
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(createButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
//     connect(createButton, SIGNAL(clicked()), this, SLOT(create_tables()));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

//     setWindowTitle(tr("Cached Table"));
}

float TableEditor::getDbVersion()
{
    QSqlQuery dbVersion;
    dbVersion.exec("SELECT ver FROM db_info");
    if ( dbVersion.isActive() && dbVersion.isSelect() && dbVersion.next() ) {
        qDebug()<<" dbVersion.value( 0 ).toString().toFloat() :"<<dbVersion.value( 0 ).toString().toFloat();
        // There should be only one (or none for old DB) element, so go to first
        return ( dbVersion.value( 0 ).toString().toDouble() ); 
    }
    else {
        qDebug()<<" old version";
        return ( 0.2 ); // if table is empty, assume oldest (0.2), and port
    }
}

