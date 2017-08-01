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
    auth/smcccauth.cpp \
    auth/smcccyggdrasil.cpp \
    json/smcccjsonassets.cpp \
    json/smcccjsondownloads.cpp \
    json/smcccjson.cpp \
    json/smcccjsonlibraries.cpp \
    json/smcccjsonnatives.cpp \
    json/smcccjsoninheritsfrom.cpp \
    net/smccchttprequest.cpp \
    net/smcccnet.cpp

HEADERS += \
        smccc.h \
        smccc_global.h \
    auth/smcccauth.h \
    auth/smcccyggdrasil.h \
    json/smcccjsonassets.h \
    json/smcccjsondownloads.h \
    json/smcccjson.h \
    json/smcccjsonlibraries.h \
    json/smcccjsonnatives.h \
    json/smcccjsoninheritsfrom.h \
    net/smccchttprequest.h \
    net/smcccnet.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
