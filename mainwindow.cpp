#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hopitaux.h"
#include "connection.h"
#include <QApplication>
#include <QValidator>
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id_hopital->setValidator(new QIntValidator(0,9999999,this));
    ui->capacite->setValidator(new QIntValidator(0,9999999,this));
    ui->id_hopital_2->setValidator(new QIntValidator(0,9999999,this));
    ui->id_hopital_3->setValidator(new QIntValidator(0,9999999,this));
    ui->capacite_2 ->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_hopitaux->setModel(H.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_boutton_ajouter_clicked()
{
    int id_hopital=ui->id_hopital->text().toInt();
    QString nom_hopital=ui->nom_hopital->text();
    QString adresse=ui->adresse->text();
    int capacite=ui->capacite->text().toInt();
    Hopitaux H(id_hopital,nom_hopital,adresse,capacite);

    bool test=H.ajouter();

    if(test)
    {
        ui->tab_hopitaux->setModel(H.afficher());
        QMessageBox::information(nullptr, QObject::tr("Succée"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_boutton_supprimer_clicked()
{
    int id_hopital=ui->id_hopital_2->text().toInt();
    bool test=H.supprimer(id_hopital);
    if(test)
    {
        ui->tab_hopitaux->setModel(H.afficher());
        QMessageBox::information(nullptr, QObject::tr("Succée"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_boutton_modifier_clicked()
{


        int id_hopital =ui->id_hopital_3->text().toInt();
        QString nom=ui->nom_hopital_2->text();
        QString adresse=ui->adresse_2->text();
        int capacite=ui->capacite_2->text().toInt();


        QString id_hop= QString::number(id_hopital);
        QString capa= QString::number(capacite);



        QSqlQuery quer;
        quer.prepare("update HOPITAUX set ID_HOPITAUX='"+id_hop+"', NOM='"+nom+"',ADRESSE='"+adresse+"',CAPACITE='"+capa+"'");
        if(quer.exec())
        {
            ui->tab_hopitaux->setModel(H.afficher());
            QMessageBox::information(nullptr,QObject::tr("Succée"), QObject::tr("Modification effectué \n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Echec"),  QObject::tr("Modification non effectué \n"  "Click Cancel to exit."),QMessageBox::Cancel);


}

