// Qt headers
#include <QGuiApplication>
#include <QtQuick/QQuickView>

// System headers

// Own headers

int main(int argc, char *argv[])
{
    QGuiApplication app (argc, argv);
    QQuickView view;

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return app.exec();
}
