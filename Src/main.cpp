// Qt headers
#include <QGuiApplication>
#include <QtQuick/QQuickView>
// System headers
#include <iostream>
// Own headers
#include <Game.h>

const std::string version = "alpha v0.09";
const std::string title = "Qt-VRGame";

int main(int argc, char *argv[])
{
    // Title and version
    std::cout << title.data() << ": " << version.data() << std::endl;

    // Create main app and qml view
    QGuiApplication app (argc, argv);
    QQuickView view;

    // Register main class under GameQML module
    qmlRegisterType<Game>("GameQML", 1, 0, "Game");

    // Setup main view
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/Assets/QML//main.qml"));
    view.setTitle(QString(title.data()) + QString(": ") + QString(version.data()));
    view.show();

    return app.exec();
}
