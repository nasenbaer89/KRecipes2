/***************************************************************************
*   Copyright © 2003-2004 Unai Garro <ugarro@gmail.com>                   *
*   Copyright © 2003-2004, 2006 Jason Kivlighn <jkivlighn@gmail.com>      *
*   Copyright © 2003-2004 Cyril Bosselut <bosselut@b1project.com> 
*   Copyright © 2013 Stefanie Dargel <nasenbaer8912@gmail.com>
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "literecipedb.h"

LiteRecipeDB::LiteRecipeDB( const QString &_dbFile ) : RecipeDB()
{
    qDebug();
}

void LiteRecipeDB::createTable(const QString &tablename)
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

void LiteRecipeDB::portOldDatabases(float version)
{
    if ((qRound(version * 100)) == 96) //FIXME not very nice
    {
        QSqlQuery query;
        createTable("recipes_copy");
        
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
        createTable("recipes");   
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
        createTable("db_info");
    }
}

int LiteRecipeDB::maxAuthorNameLength() const
{
    return 50;
}

int LiteRecipeDB::maxCategoryNameLength() const
{
    return 40;
}

int LiteRecipeDB::maxIngredientNameLength() const
{
    return 50;
}

int LiteRecipeDB::maxIngGroupNameLength() const
{
    return 50;
}

int LiteRecipeDB::maxRecipeTitleLength() const
{
    return 200;
}

int LiteRecipeDB::maxUnitNameLength() const
{
    return 20;
}

int LiteRecipeDB::maxPrepMethodNameLength() const
{
    return 20;
}

int LiteRecipeDB::maxPropertyNameLength() const
{
    return 20;
}

int LiteRecipeDB::maxYieldTypeLength() const 
{
    return 20;
}

LiteRecipeDB::~LiteRecipeDB()
{
}