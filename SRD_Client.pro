QT += core
QT -= gui

CONFIG += c++11

TARGET = SRD_Client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    srd_client.cpp \
    config/config.cpp

HEADERS += \
    srd_client.h \
    config/config.h

DISTFILES += \
    .gitattributes \
    .gitignore
