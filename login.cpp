#include "login.h"
#include "ui_login.h"
#include <QSqlQueryModel>
#include "employee.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "authentification.h"
#include "connection.h"
#include "register.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include"menu.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
       ui->male->setText(E.CaptchaGenerator());
}

login::~login()
{
    delete ui;
}



void login::on_registerButton_clicked()

{
    //this will show the register form
    this->close();
    Register Reg_Form;
    Reg_Form.setAttribute(Qt::WA_TranslucentBackground);
    Reg_Form.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    Reg_Form.exec();

}






/*void login::on_signInButton_clicked()
{
QMessageBox::information(this, "Login", "Username and password is correct");
         ma = new MainWindow(this);
         ma->show();


}
*/


void login::on_closeButton_clicked()
{
    this->close();
}






void login::on_signInButton_clicked()
{

        // Récupérer les données saisies dans les champs de l'interface
        QString LOGIN = ui->userLineEdit->text();
        QString MDP = ui->passwordlineEdit->text();
        if (LOGIN.isEmpty() || MDP.isEmpty() ) {
            qDebug() << "Veuillez remplir tous les champs.";}

        QSqlQuery qry;

        if (qry.exec("SELECT * FROM AUTHENTIFICATION WHERE LOGIN='"+LOGIN+"'AND MDP='"+MDP+"'")) {
            qry.bindValue(":LOGIN", LOGIN);
            qry.bindValue(":MDP",MDP);
            if (qry.next() and (ui->stela->text() == ui->male->text() ))

            {

                            QMessageBox::information(this, "CAPTCHA Verification", "CAPTCHA verified");
                              ui->male->setText(E.CaptchaGenerator());
                               ui->stela->clear();





                               QMessageBox::information(this, "Connexion réussie", "Bienvenue, " + LOGIN + " !");

                               ma = new menu(this);

                               ma->show();
            }




            else if ((ui->stela->text() != ui->male->text() ) and qry.next()  )
            {



                   QMessageBox::warning(this, "CAPTCHA Verification", "CAPTCHA verification failed");



                   ui->stela->clear();

                   ui->male->setText(E.CaptchaGenerator());


                }



            else if (!qry.next() and (ui->stela->text() != ui->male->text() ) )
            {
                QMessageBox::critical(this, "Erreur de connexion", "Nom d'utilisateur ou salaire incorrect.");


                   QMessageBox::warning(this, "CAPTCHA Verification", "CAPTCHA verification failed");



                   ui->stela->clear();

                   ui->male->setText(E.CaptchaGenerator());


                }




            else if (!qry.next() and (ui->stela->text() == ui->male->text() ) )
            {
                QMessageBox::critical(this, "Erreur de connexion", "Nom d'utilisateur ou salaire incorrect.");


                   ui->male->setText(E.CaptchaGenerator());
                   ui->stela->clear();


                }




        }




        }









