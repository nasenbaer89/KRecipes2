/***************************************************************************
*   Copyright © 2003 Unai Garro <ugarro@gmail.com>                        *
*   Copyright © 2003 Cyril Bosselut <bosselut@b1project.com>              *
*   Copyright © 2003-2006 Jason Kivlighn <jkivlighn@gmail.com>            *
*   FIXME
*
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/

#ifndef KRECIPES_H
#define KRECIPES_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <tuple>

#define DEFAULT_DB_NAME "Krecipes"

class RecipeDB: public QObject
{
    Q_OBJECT

public:
    enum Error {NoError = 0, NoDriverFound, RefusedByServer, NewerDbVersion, FixDbFailed};

    RecipeDB();
    virtual ~RecipeDB();

    static RecipeDB* createDatabase(const QString &dbType, const QString &file = QString());   //FIXME
    RecipeDB::Error connect(const QString &host = QString(), const QString &user = QString(),
                            const QString &pass = QString(), const QString &DBName = DEFAULT_DB_NAME, int port = 0);
    //FIXME what are create_db, create_tables?
    virtual void createTable(const QString &tableName = "all") = 0;

    virtual int maxAuthorNameLength() const = 0;
    virtual int maxCategoryNameLength() const = 0;
    virtual int maxIngredientNameLength() const = 0;
    virtual int maxIngGroupNameLength() const = 0;
    virtual int maxRecipeTitleLength() const = 0;
    virtual int maxUnitNameLength() const = 0;
    virtual int maxPrepMethodNameLength() const = 0;
    virtual int maxPropertyNameLength() const = 0;
    virtual int maxYieldTypeLength() const = 0;

    float databaseVersion();      //FIXME virtual??
    RecipeDB::Error checkIntegrity();

    virtual std::vector< std::tuple<int, QString, int> > getCategories() = 0;
    virtual std::vector< std::tuple<int, QString, int> > getRecipes() = 0;

protected:
    double latestDBVersion() const;
    QString krecipes_version() const;
    QSqlDatabase * database;
    QSqlQuery * m_query;
    virtual QString qsqlDriverPlugin() const {
        return QString();
    }

    virtual void portOldDatabases(float version) = 0;
private:
//     QString DBname;
    const QString connectionName;
};

#endif
