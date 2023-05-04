#ifndef AMBULANCE_H
#define AMBULANCE_H
#include <QString>
#include <qsqlquery.h>
#include <QSqlQueryModel>
#include<QtCharts>

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
    bool update();
    QSqlQueryModel* recherche(QString id,QString marque,QString modele,QString etat);
    QSqlQueryModel*  trier(int test);
    QChart *statistique_chart();
    void refreshChart();
    QSqlQueryModel * afficherAr();




private:
   int matricule,KM;
   QString Modele, marque,etat;
};

#endif // AMBULANCE_H
