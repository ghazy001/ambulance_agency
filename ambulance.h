#ifndef AMBULANCE_H
#define AMBULANCE_H
#include <QString>
#include <qsqlquery.h>
#include <QSqlQueryModel>


class ambulance
{

public:
   ambulance();
   ambulance(int,QString,QString,QString,int);
   //.............
   int getmatricule();
   QString getmarque();
   QString getmodele();
   QString getetat();
   int getkm();

   //.............
   void setmatricule(int);
   void setmarque(QString);
   void setmodele(QString);
   void setetat(QString);
    void setkm(int);

   //...........
   bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int);
   bool existance(QString id);


private:
   int matricule,KM;
   QString Modele, marque,etat;
};

#endif // AMBULANCE_H
