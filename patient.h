#ifndef PAtIENT_H
#define PAtIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <string>

class Patient
{
public:
    Patient();
     Patient(int, QString, QString, QString, int, QString);
     int getid_patient();
     QString getnom();
     QString getprenom();
     QString getadresse();
     int getnum_tel();
     QString getmail();


     void setid_patient(int);
     void setnom(QString);
     void setprenom(QString);
     void setadresse(QString);
     void setnum_tel(int);
     void setmail(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier (int);

    std::string CaptchaGenerator();

    QSqlQueryModel* recherche(QString id_patient,QString nom , QString prenom );

           QSqlQueryModel * tri_N_Passeport();


           std::string getCaptcha();
           bool verify(const std::string& input);



private:
    int id_patient;
    QString nom, prenom, adresse, mail;
    int num_tel;

 void affichecap();

  std::string generateRandomString(int length);
  std::string m_captcha;
};











#endif // PAtIENT_H
