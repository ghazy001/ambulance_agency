#include "ambulance.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QObject>

ambulance::ambulance(){
    matricule=0;
    marque=" ";
    Modele=" ";
    etat=" ";
    KM=0;

}
ambulance::ambulance(int matricule,QString marque,QString Modele ,QString etat,int KM){
    this->matricule=matricule;
    this->marque=marque;
    this->Modele=Modele;
    this->etat=etat;
    this->KM=KM;

}
int ambulance::getmatricule(){
    return matricule;
}
QString ambulance::getmarque(){
    return marque;
}
QString ambulance::getmodele(){
    return Modele;
}
QString ambulance::getetat(){
    return etat;
}

int ambulance::getkm(){
    return KM;
}

void ambulance::setmatricule(int matricule){
    this->matricule=matricule;
}
void ambulance::setmodele(QString Modele){
    this->Modele=Modele;

}
void ambulance::setmarque(QString marque){
    this->marque=marque;

}
void ambulance::setkm(int KM){
    this->KM=KM;
}
void ambulance::setetat(QString etat){
    this->etat=etat;
}

bool ambulance::ajouter(){

    QSqlQuery query;
    QString matricule_string=QString::number(matricule);
    QString km_string=QString::number(KM);
    query.prepare("INSERT INTO AMBULANCE (MATRICULE, MARQUE, MODELE, ETAT, KILOMETRAGE) "
                  "VALUES (:matricule, :marque, :Modele, :etat, :KM)");
    query.bindValue(":matricule", matricule_string);
    query.bindValue(":marque", marque);
    query.bindValue(":Modele", Modele);
    query.bindValue(":etat", etat);
    query.bindValue(":KM", km_string);


    return query.exec();
}


bool ambulance::supprimer(int matricule){
    QSqlQuery query;
    query.prepare("DELETE FROM AMBULANCE WHERE MATRICULE=:matricule ");
    query.bindValue(":matricule", matricule);

    return query.exec();

}





QSqlQueryModel * ambulance::afficher(){


    QSqlQueryModel *model =new QSqlQueryModel();


          model->setQuery("SELECT * FROM AMBULANCE");
      /*    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Modele"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Kilometrage"));


*/

    return model;
}

bool ambulance::existance(QString id)
{
    QMessageBox msgBox;
    QSqlQuery query;
    int count=0;
    query.prepare("SELECT * FROM AMBULANCE WHERE MATRICULE= ?");
    query.addBindValue(id);
    if(query.exec() )
    {
        while (query.next())
        {
            count ++;
        }
        if(count>=1)
        {
            msgBox.setText("matricule deja existe");
            msgBox.exec();
            return 1;
        }

    }
    return 0;
}














