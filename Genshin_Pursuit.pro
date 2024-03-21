QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrow.cpp \
    hotel.cpp \
    introduction.cpp \
    main.cpp \
    maincharacter.cpp \
    mainscene.cpp \
    myequipment.cpp \
    qqking.cpp \
    qqren.cpp \
    scene01.cpp \
    scene02.cpp \
    scene03.cpp \
    startscene.cpp \
    choosescene.cpp \
    syfs.cpp

HEADERS += \
    arrow.h \
    hotel.h \
    introduction.h \
    maincharacter.h \
    mainscene.h \
    myequipment.h \
    qqking.h \
    qqren.h \
    scene01.h \
    scene02.h \
    scene03.h \
    startscene.h \
    choosescene.h \
    syfs.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    linny.qrc






