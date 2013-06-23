#include <QApplication>
#include <QSqlDatabase>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include "krecipes2.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Krecipes2 widget;
    widget.show();
//     QQuickView viewer;
//     viewer.setSource(QUrl("../src/qml/main.qml"));
//     viewer.show();
// 
//     QObject::connect(viewer.engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    return app.exec();
}
