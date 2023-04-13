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


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
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
            if (qry.next()) {
                QMessageBox::information(this, "Connexion réussie", "Bienvenue, " + LOGIN + " !");
                ma = new MainWindow(this);
                ma->show();
            } else {
                QMessageBox::critical(this, "Erreur de connexion", "Nom d'utilisateur ou salaire incorrect.");
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête.");
        }

      }

