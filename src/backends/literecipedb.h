/***************************************************************************
*   Copyright © 2003-2004 Unai Garro <ugarro@gmail.com>                   *
*   Copyright © 2003-2004 Jason Kivlighn <jkivlighn@gmail.com>            *
*   Copyright © 2003-2004 Cyril Bosselut <bosselut@b1project.com>
*   Copyright © 2013 Stefanie Dargel <nasenbaer8912@gmail.com>
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/

#ifndef LITERECIPEDB_H
#define LITERECIPEDB_H 

#include "recipedb.h"

#define SQLITE_DRIVER "QSQLITE"

class LiteRecipeDB : public RecipeDB
{
    Q_OBJECT
    
public:
    LiteRecipeDB(const QString &DBName = DEFAULT_DB_NAME);
    ~LiteRecipeDB(void);
    
    virtual void createTable(const QString &tableName = "all");

    virtual int maxAuthorNameLength() const;
    virtual int maxCategoryNameLength() const;
    virtual int maxIngredientNameLength() const;
    virtual int maxIngGroupNameLength() const;
    virtual int maxRecipeTitleLength() const;
    virtual int maxUnitNameLength() const;
    virtual int maxPrepMethodNameLength() const;
    virtual int maxPropertyNameLength() const;
    virtual int maxYieldTypeLength() const;
    
    private:
    virtual void portOldDatabases(float version); //TODO does not import older than recent upstream version
    QString qsqlDriverPlugin() const { return SQLITE_DRIVER; }
//     virtual QStringList backupCommand() const; //TODO
//     virtual QStringList restoreCommand() const; //TODO
//     virtual void storePhoto( int recipeID, const QByteArray &data ); //TODO
    
    //FIXME what are those funtions for?
//     protected:
//     QString escapeAndEncode( const QString &s ) const;
//     virtual QString unescapeAndDecode( const QByteArray &s ) const;
//     private:
//     QString escape( const QString &s ) const;
};

#endif