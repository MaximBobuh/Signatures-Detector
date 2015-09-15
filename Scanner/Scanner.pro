#-------------------------------------------------
#
# Project created by QtCreator 2015-09-12T18:35:36
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = Scanner
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    scanner.cpp \
    server.cpp

HEADERS += \
    scanner.h \
    server.h
