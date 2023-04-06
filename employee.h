#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQueryModel>

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

        QSqlQueryModel* recherche(QString id);
        QSqlQueryModel * tri_N_Passeport();


private:
    int id,salaire;
    QString nom, prenom,mail;


};


#endif // EMPLOYEE_H
