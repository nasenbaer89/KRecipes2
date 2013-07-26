// #include "recipedb.h"
#include "literecipedb.h"
#include <klocalizedstring.h>

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RecipeDB::RecipeDB() : QObject(), connectionName(QString("krecipes"))  //FIXME not unique
{
}

RecipeDB::~RecipeDB()
{
}

RecipeDB* RecipeDB::createDatabase(const QString &dbType, const QString &file)
{
//     qDebug();
    RecipeDB * database = 0;

    if (dbType == "SQLite") {
        database = new LiteRecipeDB(file);
    } else {
        qDebug() << "No database support included (or available) for the " << dbType << " database." ;
    }
//     qDebug() << "database :" << database;
    return database;
}

RecipeDB::Error RecipeDB::connect(const QString &host, const QString &user, const QString &pass, const QString &DBName, int port)
{
//     qDebug();
    qDebug() << "QSqlRecipeDB: Opening Database..." ;
    qDebug() << "Parameters: \thost: " << host << "\tuser: " << user << "\tDBName: " << DBName ;


    //we need to have a unique connection name for each QSqlRecipeDB class as multiple db's may be open at once (db to db transfer)
//         qDebug()<<" qsqlDriver() :"<<qsqlDriver()<< " connectionName "<<connectionName;

    bool driver_found = false;

    const QStringList drivers = QSqlDatabase::drivers();
    for (QStringList::const_iterator it = drivers.constBegin(); it != drivers.constEnd(); ++it) {
        if ((*it) == qsqlDriverPlugin()) {
            driver_found = true;
            break;
        }
    }

    if (!driver_found) {
        qDebug() << i18n("The Qt database plugin '%1' is not installed.  This plugin is required for using this database backend.", qsqlDriverPlugin()); //FIXME should be shown to the user
        return NoDriverFound;
    }

    if (!qsqlDriverPlugin().isEmpty()) {
//         qDebug() << "qsqlDriverPlugin() :" << qsqlDriverPlugin() << " connectionName :" << connectionName;
        database = new QSqlDatabase;
        *database = QSqlDatabase::addDatabase(qsqlDriverPlugin(), connectionName);
    }

    database->setDatabaseName(DBName);
    if (!(user.isEmpty()))
        database->setUserName(user);
    if (!(pass.isEmpty()))
        database->setPassword(pass);
    database->setHostName(host);
    if (port > 0)
        database->setPort(port);
    qDebug() << "Parameters set. Calling database->open()" ;

    if (!database->open()) {
        qDebug() << "database.open false";
    }
    qDebug() << "database :" << *database;

//
//     // Check integrity of the database (tables). If not possible, exit
//     // Because checkIntegrity() will create tables if they don't exist,
//     // we don't want to run this when creating the database.  We would be
//     // logged in as another user (usually the superuser and not have ownership of the tables //FIXME what??

    Error integr_err = checkIntegrity();
    if (integr_err == NewerDbVersion) {
        qDebug() << i18n("This database was created with a newer version of Krecipes and cannot be opened."); //FIXME should be shown to the user
        return NewerDbVersion;
    } else if (integr_err == FixDbFailed) {
        qDebug() << i18n("Failed to fix database structure."); //FIXME should be shown to the user
        return FixDbFailed;
    }

    // Database was opened correctly
    m_query = new QSqlQuery(QString(), *database);
    m_query->setForwardOnly(true);
    return NoError;
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
//     else?
//     return QString(); //Oh, well.  We couldn't get the version (shouldn't happen).
    return "krecipes2_master";

}

float RecipeDB::databaseVersion() //FIXME this should go into literecipedb?
{
//     qDebug();
    QString command = "SELECT ver FROM db_info";
    QSqlQuery dbVersion(command, *database);
    if (dbVersion.lastError().type() != QSqlError::NoError) {
        qDebug() << dbVersion.lastError();
    }
    if (dbVersion.isActive() && dbVersion.isSelect() && dbVersion.next()) {
//         qDebug() << "dbVersion.value(0).toString().toDouble() :" << dbVersion.value(0).toString().toDouble();
        return (dbVersion.value(0).toString().toDouble());   // There should be only one (or none for old DB) element, so go to first
    } else {
        qDebug() << " old version";
        return (0.2);   // if table is empty, assume oldest (0.2), and port
    }
}

RecipeDB::Error RecipeDB::checkIntegrity()
{
//     qDebug();
    QStringList existingTableList = database->tables();
    if (existingTableList.isEmpty()) {
        createTable();
        qDebug() << "New Database created!";
        return NoError;
    }

    qDebug() << "Checking database version...";
    float version = databaseVersion();
    float latest_version = latestDBVersion();
    if (int(qRound(version * 1e5)) > int(qRound(latest_version * 1e5))) {           //correct for float's imprecision
        return NewerDbVersion;
    }

    // Check for older versions, and port
//     qDebug();
    qDebug() << "version found... " << version;
    qDebug() << "latest version... " << latest_version;
    if (int(qRound(version * 1e5)) < int(qRound(latest_version * 1e5))) {           //correct for float's imprecision
        switch (QMessageBox::question(0,
                                      "@info", "<p>The database was created with a previous version of Krecipes. "
                                      "Would you like Krecipes to update this database to work with this version of "
                                      "Krecipes?  Depending on the number of recipes and amount of data, this could "
                                      "take some time.</p>"
                                      "<warning>"
                                      "<p>After updating, this database will no longer be compatible with "
                                      "previous versions of Krecipes.</p>"
                                      "<p>Cancelling this operation may result in corrupting the database.</p>"
                                      "</warning>")) {
        case QMessageBox::Yes:
            portOldDatabases(version);
            break;
        case QMessageBox::No:
            return FixDbFailed;
        }
    }
    // FIXME is this really necessary??
    // Check existence of the necessary tables (the database may be created, but empty)
    QStringList tables = {"authors", "categories", "db_info", "ingredients", "ingredient_groups", "ingredient_info",
                          "ingredient_list", "ingredient_properties", "ingredient_weights",
                          "prep_method_list", "prep_methods", "rating_criteria", "rating_criterion_list",
                          "ratings", "recipes", "unit_list", "units", "units_conversion", "yield_types"
                         };
    existingTableList.clear();
    existingTableList << database->tables();
    tables.sort();
    existingTableList.sort();
    auto it_ex = existingTableList.begin();
    for (auto it = tables.begin(); it != tables.end(); ++it) {
        if ((it_ex != tables.end()) && (*it == *it_ex))
            ++it_ex;
        else {
            qDebug() << "Recreating missing table: " << *it;
            createTable(*it);
        }
    }
    // FIXME is this really necessary??
    QStringList newTableList = database->tables();
    if (newTableList.isEmpty())
        return FixDbFailed;
    return NoError;
}


