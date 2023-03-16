#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement.h"
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
    ui->tab_equipement->setModel(eq.afficher());
    ui->id_e->setValidator(new QIntValidator(0, 9999999, this));
    ui->code_e->setValidator(new QIntValidator(0, 9999999, this));
    ui->prix_e->setValidator(new QIntValidator(0, 10000, this));
    ui->id_e_2->setValidator(new QIntValidator(0, 9999999, this));
    ui->code_e_2->setValidator(new QIntValidator(0, 9999999, this));
    ui->prix_e_2->setValidator(new QIntValidator(0, 10000, this));
    QRegExp
    regExp("^[A-Za-z]*$");
    ui->nom_e->setValidator(new QRegExpValidator(regExp, this));
    ui->nom_e_2->setValidator(new QRegExpValidator(regExp, this));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_e_clicked()
{
    int id_equipement=ui->id_e->text().toInt();
    ui->tab_equipement->setModel(eq.afficher());
      int code_QR=ui->code_e->text().toInt();
        QString reference=ui->ref_e->text();
       int prix=ui->prix_e->text().toInt();
        QString nom_equipement=ui->nom_e->text();

        equipement eq(id_equipement,code_QR,reference,prix,nom_equipement);
        bool test=eq.ajouter();
        if(test)
       {
            ui->tab_equipement->setModel(eq.afficher());

          QMessageBox::information(nullptr, QObject::tr("oui"),
          QObject::tr("ajout effectuee.\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);


       }
        else
         QMessageBox::critical(nullptr, QObject::tr("non"),
         QObject::tr("ajout non effectuee.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_supprimer_e_clicked()
{ equipement eq;
    int id_equipement =ui->id_e_s->text().toInt();
       bool test=eq.supprimer(id_equipement);
       if(test)
      {
                       ui->tab_equipement->setModel(eq.afficher());

         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectue.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectue.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_pushButton_2_clicked()
{int id_equipement=ui->id_e_2->text().toInt();

    int code_QR=ui->code_e_2->text().toInt();
    QString reference=ui->ref_e_2->text();
    int prix=ui->prix_e_2->text().toInt();
    QString nom_equipement=ui->nom_e_2->text();
    QString id_string = QString::number(id_equipement) ;
    QString code_string = QString::number(code_QR) ;
    QString prix_string = QString::number(prix) ;


QSqlQuery quer;
    quer.prepare("update EQUIPEMENT set ID_EQUIPEMENT='"+id_string+"', CODE_QR='"+code_string+"',REFERENCE='"+reference+"',PRIX='"+prix_string+"',   NOM_EQUIPEMENT='"+nom_equipement+"' WHERE ID_EQUIPEMENT='"+id_string+"'");
    if(quer.exec())
    {
        ui->tab_equipement->setModel(eq.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"), QObject::tr("modification effectué \n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not OK"),  QObject::tr("modification non effectué \n"  "Click Cancel to exit."),QMessageBox::Cancel);



}
