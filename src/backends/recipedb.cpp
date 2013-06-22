#include "recipedb.h"
#include "literecipedb.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <iostream>

RecipeDB::RecipeDB() : QObject(), connectionName( QString("krecipes")) //FIXME not unique
{
    
}

RecipeDB::~RecipeDB()
{
}

RecipeDB* RecipeDB::createDatabase(const QString &dbType, const QString &file)
{
    qDebug();
    RecipeDB * database = 0;

    if ( dbType == "SQLite" ) {
        database = new LiteRecipeDB(file);
    }
    else {
        qDebug() << "No database support included (or available) for the " << dbType << " database." ;
    }
    qDebug()<<" database :"<<database;
    return database;
}

RecipeDB::Error RecipeDB::connect( bool create_db, bool create_tables, const QString &host, const QString &user, const QString &pass, const QString &DBName, int port)
{
    qDebug() << "QSqlRecipeDB: Opening Database..." ;
    qDebug() << "Parameters: \n\thost: " << host << "\n\tuser: " << user << "\n\ttable: " << DBName ;

    
    //we need to have a unique connection name for each QSqlRecipeDB class as multiple db's may be open at once (db to db transfer)
//         qDebug()<<" qsqlDriver() :"<<qsqlDriver()<< " connectionName "<<connectionName;
    
    bool driver_found = false;

    const QStringList drivers = QSqlDatabase::drivers();
    for ( QStringList::const_iterator it = drivers.constBegin(); it != drivers.constEnd(); ++it ) {
        if ( ( *it ) == qsqlDriverPlugin() ) {
            driver_found = true;
            break;
        }
    }

    if ( !driver_found ) {
        std::cout << "The Qt database plugin " << qPrintable(qsqlDriverPlugin()) << " is not installed.  This plugin is required for using this database backend."<< std::endl;
        return NoDriverFound;
    }
    
    if ( !qsqlDriverPlugin().isEmpty() ) {
        qDebug()<<" qsqlDriverPlugin() :" << qsqlDriverPlugin()<<" connectionName :"<<connectionName;
        database = new QSqlDatabase;
        *database = QSqlDatabase::addDatabase( qsqlDriverPlugin(), connectionName );
    }

    qDebug()<< "DBname: " << DBName;
    database->setDatabaseName(DBName);
    if (!(user.isEmpty()))
        database->setUserName(user);
    if (!(pass.isEmpty()))
        database->setPassword(pass);
    database->setHostName( host );
    if ( port > 0 )
        database->setPort(port);
    qDebug() << "Parameters set. Calling database->open()" ;

    if ( !database->open() ) {
        qDebug()<<" database.open false : create_db ? :" << create_db;
    }
    qDebug()<<"database :"<<*database;

    if ( int( qRound( databaseVersion() * 1e5 ) ) > int( qRound( latestDBVersion() * 1e5 ) ) ) { //correct for float's imprecision
        std::cout << "This database was created with a newer version of Krecipes and cannot be opened." << std::endl;
        return NewerDbVersion;
    }
// 
//     // Check integrity of the database (tables). If not possible, exit
//     // Because checkIntegrity() will create tables if they don't exist,
//     // we don't want to run this when creating the database.  We would be
//     // logged in as another user (usually the superuser and not have ownership of the tables
//     if ( create_tables && !checkIntegrity() ) {
//         dbErr = i18n( "Failed to fix database structure." );
//         return FixDbFailed;
//     }
// 
//     // Database was opened correctly
//     m_query = new QSqlQuery( QString(), *database );
//     m_query->setForwardOnly(true);
//     dbOK = true;
//     return NoError;
}

double RecipeDB::latestDBVersion() const
{
    return 1;
}

QString RecipeDB::krecipes_version() const
{
//     const KComponentData * this_instance = &KGlobal::mainComponent();
//     if ( this_instance && this_instance->aboutData() )
//         return this_instance->aboutData() ->version();
    QString krecipes2_master;

    return QString(); //Oh, well.  We couldn't get the version (shouldn't happen).
}

float RecipeDB::databaseVersion()
{
    qDebug();
    QString command = "SELECT ver FROM db_info";
    QSqlQuery dbVersion( command, *database);
    qDebug() << "dbVersion.isActive() :" << dbVersion.isActive()<<" database :"<<database;
    qDebug() << "dbVersion.isSelect() :" <<dbVersion.isSelect();
    if ( dbVersion.isActive() && dbVersion.isSelect() && dbVersion.next() ) {
        qDebug() << "dbVersion.value(0).toString().toDouble() :"<<dbVersion.value( 0 ).toString().toDouble();
        return ( dbVersion.value(0).toString().toDouble() ); // There should be only one (or none for old DB) element, so go to first
    }
    else {
        qDebug()<<" old version";
        return ( 0.2 ); // if table is empty, assume oldest (0.2), and port
    }
}