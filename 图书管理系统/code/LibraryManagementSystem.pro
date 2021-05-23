QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcard.cpp \
    admingui.cpp \
    authentication.cpp \
    borrowbook.cpp \
    connectdatabase.cpp \
    insertbook.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    manageuser.cpp \
    register.cpp \
    returnbook.cpp \
    usersearchbook.cpp

HEADERS += \
    addcard.h \
    admingui.h \
    authentication.h \
    borrowbook.h \
    connectdatabase.h \
    insertbook.h \
    login.h \
    mainwindow.h \
    manageuser.h \
    register.h \
    returnbook.h \
    usersearchbook.h

FORMS += \
    addcard.ui \
    admingui.ui \
    authentication.ui \
    borrowbook.ui \
    insertbook.ui \
    login.ui \
    mainwindow.ui \
    manageuser.ui \
    register.ui \
    returnbook.ui \
    usersearchbook.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagesrc.qrc
