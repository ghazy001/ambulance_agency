#include "authentification.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QString>
#include <QSqlRecord>
#include <QSqlField>
#include <QLineEdit>
#include"ui_mainwindow.h"
#include "mainwindow.h"

authentification::authentification()
{
 LOGIN="";
 MDP="";

}

authentification::authentification(QString LOGIN, QString MDP)
{
 this->LOGIN=LOGIN;
this->MDP=MDP;


}
QString authentification::getLOGIN(){return LOGIN;}
QString authentification::getMDP(){return MDP;}


void authentification::setLOGIN(QString LOGIN){this->LOGIN=LOGIN;};
void authentification::setMDP(QString MDP){this->MDP=MDP;}


QSqlQueryModel* authentification::afficher1()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT* FROM AUTHENTIFICATION");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("LOGIN"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("MDP"));


return model;

}
bool authentification::supprimer1(QString LOGIN)
{
    QSqlQuery query;

    query.prepare("Delete from AUTHENTIFICATION where LOGIN= :LOGIN");
    query.bindValue(":LOGIN",LOGIN);
    return query.exec();
}


/*
QSqlQueryModel* authentification::afficher1()
{QSqlQueryModel* model = new QSqlQueryModel();

    // Récupération des données de la table AUTHENTIFICATION
    model->setQuery("SELECT LOGIN, MDP FROM AUTHENTIFICATION");

    // Masquer la colonne contenant les mots de passe
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("LOGIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MDP"));
    model->setHeaderData(1, Qt::Horizontal, Qt::ItemIsEnabled); // Empêcher l'édition de la colonne

    // Afficher les étoiles dans la colonne MDP
    for (int i = 0; i < model->rowCount(); i++) {
        QModelIndex index = model->index(i, 1);
        QString password = model->data(index, Qt::DisplayRole).toString();
        model->setData(index, QString(password.length(), '*'), Qt::DisplayRole);
        model->setData(index, password, Qt::EditRole);
    }

   // Masquer le mot de passe dans l'affichage
    for(int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex index = model->index(i, 1); // Récupérer l'index de la colonne MDP
        model->setData(index, QString("*").repeated(index.data().toString().size()), Qt::DisplayRole); // Remplacer le mot de passe par des points
    }

    return model;
    }*/

bool authentification::ajouter()
{
    QSqlQuery query;


         query.prepare("INSERT INTO AUTHENTIFICATION (LOGIN, MDP) "
                       "VALUES (:LOGIN, :MDP)");
         query.bindValue(":LOGIN",LOGIN);
         query.bindValue(":MDP", MDP);

         return query.exec();

}
