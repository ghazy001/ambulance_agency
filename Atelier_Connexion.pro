#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       +=  sql charts printsupport network
QT += network

INCLUDEPATH += C:\Program Files\OpenSSL-Win64\include
LIBS += -LC:\Users\zeddi\OneDrive\Bureau\final\aa -lssleay32 -llibeay32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    authentification.cpp \
    employee.cpp \
    login.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    register.cpp \
    smtp.cpp

HEADERS += \
    authentification.h \
    employee.h \
    login.h \
        mainwindow.h \
    connection.h \
    register.h \
    smtp.h

FORMS += \
        login.ui \
        mainwindow.ui \
        register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    logo.qrc


