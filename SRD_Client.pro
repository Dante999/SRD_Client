QT += core gui \
    serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#CONFIG += c++11

TARGET = SRD_Client
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    srd_client.cpp \
    config/config.cpp \
    dashboard/pixmaps/carshape.cpp \
    dashboard/pixmaps/damagemonitor.cpp \
    dashboard/pixmaps/dashboardcontent.cpp \
    dashboard/pixmaps/defaultmonitor.cpp \
    dashboard/pixmaps/textframe.cpp \
    dashboard/dashboard.cpp \
    dashboard/dashboardthread.cpp \
    serialcom.cpp

HEADERS += \
    srd_client.h \
    config/config.h \
    dashboard/pixmaps/carshape.h \
    dashboard/pixmaps/damagemonitor.h \
    dashboard/pixmaps/dashboardcontent.h \
    dashboard/pixmaps/defaultmonitor.h \
    dashboard/pixmaps/interfacemonitor.h \
    dashboard/pixmaps/settings.h \
    dashboard/pixmaps/textframe.h \
    dashboard/dashboard.h \
    dashboard/dashboardthread.h \
    clientData.h \
    serialcom.h

DISTFILES += \
    .gitattributes \
    .gitignore
