#include "register.h"
#include "ui_register.h"
#include <QSqlQuery>
#include<QDebug>
#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include "login.h"
Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_closeButton_clicked()
{
this->close();
    login Reg_Form;
    Reg_Form.setAttribute(Qt::WA_TranslucentBackground);
    Reg_Form.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    Reg_Form.exec();


//this will close the register form


}


void Register::on_registerButton_clicked()
{
    // Récupérer les données saisies dans les champs Nom, Password et Mail
    QString LOGIN = ui->userNameEdit->text();
    QString MDP= ui->passwordLineEdit->text();

    if (LOGIN.isEmpty() || MDP.isEmpty()) {

        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Veuillez remplir tous les champs.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }





    QSqlQuery query;
    query.prepare("INSERT INTO AUTHENTIFICATION (LOGIN,MDP) "
                  "VALUES (:LOGIN, :MDP)");


    query.bindValue(":LOGIN", LOGIN);
    query.bindValue(":MDP", MDP);


    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("Données insérées avec succès.\n"

                                         "Click ok to exit."), QMessageBox::Ok);



    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion : " << query.lastError().text();
    }


}


/*
void Register::on_registerButton_clicked()
{

// Récupérer les données saisies dans les champs Nom, Password et Mail
QString nom =ui->userNameEdit->text();
QString password= ui->passwordLineEdit->text();
QString mail = ui->mailLineEdit->text();

srand(time(0));

    // générer un identifiant aléatoire entre 1000 et 9999
    int random_id = rand() % 9000 + 100;

// Insérer les données dans la table "employe"
QSqlQuery query;
query.prepare("INSERT INTO EMPLOYE (id, nom, password, mail) "
              "VALUES (:id, :nom, :salaire, :ADRESSE_MAIL)");
 query.bindValue(":id", random_id);

query.bindValue(":nom", nom);
query.bindValue(":salaire", password);
query.bindValue(":ADRESSE_MAIL", mail);
if (!query.exec()) {
    qDebug() << "Erreur lors de l'insertion : " << query.lastError().text();

}*/
