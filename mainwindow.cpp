#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QTextStream>
#include <QTextDocument>
#include <QDataStream>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tab_employe->setModel(emp.afficher());
    ui->id_e->setValidator(new QIntValidator(0, 9999999, this));
    ui->salaire_e->setValidator(new QIntValidator(0, 10000, this));
    ui->id_e_2->setValidator(new QIntValidator(0, 9999999, this));
    ui->salaire_e_2->setValidator(new QIntValidator(0, 10000, this));
     ui->id_e_s->setValidator(new QIntValidator(0, 9999999, this));
     QRegExp
         regExp("^[A-Za-z]*$");
     ui->nom_e->setValidator(new QRegExpValidator(regExp, this));
     ui->prenom_e->setValidator(new QRegExpValidator(regExp, this));
     ui->nom_e_2->setValidator(new QRegExpValidator(regExp, this));
      ui->prenom_e_2->setValidator(new QRegExpValidator(regExp, this));
}







MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_e_clicked()
{
    int id=ui->id_e->text().toInt();
    ui->tab_employe->setModel(emp.afficher());
        QString nom=ui->nom_e->text();
        QString prenom=ui->prenom_e->text();
        int salaire=ui->salaire_e->text().toInt();
        QString mail=ui->mail_e->text();

        employee emp(id,nom,prenom,salaire,mail);
        bool test=emp.ajouter();
        if(test)
       {
            ui->tab_employe->setModel(emp.afficher());

          QMessageBox::information(nullptr, QObject::tr("ok"),
          QObject::tr("ajout effectuee.\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);


       }
        else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("ajout non effectue.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_supprimer_e_clicked()
{ employee emp;
    int id =ui->id_e_s->text().toInt();
       bool test=emp.supprimer(id);
       if(test)
      {
                       ui->tab_employe->setModel(emp.afficher());

         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectue.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectue.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_UPDATE_clicked()
{

    int id=ui->id_e_2->text().toInt();

        QString nom=ui->nom_e_2->text();
        QString prenom=ui->prenom_e_2->text();
        int salaire=ui->salaire_e_2->text().toInt();
        QString mail=ui->mail_e_2->text();
        QString id_string=QString::number(id);
        QString sal_string=QString::number(salaire);

    QSqlQuery quer;
        quer.prepare("update EMPLOYE set ID_EMPLOYE='"+id_string+"', NOM='"+nom+"',PRENOM='"+prenom+"',SALAIRE='"+sal_string+"',   ADRESSE_MAIL='"+mail+"' WHERE ID_EMPLOYE='"+id_string+"'");
        if(quer.exec())
        {
           ui->tab_employe->setModel(emp.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"), QObject::tr("modification effectué \n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("not OK"),  QObject::tr("modification non effectué \n"  "Click Cancel to exit."),QMessageBox::Cancel);
}

