#include <QtWidgets>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>
#include <kdebug.h>

#include "tableeditor.h"

TableEditor::TableEditor(QWidget* parent): QWidget(parent)
{
    qDebug();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../krecipes.sqlite");
    if (!db.open())
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This Program needs SQLite support."), QMessageBox::Cancel);
        return;
    }
    db_version = getDbVersion();
    db_version_latest = 1;
    if (db_version < db_version_latest)
    {
        portOldDatabse();
    }
    db_version = getDbVersion();
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
    connect(createButton, SIGNAL(clicked()), this, SLOT(create_tables()));

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


void TableEditor::create_tables(QString tablename)
{
    QSqlQuery query;
    if ((tablename == "db_info") || (tablename == "all")) {
        query.exec("create table db_info (ver FLOAT NOT NULL,generated_by varchar(200) default NULL)");
        if (query.lastError().type() != QSqlError::NoError)
            qDebug() << query.lastError();
        else {
            query.exec("insert into db_info values(1, 'krecipes2_master')");
            if (query.lastError().type() != QSqlError::NoError)
                qDebug() << query.lastError();
        }
    }
    if ((tablename == "authors") || (tablename == "all")) {
        //query.exec("drop table authors");
        query.exec("create table authors (id int NOT NULL primary key, name varchar(50) default NULL)");
        if (query.lastError().type() != QSqlError::NoError)
            qDebug() << query.lastError();
    }
    if ((tablename == "categories") || (tablename == "all")) {
        //query.exec("drop table categories");
        query.exec("create table categories (id int NOT NULL primary key, name varchar(40) default NULL,"
                   " parent_id int NOT NULL default -1)");
        if (query.lastError().type() != QSqlError::NoError)
            qDebug() << query.lastError();
    }
    if ((tablename == "recipes") || (tablename == "all")) {
        //query.exec("drop table recipes");
        query.exec("create table recipes (id int not null primary key, title varchar(200), author_id int,"
                   " category_id int, yield_amount float, yield_type_id int, instructions TEXT,"
                   " photo BLOB, prep_time TIME, ctime TIMESTAMP, mtime TIMESTAMP, atime TIMESTAMP)");
        if (query.lastError().type() != QSqlError::NoError)
            qDebug() << query.lastError();
    }
    if (tablename == "recipes_copy") {
        query.exec("create table recipes_copy(id int not null primary key, title varchar(200),"
                   " author_id int,  yield_amount float, yield_type_id int,"
                   " instructions TEXT, photo BLOB, prep_time TIME, ctime TIMESTAMP, mtime TIMESTAMP, atime TIMESTAMP)");
        if (query.lastError().type() != QSqlError::NoError)
            qDebug() << query.lastError();
    }
    if ((tablename == "yield_types") || (tablename == "all")) {
        query.exec("CREATE TABLE yield_types (id int NOT NULL primary key, name varchar(20))");
    }
}

void TableEditor::portOldDatabse()
{
    if ((round(db_version * 100)) == 96) //FIXME not very nice
    {
        QSqlQuery query;
        create_tables("recipes_copy");
        
        query.exec("insert into recipes_copy select recipes.id, recipes.title, author_list.author_id,"
                   " recipes.yield_amount, recipes.yield_type_id, recipes.instructions, recipes.photo,"
                   " recipes.prep_time, recipes.ctime, recipes.mtime, recipes.atime"
                   " from recipes left outer join author_list on author_list.recipe_id = recipes.id order by recipes.id asc;");
        if (query.lastError().type() != QSqlError::NoError) {
            qDebug() << query.lastError();
            return;
        }
        else
            query.exec("drop table author_list");
        
        query.exec("drop table recipes");
        create_tables("recipes");   
        query.exec("insert into recipes select recipes_copy.id, recipes_copy.title, recipes_copy.author_id,"
                   " category_list.category_id, recipes_copy.yield_amount, recipes_copy.yield_type_id, recipes_copy.instructions,"
                   " recipes_copy.photo, recipes_copy.prep_time, recipes_copy.ctime, recipes_copy.mtime, recipes_copy.atime"
                   " from recipes_copy left outer join category_list on category_list.recipe_id = recipes_copy.id and category_list.category_id != '-1' order by recipes_copy.id asc;");
        if (query.lastError().type() != QSqlError::NoError) {
            qDebug() << query.lastError();
            return;
        }
        else {
            query.exec("drop table category_list");
            query.exec("drop table recipes_copy");
        }
        
        query.exec("drop table db_info");
        create_tables("db_info");
    }
}