QT += qml quick
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Src/main.cpp \
    Src/Main/Game.cpp \
    Src/Main/GameContent.cpp \
    Src/Graphic/GameRenderer.cpp \
    Src/Assets/GameResourcesManager.cpp \
    Src/Main/SysMethods.cpp

RESOURCES += \
    Assets/QML/qml.qrc \
    Assets/Shaders/shaders.qrc \
    Assets/Models/models.qrc

INCLUDEPATH += \
    Src \
    Src/Main \
    Src/Graphic \
    Src/Assets \


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Src/Main/Game.h \
    Src/Main/GameContent.h \
    Src/Graphic/GameRenderer.h \
    Src/Assets/GameResourcesManager.h \
    Src/Main/SystemTypes.h \
    Src/Main/SysMethods.h \
    Src/Main/Config.h

DISTFILES +=

