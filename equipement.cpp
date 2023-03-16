#include "equipement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QString>
equipement::equipement()
{id_equipement=0;
    code_QR=0;
    reference="";
    prix=0;
    nom_equipement="";

}
equipement::equipement(int id_equipement,int code_QR, QString reference, int prix, QString nom_equipement)
{
 this->id_equipement=id_equipement;
this->code_QR=code_QR;
this->reference=reference;
this->prix=prix;
this->nom_equipement=nom_equipement;

}
int equipement::getid_equipement(){return id_equipement;}
int equipement::getcode_QR(){return code_QR;}
QString equipement::getreference(){return reference;}
int equipement::getprix(){return prix;}
QString equipement::getnom_equipement(){return nom_equipement;}

void equipement::setid_equipement(int id_equipement){this->id_equipement=id_equipement;};
void equipement::setcode_QR(int code_QR){this->code_QR=code_QR;}
void equipement::setreference(QString reference){this->reference=reference;}
void equipement::setprix(int prix){this->prix=prix;}
void equipement::setnom_equipement(QString nom_equipement){this->nom_equipement=nom_equipement;}
QSqlQueryModel* equipement::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT* FROM equipement");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_equipement"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("code_QR"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom_equipement"));


return model;

}
bool equipement::ajouter()
{
    QSqlQuery query;
    QString num_string= QString::number(id_equipement);
         query.prepare("INSERT INTO Equipement (id_equipement,code_QR, reference, prix, nom_equipement) "
                       "VALUES (:id_equipement, :code_QR, :reference, :prix,:nom_equipement)");
         query.bindValue(":id_equipement", num_string);
         query.bindValue(":code_QR", code_QR);
         query.bindValue(":reference", reference);
         query.bindValue(":prix", prix);
         query.bindValue(":nom_equipement", nom_equipement);

         return query.exec();

}
bool equipement::supprimer(int id_equipement)
{
    QSqlQuery query;
    QString res=QString::number(id_equipement);
    query.prepare("Delete from equipement where id_equipement= :id_equipement");
    query.bindValue(":id_equipement",res);
    return query.exec();
}

