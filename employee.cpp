#include "employee.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QString>
employee::employee()
{id=0;
 nom="";
 prenom="";
 salaire=0;
 mail="";
}

employee::employee(int id,QString nom, QString prenom, int salaire, QString mail)
{
 this->id=id;
this->nom=nom;
this->prenom=prenom;
this->salaire=salaire;
this->mail=mail;

}
int employee::getid(){return id;}
QString employee::getnom(){return nom;}
QString employee::getprenom(){return prenom;}
int employee::getsal(){return salaire;}
QString employee::getmail(){return mail;}

void employee::setid(int id){this->id=id;};
void employee::setnom(QString nom){this->nom=nom;}
void employee::setprenom(QString prenom){this->prenom=prenom;}
void employee::setsal(int salaire){this->salaire=salaire;}
void employee::setmail(QString mail){this->mail=mail;}


QSqlQueryModel* employee::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT* FROM Employe");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));


return model;

}

bool employee::ajouter()
{
    QSqlQuery query;
    QString num_string= QString::number(id);
    QString salstring=QString::number(salaire);
         query.prepare("INSERT INTO Employe (ID_EMPLOYE, NOM, PRENOM, SALAIRE, adresse_mail) "
                       "VALUES (:id, :forename, :surname, :salaire,:mail)");
         query.bindValue(":id", num_string);
         query.bindValue(":forename", nom);
         query.bindValue(":surname", prenom);
         query.bindValue(":salaire", salstring);
         query.bindValue(":mail", mail);

         return query.exec();

}
bool employee::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from Employe where ID_EMPLOYE= :id");
    query.bindValue(":id",res);
    return query.exec();
}

bool employee::modifier(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString sal_string=QString::number(salaire);

    query.prepare("update EMPLOYE set ID_EMPLOYE='"+id_string+"', NOM='"+nom+"',PRENOM='"+prenom+"',SALAIRE='"+sal_string+"',   ADRESSE_MAIL='"+mail+"' WHERE ID_EMPLOYE='"+id_string+"'");
    query.bindValue(":id", id_string);
    query.bindValue(":forename", nom);
    query.bindValue(":surname", prenom);
    query.bindValue(":salaire",sal_string );
    query.bindValue(":mail", mail);



          return    query.exec();
}

QSqlQueryModel * employee::recherche(QString id )  /*cherche un producteur de meme id*/
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM EMPLOYE WHERE  ID_EMPLOYE LIKE '" + id + "' ");


    return model;
}



QSqlQueryModel * employee::tri_N_Passeport()
   {QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("select * from EMPLOYE order by ID_EMPLOYE");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));

       return model;
   }

