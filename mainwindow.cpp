#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ambulance.h"
#include <QValidator>
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->matricule1->setValidator(new QIntValidator(0,999999,this));
   ui->km->setValidator(new QIntValidator(0,999999,this));
   //ui->matricule_supp->setValidator(new QIntValidator(0,999999,this));
   ui->tab_ambulance->setModel(A.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_insertButton_2_clicked()
{
    QMessageBox msgBox;
    int matricule=ui->matricule1->text().toInt();
    QString marque=ui->marque->text();
    QString Modele=ui->modele->currentText();
    QString etat=ui->etat->currentText();
    int KM=ui->km->text().toInt();
    QString matricule_string=QString::number(matricule);
  if (!A.existance(matricule_string)){
   ambulance A( matricule,marque,Modele,etat,KM);

   bool test=A.ajouter();

   if( test){
       msgBox.setText("Informations has been added");
       ui->tab_ambulance->setModel(A.afficher());
             msgBox.exec();
   } }
   else {
       msgBox.setText("Informations has been failed");
             msgBox.exec();
   }


}

void MainWindow::on_deleteButton_clicked()
{
ambulance A1;
A1.setmatricule(ui->matricule1->text().toInt());

bool test=A1.supprimer(A1.getmatricule());
QMessageBox msgBox;
if( test){
    msgBox.setText("Removed");
    ui->tab_ambulance->setModel(A.afficher());
         msgBox.exec();
}
else {
    msgBox.setText("Failed");
          msgBox.exec();
}
}

void MainWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://wa.me/+21626864405",QUrl::TolerantMode));
}



void MainWindow::on_pushButton_2_clicked()
{
    //Update

    int matricule=ui->matricule1->text().toInt();
    QString marque=ui->marque->text();
    QString Modele=ui->modele->currentText();
    QString etat=ui->etat->currentText();
    int KM=ui->km->text().toInt();

    QString matricule_string=QString::number(matricule);
    QString km_string=QString::number(KM);

        QSqlQuery quer;
        quer.prepare("update AMBULANCE set MATRICULE='"+matricule_string+"', MARQUE='"+marque+"',MODELE='"+Modele+"',KILOMETRAGE='"+km_string+"',   ETAT='"+etat+"' WHERE MATRICULE='"+matricule_string+"' ");
        if(quer.exec())
        {
            ui->tab_ambulance->setModel(A.afficher());
            QMessageBox::information(nullptr,QObject::tr("OK"), QObject::tr("modification effectué \n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("not OK"),  QObject::tr("modification non effectué \n"  "Click Cancel to exit."),QMessageBox::Cancel);

    }




void MainWindow::on_tab_ambulance_clicked(const QModelIndex &index)
//£££££££
{
    int val=ui->tab_ambulance->model()->data(index).toInt();
    QString val_string=QString::number(val);
        QSqlQuery qry;

        qry.prepare("select * from AMBULANCE where MATRICULE=:v ");
        qry.bindValue(":v",val_string);
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->matricule1->setText(qry.value(0).toString());
                ui->marque->setText(qry.value(1).toString());
                ui->modele->setCurrentText(qry.value(2).toString());
                ui->km->setText(qry.value(3).toString());
                ui->etat->setCurrentText(qry.value(4).toString());

            }

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
}
