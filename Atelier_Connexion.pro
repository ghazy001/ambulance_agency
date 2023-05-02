#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql quick printsupport  widgets multimedia serialport charts svg

QT       += core gui serialport
QT       += sql
QT       += multimedia
QT       += printsupport
QT       += multimediawidgets charts printsupport widgets axcontainer network
QT       +=network
QT       += charts
QT       +=  sql charts printsupport network
QT += network

INCLUDEPATH += C:\Program Files\OpenSSL-Win64\include
LIBS += -LC:\Users\malek\Desktop\integ -lssleay32 -llibeay32



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

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

CONFIG += c++11 sql

SOURCES += \
    NotificationLayout.cpp \
    NotificationWidget.cpp \
    Operation.cpp \
    QrCode.cpp \
    Result.cpp \
    ambulance.cpp \
    arduino.cpp \
    authentification.cpp \
    employee.cpp \
   equipement.cpp \
    gestionambulance.cpp \
    gestionemploye.cpp \
    gestionpatient.cpp \
    login.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    menu.cpp \
    patient.cpp \
    register.cpp \
    smtp.cpp

HEADERS += \
    NotificationLayout.h \
    NotificationWidget.h \
    Operation.h \
    QrCode.hpp \
    Result.h \
    ambulance.h \
    arduino.h \
    authentification.h \
    employee.h \
     equipement.h \
   gestionambulance.h \
    gestionemploye.h \
    gestionpatient.h \
    login.h \
        mainwindow.h \
    connection.h \
    menu.h \
    patient.h \
    register.h \
    smtp.h

FORMS += \
        gestionambulance.ui \
        gestionemploye.ui \
        gestionpatient.ui \
        login.ui \
        mainwindow.ui \
        menu.ui \
        register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    cr7.qrc \
    cr7.qrc \
    logo.qrc \
    src.qrc \
    src7.qrc

DISTFILES += \
    icons/Capture d’écran 2023-04-02 215328.png \
    icons/lock_32x32.png \
    icons/logo.png \
    icons/mail_32x32.png \
    icons/rocket_48x48.png \
    icons/signature.png \
    icons/smart-ambulance-cartoon-character-design-playing-vector-32647342-removebg-preview (1).png \
    icons/user_32x32.png
