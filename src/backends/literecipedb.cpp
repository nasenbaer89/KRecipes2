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
#include <QStringList>
#include <tuple>

#include "literecipedb.h"

LiteRecipeDB::LiteRecipeDB( const QString &_dbFile ) : RecipeDB()
{
    qDebug();
}

void LiteRecipeDB::createTable(const QString &tableName) //FIXME auto indexes are created
{
    qDebug()<<" tableName :"<<tableName;
    QStringList commands;
    QSqlQuery query;

    if ((tableName == "authors") || (tableName == "all")) {
        commands << QString("create table authors (id int NOT NULL primary key, name varchar(%1) default NULL)")
                            .arg( maxAuthorNameLength() );
    }
    if ((tableName == "categories") || (tableName == "all")) {
        commands << QString("create table categories (id int NOT NULL primary key, name varchar(%1) default NULL,"
                            " parent_id int NOT NULL default -1)").arg( maxCategoryNameLength() );
        commands << "CREATE index parent_id_index ON categories(parent_id);"; //FIXME
    }
    if ((tableName == "db_info") || (tableName == "all")) {
        commands << ("create table db_info (ver FLOAT NOT NULL,generated_by varchar(200) default NULL)");
        commands << QString("insert into db_info values(%1, 'Krecipes2 %2')")
                    .arg(latestDBVersion()).arg(krecipes_version());
    }
    if ((tableName == "ingredients") || (tableName == "all")) {
        commands << QString("create table ingredients (id int not null primary key, name varchar(%1));" )
        .arg(maxIngredientNameLength());
    }
    if ((tableName == "ingredient_info") || (tableName == "all")) { //FIXME
        commands << "CREATE TABLE ingredient_info (ingredient_id INT, property_id INT, amount FLOAT, per_units INTEGER);";
    }
    if ((tableName == "ingredient_groups") || (tableName == "all")) {//FIXME
        commands << QString("CREATE TABLE ingredient_groups (id INT NOT NULL primary key, name varchar(%1));" )
                            .arg( maxIngGroupNameLength() );
    }
    if ((tableName == "ingredient_list") || (tableName == "all")) { //FIXME what does this table do?
        commands << "CREATE TABLE ingredient_list (id INT NOT NULL primary key, recipe_id INT, ingredient_id INT,"
                    " amount FLOAT, amount_offset FLOAT, unit_id INT, order_index INT, group_id INT, substitute_for INT);"
        << "CREATE index ridil_index ON ingredient_list(recipe_id);" // FIXME what are the indexes doing?
        << "CREATE index iidil_index ON ingredient_list(ingredient_id);"
        << "CREATE index gidil_index ON ingredient_list(group_id);";
    }
    if ((tableName == "ingredient_properties") || (tableName == "all")) { //FIXME
        commands << QString("CREATE TABLE ingredient_properties (id INT NOT NULL primary key, name VARCHAR(%1),"
                            " units VARCHAR(%2));").arg( maxPrepMethodNameLength() ).arg( maxUnitNameLength() );
    }
    if ((tableName == "ingredient_weights") || (tableName == "all")) { //FIXME
        commands << "CREATE TABLE ingredient_weights (id INT NOT NULL primary key, ingredient_id INT NOT NULL,"
                    " amount FLOAT, unit_id INT, weight FLOAT, weight_unit_id INT, prep_method_id INT);"
        << "CREATE index weight_wid_index ON ingredient_weights(weight_unit_id)"
        << "CREATE index weight_pid_index ON ingredient_weights(prep_method_id)"
        << "CREATE index weight_uid_index ON ingredient_weights(unit_id)"
        << "CREATE index weight_iid_index ON ingredient_weights(ingredient_id)";
    }
    if ((tableName == "prep_methods") || (tableName == "all")) {
        commands << QString("CREATE TABLE prep_methods (id INT NOT NULL primary key, name VARCHAR(%1));" )
                            .arg( maxPrepMethodNameLength() );
    }
    if ((tableName == "prep_method_list") || (tableName == "all")) { //FIXME
        commands << "CREATE TABLE prep_method_list (ingredient_list_id INT NOT NULL, prep_method_id INT NOT NULL,"
                    "order_index INTEGER );"
        << "CREATE index iid_index ON prep_method_list(ingredient_list_id);"
        << "CREATE index pid_index ON prep_method_list(prep_method_id);";
    }
    if ((tableName == "ratings") || (tableName == "all")) { //FIXME
        commands << "CREATE TABLE ratings (id INT NOT NULL primary key, recipe_id int(11) NOT NULL, comment TEXT,"
                    " rater TEXT, created TIMESTAMP);";
    }
    if ((tableName == "rating_criteria") || (tableName == "all")) { //FIXME
        commands << "CREATE TABLE rating_criteria (id INT NOT NULL primary key, name TEXT);";
    }
    if ((tableName == "rating_criterion_list") || (tableName == "all")) { //FIXME
        commands << "CREATE TABLE rating_criterion_list (rating_id INT NOT NULL, rating_criterion_id INT, stars FLOAT);";
    }
    if ((tableName == "recipes") || (tableName == "all")) {
    commands << QString("create table recipes (id int not null primary key, title varchar(%1), author_id int,"
                        " category_id int, yield_amount float, yield_type_id int, instructions TEXT,"
                        " photo BLOB, prep_time TIME, ctime TIMESTAMP, mtime TIMESTAMP, atime TIMESTAMP);")
                        .arg(maxRecipeTitleLength());
    }
    if (tableName == "recipes_copy") {
        commands << QString("create table recipes_copy(id int not null primary key, title varchar(%1),"
                            " author_id int,  yield_amount float, yield_type_id int, instructions TEXT,"
                            " photo BLOB, prep_time TIME, ctime TIMESTAMP, mtime TIMESTAMP, atime TIMESTAMP)")
                            .arg(maxRecipeTitleLength());
    }
    if ((tableName == "units") || (tableName == "all")) {
        commands << QString("CREATE TABLE units (id INT NOT NULL primary key, name VARCHAR(%1), name_abbrev VARCHAR(%2),"
                            " plural VARCHAR(%3), plural_abbrev VARCHAR(%4), type INT NOT NULL DEFAULT '0');" )
           .arg( maxUnitNameLength() ).arg( maxUnitNameLength() ).arg( maxUnitNameLength() ).arg( maxUnitNameLength() );
    }
    if ((tableName == "units_conversion") || (tableName == "all")) {//FIXME
        commands << "CREATE TABLE units_conversion (unit1_id INT, unit2_id INT, ratio FLOAT);";
    }
    if ((tableName == "unit_list") || (tableName == "all")) { //FIXME neccessar?
        commands << "CREATE TABLE unit_list (ingredient_id INT, unit_id INT);";
    }
    if ((tableName == "yield_types") || (tableName == "all")) {
        commands << QString("CREATE TABLE yield_types (id int NOT NULL primary key, name varchar(%1))")
                            .arg( maxYieldTypeLength() );
    }
    // execute the queries
    for ( QStringList::const_iterator it = commands.constBegin(); it != commands.constEnd(); ++it ) {
        database->exec( *it );
        if (database->lastError().type() != QSqlError::NoError)
            qDebug() << " " << database->lastError();
    }
}

std::vector< std::tuple<int, QString, int> > LiteRecipeDB::getCategories()
{
    QString command = "SELECT id, name, parent_id FROM categories";
    QSqlQuery query(command, *database);
    if (query.lastError().type() != QSqlError::NoError) {
        qDebug() << query.lastError();
        return std::vector< std::tuple<int, QString, int> >();
    }
    std::vector< std::tuple<int, QString, int> > category_list;
    if (query.isActive() && query.isSelect())
    {
        while(query.next())
        {
            category_list.push_back(std::make_tuple<int, QString, int>(query.value(0).toInt(),
                                                                       query.value(1).toString(),
                                                                       query.value(2).toInt()));
        }
    }
    return category_list;
}

std::vector< std::tuple< int, QString, int > > LiteRecipeDB::getRecipes()
{
    QString command = "SELECT id, title, category_id FROM recipes order by category_id asc";
    QSqlQuery query(command, *database);
    if (query.lastError().type() != QSqlError::NoError) {
        qDebug() << query.lastError();
        return std::vector< std::tuple<int, QString, int> >();
    }
    std::vector< std::tuple<int, QString, int> > recipe_list;
    if (query.isActive() && query.isSelect())
    {
        while(query.next())
        {
            recipe_list.push_back(std::make_tuple<int, QString, int>(query.value(0).toInt(),
                                                                       query.value(1).toString(),
                                                                       query.value(2).toInt()));
        }
    }
    return recipe_list;
}


void LiteRecipeDB::portOldDatabases(float version)
{//TODO switch(), make version integer
    qDebug() << "porting...";
    if ((qRound(version * 100)) < 100) //FIXME not very nice
    {
        QSqlQuery query(*database);
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
    qDebug() << "done.";
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

// void LiteRecipeDB::storePhoto( int recipeID, const QByteArray &data ) //TODO
// {
//     QSqlQuery query( QString(), *database);
// 
//     query.prepare( "UPDATE recipes SET photo=\"?\",ctime=ctime,atime=atime,mtime=mtime WHERE id=" + QString::number( recipeID ) );
//     query.addBindValue( KCodecs::base64Encode( data ) );
//     query.exec();
// }

// QStringList LiteRecipeDB::backupCommand() const //TODO
// {
//     KConfigGroup config( KGlobal::config(), "Server" );
//     QString binary = config.readEntry( "SQLitePath", "sqlite3" );
// 
//     QStringList command;
//     command<<binary<<database->databaseName()<<".dump";
//     return command;
// }
// 
// QStringList LiteRecipeDB::restoreCommand() const //TODO
// {
//     KConfigGroup config( KGlobal::config(), "Server" );
//     QString binary = config.readEntry( "SQLitePath", "sqlite3" );
// 
//     QStringList command;
//     command<<binary<<database->databaseName();
//     return command;
// }

LiteRecipeDB::~LiteRecipeDB()
{
}