#ifndef HOPITAUX_H
#define HOPITAUX_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Hopitaux
{

public:
    //constructeur
    Hopitaux();
    Hopitaux(int,QString,QString,int);

    //getters
    int getid_hopital();
    QString getnom_hopital();
    QString getadresse();
    int getcapacite();

    //setters
    void setid_hopital(int);
    void setnom_hopital(QString);
    void setadresse(QString);
    void setcapacite(int);

    //Fonctionalite de base relative à l'entite Hopitaux
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);

private:
    int id_hopital,capacite;
    QString nom_hopital,adresse;


};

#endif // HOPITAUX_H
