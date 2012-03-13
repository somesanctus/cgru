######################################################################
# Automatically generated by qmake (2.01a) ?? 22. ??? 01:28:40 2009
######################################################################

TEMPLATE = app
QT += network xml
TARGET = afmonitor
DEPENDPATH += . src
INCLUDEPATH += ../include \
                ../libafanasy/src \
                ../libafqt/src \
                ./src 
DESTDIR = ../../../afanasy/bin
DEFINES += WINNT
LIBPATH += ../../../afanasy/bin \
            $(PYTHONPATH)/libs
LIBS += afanasy.lib afqt.lib wsock32.lib
# Input
HEADERS += src/itemjob.h \
           src/itemnode.h \
           src/itemrender.h \
           src/itemuser.h \
           src/listjobs.h \
           src/listnodes.h \
           src/listrenders.h \
           src/listusers.h \
           src/monitorhost.h \
           src/monitorwindow.h
SOURCES += src/itemjob.cpp \
           src/itemnode.cpp \
           src/itemrender.cpp \
           src/itemuser.cpp \
           src/listjobs.cpp \
           src/listnodes.cpp \
           src/listrenders.cpp \
           src/listusers.cpp \
           src/main.cpp \
           src/monitorhost.cpp \
           src/monitorwindow.cpp
