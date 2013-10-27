QT += network \
    xml
TARGET = whoIsUp
TEMPLATE = app
SOURCES += main.cpp \
    porttester.cpp \
    oneporttester.cpp \
    host.cpp \
    service.cpp \
    configurationreader.cpp \
    orporttester.cpp \
    porttesterset.cpp \
    andporttester.cpp \
    floatingservicesmodel.cpp \
    fixedservicesmodel.cpp \
    servicesmodel.cpp \
    serviceswidget.cpp \
    servicestabwidget.cpp
HEADERS += porttester.h \
    oneporttester.h \
    host.h \
    service.h \
    configurationreader.h \
    orporttester.h \
    porttesterset.h \
    andporttester.h \
    floatingservicesmodel.h \
    fixedservicesmodel.h \
    servicesmodel.h \
    serviceswidget.h \
    servicestabwidget.h
FORMS += serviceswidget.ui
