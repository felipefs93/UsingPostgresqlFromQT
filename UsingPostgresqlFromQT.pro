QT += core sql
QT -= gui

CONFIG += c++11

TARGET = UsingPostgresqlFromQT
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    qsqldbhelper.cpp

HEADERS += \
    qsqldbhelper.h
