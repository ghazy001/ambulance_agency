#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQueryModel>

class equipement
{public:
    equipement();
        equipement (int,int,QString,int,QString);
        int getid_equipement();
        int getcode_QR();
        QString getreference();
        int getprix();
        QString getnom_equipement();

        void setid_equipement(int);
        void setcode_QR(int);
        void setreference(QString);
        void setprix(int);
        void setnom_equipement(QString);

        QSqlQueryModel* afficher();

        bool ajouter();
        bool supprimer(int id);




private:
    int id_equipement,code_QR;
    QString reference, nom_equipement;
    int prix;



};

#endif // EQUIPEMENT_H
