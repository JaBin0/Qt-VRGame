// Qt headers
#include <QGuiApplication>
#include <QtQuick/QQuickView>

// System headers
#include <iostream>


// Own headers
#include <Game.h>

const std::string version = "0.04";

int main(int argc, char *argv[])
{
    // Title and version
    std::cout << "Qt-VRGame v" << version.data() << std::endl;

    // Create main app and qml view
    QGuiApplication app (argc, argv);
    QQuickView view;

    // Register main class under GameQML module
    qmlRegisterType<Game>("GameQML", 1, 0, "Game");

    // Setup main view
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///QML//main.qml"));
    view.show();

    return app.exec();
}
