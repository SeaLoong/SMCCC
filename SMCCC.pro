#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T20:54:43
#
#-------------------------------------------------

QT       += network
QT       -= gui

CONFIG += c++11
TARGET = SMCCC
TEMPLATE = lib

DEFINES += SMCCC_LIBRARY
DEFINES += QUAZIP_BUILD

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
    smcccauth.cpp \
    smcccyggdrasil.cpp \
    smcccjsonassets.cpp \
    smcccjsondownloads.cpp \
    smcccjson.cpp \
    smcccjsonlibraries.cpp \
    smcccjsonnatives.cpp \
    smcccjsoninheritsfrom.cpp \
    smccchttprequest.cpp \
    smcccnet.cpp \
    smcccdownloadinfo.cpp \
    quazip/JlCompress.cpp \
    quazip/qioapi.cpp \
    quazip/quaadler32.cpp \
    quazip/quacrc32.cpp \
    quazip/quagzipfile.cpp \
    quazip/quaziodevice.cpp \
    quazip/quazip.cpp \
    quazip/quazipdir.cpp \
    quazip/quazipfile.cpp \
    quazip/quazipfileinfo.cpp \
    quazip/quazipnewinfo.cpp \
    quazip/unzip.c \
    quazip/zip.c

HEADERS += \
        smccc.h \
        smccc_global.h \
    smcccauth.h \
    smcccyggdrasil.h \
    smcccjsonassets.h \
    smcccjsondownloads.h \
    smcccjson.h \
    smcccjsonlibraries.h \
    smcccjsonnatives.h \
    smcccjsoninheritsfrom.h \
    smccchttprequest.h \
    smcccnet.h \
    smcccdownloadinfo.h \
    quazip/crypt.h \
    quazip/ioapi.h \
    quazip/JlCompress.h \
    quazip/quaadler32.h \
    quazip/quachecksum32.h \
    quazip/quacrc32.h \
    quazip/quagzipfile.h \
    quazip/quaziodevice.h \
    quazip/quazip.h \
    quazip/quazip_global.h \
    quazip/quazipdir.h \
    quazip/quazipfile.h \
    quazip/quazipfileinfo.h \
    quazip/quazipnewinfo.h \
    quazip/unzip.h \
    quazip/zip.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32: LIBS += -L$$PWD/quazip/zlib/lib/ -lz

INCLUDEPATH += $$PWD/quazip/zlib/include
DEPENDPATH += $$PWD/quazip/zlib/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/quazip/zlib/lib/zlib.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/quazip/zlib/lib/libz.a

