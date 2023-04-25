#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>

class employee
{
public:
    employee();

        employee(int,QString,QString,int,QString);
        int getid();
        QString getnom();
        QString getprenom();
        int getsal();
        QString getmail();

        void setid(int);
        void setnom(QString);
        void setprenom(QString);
        void setsal(int);
        void setmail(QString);

        // crud
        QSqlQueryModel* afficher();

        bool ajouter();
        bool supprimer(int id);
        bool modifier(int id);

        QSqlQueryModel* recherche(QString search);
        QSqlQueryModel * tri_N_Passeport();
        QSqlQueryModel* triNOM();
QChart *statistique_chart();
QChart * statistique_chart1();
private:
    int id,salaire;
    QString nom, prenom,mail;


};


#endif // EMPLOYEE_H
