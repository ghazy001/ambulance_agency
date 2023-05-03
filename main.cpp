#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "menu.h"
#include "login.h"

#include <QGuiApplication>
#include <QQuickView>
#include <QDebug>
#include "hopitaux.h"
#include "dumessengerserver.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Connection c;
    bool test=c.createconnect();

login l;
    menu w;

    l.setAttribute(Qt::WA_TranslucentBackground);
    l.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


    if(test)
    {l.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    DuMessengerServer Server;
    if (!Server.startServer(3333)) {
        qDebug() << "ERROR:" << Server.errorString();
        return 1;
    }
    qDebug() << "Server started...";

    return a.exec();
}
