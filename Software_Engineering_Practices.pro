QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminscreen.cpp \
    checkininfo.cpp \
    customscreen.cpp \
    houseresource.cpp \
    main.cpp \
    loginscreen.cpp \
    registerscreen.cpp \
    reservation.cpp \
    screenmanager.cpp \
    sellerscreen.cpp \
    sqlmanager.cpp \
    transaction.cpp \
    users.cpp \
    wage.cpp

HEADERS += \
    adminscreen.h \
    checkininfo.h \
    customscreen.h \
    houseresource.h \
    loginscreen.h \
    registerscreen.h \
    reservation.h \
    screenmanager.h \
    sellerscreen.h \
    sqlmanager.h \
    transaction.h \
    users.h \
    wage.h

FORMS += \
    adminscreen.ui \
    customscreen.ui \
    loginscreen.ui \
    registerscreen.ui \
    sellerscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
