import QtQuick 2.0
import GameQML 1.0

Item {
    id: root
    width: 320
    height: 480

    Game {
        id: game

    }


    Rectangle {
        id: blue;
        color: Qt.rgba(0.1, 0.1, 0.4, 1.0)
        anchors.bottom: root.bottom
        anchors.left: root.left
        anchors.right: red.left

        height: 50
        width: 100
    }

    Rectangle {
        id: red;
        color: Qt.rgba(0.4, 0.1, 0.1, 1.0)
        anchors.top: blue.top
        anchors.bottom: root.bottom
        anchors.right: root.right
        anchors.left: blue.right
    }
}
