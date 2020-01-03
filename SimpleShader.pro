include(../../../Common.pri)

TARGET = SimpleShader
SOURCES += \
    myscene.cpp \
    spieler.cpp

RESOURCES += \
    Assets.qrc \
    MyShaders.qrc \
    Sound.qrc

HEADERS += \
    spieler.h

CONFIG += resources_big
