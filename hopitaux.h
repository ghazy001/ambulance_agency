#ifndef HOPITAUX_H
#define HOPITAUX_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
class Hopitaux
{

public:
    //constructeur
    Hopitaux();
    Hopitaux(int,QString,QString,int,QImage);

    //getters
    int getid_hopital();
    QString getnom_hopital();
    QString getadresse();
    int getcapacite();
    QImage getimage();


    //setters
    void setid_hopital(int);
    void setnom_hopital(QString);
    void setadresse(QString);
    void setcapacite(int);
    void setimage(QImage);

    //Fonctionalite de base relative à l'entite Hopitaux
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* recherchee(int,QString,QString,int);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel *trier(int test);
    QSqlQueryModel *afficher_pointage();



private:
    int id_hopital,capacite;
    QString nom_hopital,adresse;
    QLineEdit lineEdit;
    QLabel label;
    QImage image;


};

#endif // HOPITAUX_H
