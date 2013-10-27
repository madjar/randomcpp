QT += network
QT -= gui
TARGET = bruteRace
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    wikipage.cpp \
    wikicrawler.cpp
HEADERS += wikipage.h \
    wikicrawler.h
