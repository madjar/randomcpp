
QT += network
TEMPLATE = app

HEADERS += \
    trombi.h \
    entry.h \
    networkaccessmanager.h \
    popchecker.h

SOURCES += \
    trombi.cpp \
    entry.cpp \
    networkaccessmanager.cpp \
    main.cpp \
    popchecker.cpp

include(../libgarbage/libgarbage.pri)
