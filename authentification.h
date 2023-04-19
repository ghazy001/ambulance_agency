#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H
#include <QString>
#include <QSqlQueryModel>


class authentification
{
public:
    authentification();

        authentification(QString,QString);

        QString getLOGIN();
        QString getMDP();


        void setLOGIN(QString);
        void setMDP(QString);


        // crud
        QSqlQueryModel* afficher1();


 bool ajouter();
 bool supprimer1(QString LOGIN);

private:

    QString LOGIN, MDP;


};

#endif // AUTHENTIFICATION_H
