#include "hopitaux.h"
#include "mainwindow.h"
#include "connection.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QObject>
#include <QtCharts>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
Hopitaux::Hopitaux()
{
id_hopital=0,nom_hopital=" ",adresse=" ",capacite=0;
}

Hopitaux::Hopitaux(int id_hopital,QString nom_hopital,QString adresse,int capacite, QImage image)
{
    this->id_hopital=id_hopital;
    this->nom_hopital=nom_hopital;
    this->adresse=adresse;
    this->capacite=capacite;
    this->image=image;
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
QImage Hopitaux::getimage()
{
    return image;
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
void Hopitaux::setimage(QImage image)
{
    this->image=image;
}
bool Hopitaux::ajouter()
{
    QSqlQuery query;
    QString id_string= QString::number(id_hopital);
    QString cap= QString::number(capacite);
    QWidget window;
    QString fileName = QFileDialog::getOpenFileName(&window, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
    QPixmap pixmap(fileName);
    QImage imageData = pixmap.toImage();
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    imageData.save(&buffer, "PNG"); // Écrire l'image dans le buffer
    buffer.close();

    // Charger l'image à partir du buffer
    QImage image;
    image.loadFromData(byteArray, "PNG");

          query.prepare("INSERT INTO HOPITAUX (ID_HOPITAUX, NOM, ADRESSE, CAPACITE,IMAGE) " "VALUES (:id_hopital, :nom_hopital, :adresse, :capacite, :image)");
          query.bindValue(":id_hopital", id_string);
          query.bindValue(":nom_hopital", nom_hopital);
          query.bindValue(":adresse", adresse);
          query.bindValue(":capacite", cap);
          query.bindValue(":image", byteArray);


          return query.exec();



}
bool Hopitaux::supprimer(int id_hopital)
{
    QSqlQuery query;
    QString res=QString::number(id_hopital);
    query.prepare("Delete from HOPITAUX WHERE  ID_HOPITAUX= '"+res+"'");

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
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Image"));

    return model;
}
bool Hopitaux::modifier()
{
    QSqlQuery query;
    QString id_hop= QString::number(id_hopital);
    QString capa= QString::number(capacite);

    query.prepare("update HOPITAUX set ID_HOPITAUX='"+id_hop+"', NOM='"+nom_hopital+"',ADRESSE='"+adresse+"',CAPACITE='"+capa+"' WHERE ID_HOPITAUX='"+id_hop+"'");

    return query.exec();
}
QSqlQueryModel * Hopitaux::recherchee(int id_hopital, QString nom_hopital, QString adresse, int capacite)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QString id_hopp= QString::number(id_hopital);
    QString capac= QString::number(capacite);
        model->setQuery("SELECT * FROM HOPITAUX WHERE ID_HOPITAUX LIKE '" +id_hopp+ "' OR NOM LIKE '" +nom_hopital+ "' OR ADRESSE LIKE '" +adresse+ "' OR CAPACITE LIKE '" +capac+ "'  ");

        return model;
}
QSqlQueryModel * Hopitaux::recherche(QString search )
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("SELECT * FROM HOPITAUX WHERE  ID_HOPITAUX LIKE '" + search + "'or NOM like '%"+search+"%' or ADRESSE like '%"+search+"%' or CAPACITE like '%"+search+"%'");


        return model;
}
QSqlQueryModel * Hopitaux::trier(int test)
{

    QSqlQueryModel *model=new QSqlQueryModel() ;
    QSqlQuery query ;

    if(test==1)
    {
        query.prepare("SELECT *  FROM HOPITAUX ORDER BY ID_HOPITAUX  ") ;
    }
    else if(test==2)
    {
        query.prepare("SELECT *  FROM HOPITAUX ORDER BY NOM  ") ;
    }
    else if(test==3)
    {
        query.prepare("SELECT *  FROM HOPITAUX ORDER BY ADRESSE  ") ;
    }

    if (query.exec()&&query.next())
    {
        model->setQuery(query) ;
    }
        return model;

    }
QSqlQueryModel * Hopitaux::afficher_pointage()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM HISTORIQUE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Alarme"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Temperature"));


 return model;
}

