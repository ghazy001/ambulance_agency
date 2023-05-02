#ifndef LOGIN_H
#define LOGIN_H
#include "employee.h"
#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QMainWindow>

#include <QWidget>
#include <QDialog>
#include"menu.h"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();


private slots:
    void on_closeButton_clicked();

    void on_signInButton_clicked();

    void on_registerButton_clicked();



private:
    Ui::login *ui;

    menu *ma;
    QSqlDatabase mydb;

    QByteArray data;

};

#endif // LOGIN_H

