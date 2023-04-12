#include "patient.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QObject>


#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include <QtCore/QDateTime>

#include <QString>
#include <string>


#include "patient.h"

#include <cstdlib>
#include <ctime>




Patient::Patient(){
id_patient=0;
nom="_";
prenom="_";
adresse="_";
num_tel=0;
mail="_";
}

 Patient::Patient(int id_patient, QString nom ,QString prenom,QString adresse,int num_tel,QString mail)
 {
     this->id_patient=id_patient;
     this->nom=nom;
     this->prenom=prenom;
     this->adresse=adresse;
     this->num_tel=num_tel;
     this->mail=mail;

 }




 bool Patient::modifier(int id)

 {



     QSqlQuery query;
     QString id_patient_string= QString::number(id_patient);
     QString num_tel_string= QString::number(num_tel);



       query.prepare("update PATIENT set ID_PATIENT='"+id_patient_string+"', NOM='"+nom+"', PRENOM='"+prenom+"', ADRESSE='"+adresse+"', NUMERO_TELEPHONE='"+num_tel_string+"', MAIL_PATIENT='"+mail+"' WHERE ID_PATIENT='"+id_patient_string+"'");

       query.bindValue(":id", id_patient_string);
       query.bindValue(":forename", nom);
       query.bindValue(":surname", prenom);
       query.bindValue(":adresse", adresse);
       query.bindValue(":tel", num_tel_string);
       query.bindValue(":mail", mail);








           return    query.exec();

}



 int Patient::getid_patient(){return id_patient;}
 QString Patient::getnom(){return nom;}
 QString Patient::getprenom(){return prenom;}
 QString Patient::getadresse(){return adresse;}
 int Patient::getnum_tel(){return num_tel;}
 QString Patient::getmail(){return mail;}


 void Patient::setid_patient(int id_patient){this->id_patient=id_patient;}
 void Patient::setnom(QString nom){this->nom=nom;}
 void Patient::setprenom(QString prenom){this->prenom=prenom;}
 void Patient::setadresse(QString adresse){this->adresse=adresse;}
 void Patient::setnum_tel(int num_tel){this->num_tel=num_tel;}
 void Patient::setmail(QString mail){this->mail=mail;}







bool Patient::ajouter()
{


    QSqlQuery query;
    QString id_patient_string= QString::number(id_patient);
    QString num_tel_string= QString::number(num_tel);

    query.prepare("INSERT INTO patient (ID_PATIENT, NOM, PRENOM, ADRESSE, NUMERO_TELEPHONE, MAIL_PATIENT) "
                  "VALUES (:id, :forename, :surname, :adresse, :tel, :mail )");
    query.bindValue(":id", id_patient_string);
    query.bindValue(":forename", nom);
    query.bindValue(":surname", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":tel", num_tel_string);
    query.bindValue(":mail", mail);



    return query.exec();

}




QSqlQueryModel* Patient::afficher()
{

    QSqlQueryModel *model = new QSqlQueryModel;
      model->setQuery("SELECT * FROM patient");


    return model;
}


bool Patient::supprimer(int id_patient)
{

    QSqlQuery query;

    query.prepare("Delete from Patient where id_patient=:id_patient ");
    query.bindValue(0, id_patient);



    return query.exec();


}





QSqlQueryModel * Patient::recherche(QString id_patient,QString nom , QString prenom   )  /*cherche un producteur de meme id*/
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM Patient WHERE id_patient LIKE '" + id_patient + "' or nom LIKE '" + nom + "' or prenom LIKE '" + prenom + "'" );


    return model;
}





QSqlQueryModel * Patient::tri_N_Passeport()
   {QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("select * from Patient order by id_patient");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PATIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr(" PRENOM"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMERO_TELEPHONE"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAIL_PATIENT"));

          return model;
      }



 QString Patient::CaptchaGenerator()
{
    std::srand(std::time(nullptr));
    QString m_captcha = QString::fromStdString(generateRandomString(6));

    return m_captcha;
}



 std::string Patient::generateRandomString(int length)
 {
     static const std::string alphanum =
         "0123456789"
         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
         "abcdefghijklmnopqrstuvwxyz";
     std::string randomString = "";
     for (int i = 0; i < length; i++) {
         int index = rand() % alphanum.length();
         randomString += alphanum[index];
     }
     return randomString;
 }











