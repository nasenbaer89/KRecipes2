#include <QApplication>
#include <QSqlDatabase>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include "tableeditor.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TableEditor editor;
    editor.show();
//     QQuickView viewer;
//     viewer.setSource(QUrl("../src/qml/main.qml"));
//     viewer.show();
// 
//     QObject::connect(viewer.engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    return app.exec();
}
