#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T20:54:43
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = SMCCC
TEMPLATE = lib

DEFINES += SMCCC_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        smccc.cpp \
    auth/auth.cpp \
    auth/yggdrasil.cpp \
    json/json.cpp \
    json/json_assets.cpp \
    json/json_downloads.cpp \
    json/json_inheritsfrom.cpp \
    json/json_libraries.cpp \
    json/json_natives.cpp \
    core.cpp \
    net/httprequest.cpp \
    net/net.cpp

HEADERS += \
        smccc.h \
        smccc_global.h \
    auth/auth.h \
    auth/yggdrasil.h \
    json/json.h \
    json/json_assets.h \
    json/json_downloads.h \
    json/json_inheritsfrom.h \
    json/json_libraries.h \
    json/json_natives.h \
    core.h \
    net/httprequest.h \
    net/net.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
