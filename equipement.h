#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>

class equipement
{public:
    equipement();
        equipement (int,QString,int,QString);
        int getid_equipement();
        QString getreference();
        int getprix();
        QString getnom_equipement();

        void setid_equipement(int);
        void setreference(QString);
        void setprix(int);
        void setnom_equipement(QString);

        QSqlQueryModel* afficher();

        bool ajouter();
        bool supprimer(int id);
        bool modifier();

       QSqlQueryModel* recherche(QString id);
       QSqlQueryModel * tri_N_Passeport();
       void notifcation();
       QSqlQueryModel* rechercher(QString a);
       QSqlQueryModel * trier(int test);
       QChart *statistique_chart();
QSqlQueryModel* remplircombo();


private:
    int id_equipement;
    QString reference, nom_equipement;
    int prix;



};

#endif // EQUIPEMENT_H
