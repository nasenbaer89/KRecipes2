#include <klocalizedstring.h>
#include <kaboutdata.h>
#include <QApplication>
// #include <QtQuick/QQuickView>
// #include <QtQml/QQmlEngine>
#include "krecipes2.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    KAboutData aboutData("krecipes2",               //componentName
                         0,                         //catalogName
                         i18n("Krecipes2"),        //displayName
                         "1.0",                     //version
                         i18n("The KDE Cookbook"), //shortDescription
                         KAboutData::License_GPL,   //licenseType
                         i18n("(c) 2013"),         //copyrightStatement
                         // Optional text shown in the About box.
                         // Can contain any information desired.
                         i18n("This product is RecipeML compatible.\nYou can get more information about this file"
                         "format in:\nhttp://www.formatdata.com/recipeml"),
                         "http://example.com/",     //homePageAddress
                         "submit@bugs.kde.org");    //bugsEmailAddress

    QApplication app(argc, argv);
    app.setApplicationName(aboutData.componentName());
    app.setApplicationVersion(aboutData.catalogName());
    app.setOrganizationDomain(aboutData.homepage());
    app.setApplicationDisplayName(aboutData.displayName());

    Krecipes2 * widget = new Krecipes2;
    widget->show();
//     QQuickView viewer;
//     viewer.setSource(QUrl("../src/qml/main.qml"));
//     viewer.show();
// 
//     QObject::connect(viewer.engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    return app.exec();
}
