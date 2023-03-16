#include "hopitaux.h"
#include "mainwindow.h"
#include "connection.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QObject>
Hopitaux::Hopitaux()
{
id_hopital=0,nom_hopital=" ",adresse=" ",capacite=0;
}

Hopitaux::Hopitaux(int id_hopital,QString nom_hopital,QString adresse,int capacite)
{
    this->id_hopital=id_hopital;
    this->nom_hopital=nom_hopital;
    this->adresse=adresse;
    this->capacite=capacite;
}
int Hopitaux::getid_hopital()
{
    return id_hopital;
}
QString Hopitaux::getnom_hopital()
{
    return nom_hopital;
}
QString Hopitaux::getadresse()
{
    return adresse;
}
int Hopitaux::getcapacite()
{
    return capacite;
}
void Hopitaux::setid_hopital(int id_hopital)
{
    this->id_hopital=id_hopital;
}
void Hopitaux::setnom_hopital(QString nom_hopital)
{
    this->nom_hopital=nom_hopital;
}
void Hopitaux::setadresse(QString adresse)
{
    this->adresse=adresse;
}
void Hopitaux::setcapacite(int capacite)
{
    this->capacite=capacite;
}
bool Hopitaux::ajouter()
{
    QSqlQuery query;
    QString id_string= QString::number(id_hopital);
    QString cap= QString::number(capacite);
          query.prepare("INSERT INTO RAYANN.HOPITAUX (ID_HOPITAUX, NOM, ADRESSE, CAPACITE) " "VALUES (:id_hopital, :nom_hopital, :adresse, :capacite)");
          query.bindValue(":id_hopital", id_string);
          query.bindValue(":nom_hopital", nom_hopital);
          query.bindValue(":adresse", adresse);
          query.bindValue(":capacite", cap);


          return query.exec();



}
bool Hopitaux::supprimer(int id_hopital)
{
    QSqlQuery query;
    QString res=QString::number(id_hopital);
    query.prepare("Delete from hopitaux where ID_HOPITAUX= :id_hopital");
    query.bindValue(":id_hopital",res);

    return query.exec();
}
QSqlQueryModel * Hopitaux::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM HOPITAUX");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID Hopital"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Capacite"));

    return model;
}
