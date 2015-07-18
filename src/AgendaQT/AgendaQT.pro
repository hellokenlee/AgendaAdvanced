#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T17:53:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AgendaQT
TEMPLATE = app

SOURCES += main.cpp\
                       mainwindow.cpp\
                        classes/client.cpp\
                        classes/Date.cpp\
                        classes/Meeting.cpp\
                        classes/User.cpp
HEADERS  += mainwindow.h\
                        classes/client.h\
                        classes/Date.h\
                        classes/Meeting.h\
                        classes/User.h


FORMS    += mainwindow.ui

INCLUDEPATH +=E:/boost_1_55_0
LIBS += E:/boost_1_55_0/stage/lib/libboost_system-vc110-mt-gd-1_55.lib \
        E:/boost_1_55_0/stage/lib/libboost_filesystem-vc110-mt-gd-1_55.lib\
        E:/boost_1_55_0/stage/lib/libboost_thread-vc110-mt-gd-1_55.lib\
        E:/boost_1_55_0/stage/lib/libboost_date_time-vc110-mt-gd-1_55.lib\
        E:/boost_1_55_0/stage/lib/libboost_regex-vc110-mt-gd-1_55.lib\
        E:/boost_1_55_0/stage/lib/libboost_chrono-vc110-mt-gd-1_55.lib

RESOURCES += \
    logo.qrc
