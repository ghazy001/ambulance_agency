#include "patient.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QObject>


#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include <QtCore/QDateTime>

#include <QString>
#include <string>


#include "patient.h"

#include <cstdlib>
#include <ctime>

#include <QtWidgets>


#include <ActiveQt/QAxObject>

Patient::Patient(){
id_patient=0;
nom="_";
prenom="_";
adresse="_";
num_tel=0;
mail="_";
}

 Patient::Patient(int id_patient, QString nom ,QString prenom,QString adresse,int num_tel,QString mail)
 {
     this->id_patient=id_patient;
     this->nom=nom;
     this->prenom=prenom;
     this->adresse=adresse;
     this->num_tel=num_tel;
     this->mail=mail;

 }




 bool Patient::modifier(int id)

 {



     QSqlQuery query;
     QString id_patient_string= QString::number(id_patient);
     QString num_tel_string= QString::number(num_tel);



       query.prepare("update PATIENT set ID_PATIENT='"+id_patient_string+"', NOM='"+nom+"', PRENOM='"+prenom+"', ADRESSE='"+adresse+"', NUMERO_TELEPHONE='"+num_tel_string+"', MAIL_PATIENT='"+mail+"' WHERE ID_PATIENT='"+id_patient_string+"'");

       query.bindValue(":id", id_patient_string);
       query.bindValue(":forename", nom);
       query.bindValue(":surname", prenom);
       query.bindValue(":adresse", adresse);
       query.bindValue(":tel", num_tel_string);
       query.bindValue(":mail", mail);








           return    query.exec();

}



 int Patient::getid_patient(){return id_patient;}
 QString Patient::getnom(){return nom;}
 QString Patient::getprenom(){return prenom;}
 QString Patient::getadresse(){return adresse;}
 int Patient::getnum_tel(){return num_tel;}
 QString Patient::getmail(){return mail;}


 void Patient::setid_patient(int id_patient){this->id_patient=id_patient;}
 void Patient::setnom(QString nom){this->nom=nom;}
 void Patient::setprenom(QString prenom){this->prenom=prenom;}
 void Patient::setadresse(QString adresse){this->adresse=adresse;}
 void Patient::setnum_tel(int num_tel){this->num_tel=num_tel;}
 void Patient::setmail(QString mail){this->mail=mail;}







bool Patient::ajouter()
{


    QSqlQuery query;
    QString id_patient_string= QString::number(id_patient);
    QString num_tel_string= QString::number(num_tel);

    query.prepare("INSERT INTO patient (ID_PATIENT, NOM, PRENOM, ADRESSE, NUMERO_TELEPHONE, MAIL_PATIENT) "
                  "VALUES (:id, :forename, :surname, :adresse, :tel, :mail )");
    query.bindValue(":id", id_patient_string);
    query.bindValue(":forename", nom);
    query.bindValue(":surname", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":tel", num_tel_string);
    query.bindValue(":mail", mail);



    return query.exec();

}




QSqlQueryModel* Patient::afficher()
{

    QSqlQueryModel *model = new QSqlQueryModel;
      model->setQuery("SELECT * FROM patient");


    return model;
}


bool Patient::supprimer(int id_patient)
{

    QSqlQuery query;

    query.prepare("Delete from Patient where id_patient=:id_patient ");
    query.bindValue(0, id_patient);



    return query.exec();


}





QSqlQueryModel * Patient::recherche(QString id_patient,QString nom , QString prenom   )
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM Patient WHERE id_patient LIKE '" + id_patient + "' or nom LIKE '" + nom + "' or prenom LIKE '" + prenom + "'" );


    return model;
}





QSqlQueryModel * Patient::tri_N_Passeport()
   {QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("select * from Patient order by id_patient");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PATIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr(" PRENOM"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMERO_TELEPHONE"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAIL_PATIENT"));

          return model;
      }



 QString Patient::CaptchaGenerator()
{
    std::srand(std::time(nullptr));
    QString m_captcha = QString::fromStdString(generateRandomString(4));

    return m_captcha;
}



 std::string Patient::generateRandomString(int length)
 {
     static const std::string alphanum =
         "0123456789"
         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
         "abcdefghijklmnopqrstuvwxyz";
     std::string randomString = "";
     for (int i = 0; i < length; i++) {
         int index = rand() % alphanum.length();
         randomString += alphanum[index];
     }
     return randomString;
 }





 QChart *Patient::statistique_chart()
 {

     QSqlQuery query0,query1,query2,query3,query4;

         qreal c1_1=0,c1_2=0,c1_3=0,c1_4=0;

         int totale=0;

         query0.prepare("SELECT * FROM PATIENT");
         query0.exec();

         query1.prepare("SELECT * FROM PATIENT WHERE ADRESSE ='TUNIS'");
         query1.exec();

         query2.prepare("SELECT * FROM PATIENT WHERE ADRESSE='SOUSSE'");
         query2.exec();

         query3.prepare("SELECT * FROM PATIENT WHERE ADRESSE='JERBA'");
         query3.exec();

         query4.prepare("SELECT * FROM PATIENT WHERE ADRESSE='NEBEL'");
         query4.exec();





         while (query0.next()){totale++;}

         while (query1.next()){c1_1++;}
         while (query2.next()){c1_2++;}
         while (query3.next()){c1_3++;}
         while (query4.next()){c1_4++;}

        totale=totale/2;

         QBarSet *set0 = new QBarSet("ADRESSE:TUNIS");
         QBarSet *set1 = new QBarSet("ADRESSE:SOUSSE");
         QBarSet *set2 = new QBarSet("ADRESSE:JERBA");
         QBarSet *set3 = new QBarSet("ADRESSE:NEBEL");

         *set0 << c1_1;
         *set1 << c1_2;
         *set2 << c1_3;
         *set3 << c1_4;

         QBarSeries *series = new QBarSeries();
         series->append(set0);
         series->append(set1);
         series->append(set2);
         series->append(set3);

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Statistique des patients ");
         chart->setAnimationOptions(QChart::AllAnimations);
         chart->setTheme(QChart::ChartThemeBlueCerulean);

         QStringList MODELEs = { /*"TUNIS", "SOUSSE","JERBA", "NEBEL"*/};
         QBarCategoryAxis *axisX = new QBarCategoryAxis();
         axisX->append(MODELEs);
         chart->addAxis(axisX, Qt::AlignBottom);
         series->attachAxis(axisX);

         QValueAxis *axisY = new QValueAxis();
         axisY->setRange(0,totale);
         chart->addAxis(axisY, Qt::AlignLeft);
         series->attachAxis(axisY);

         QPalette pal = qApp->palette();
         pal.setColor(QPalette::Window, QRgb(0xffffff));
         pal.setColor(QPalette::WindowText, QRgb(0x404044));
         qApp->setPalette(pal);

         return chart;
 }


 QSqlQueryModel * Patient::trier(int test)
 {

     QSqlQueryModel *model=new QSqlQueryModel() ;
     QSqlQuery query ;

     if(test==1)
     {
         query.prepare("SELECT *  FROM PATIENT ORDER BY ID_PATIENT  ") ;
     }
     else if(test==2)
     {
         query.prepare("SELECT *  FROM PATIENT ORDER BY NOM  ") ;
     }
     else if(test==3)
     {
         query.prepare("SELECT *  FROM PATIENT ORDER BY PRENOM  ") ;
     }

     if (query.exec()&&query.next())
     {
         model->setQuery(query) ;
     }
         return model;

     }






 void Patient::generer()
 {

 try{


     QAxObject* excel = new QAxObject("Excel.Application");

     excel->setProperty("Visible", true);

     QAxObject* workbook = excel->querySubObject("Workbooks")->querySubObject("Add");

     QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1);

     worksheet->querySubObject("Cells(int,int)", 1, 1)->setProperty("Value", "ID_PATIENT");
     worksheet->querySubObject("Cells(int,int)", 1, 2)->setProperty("Value", "NOM");
     worksheet->querySubObject("Cells(int,int)", 1, 3)->setProperty("Value", "PRENOM");
     worksheet->querySubObject("Cells(int,int)", 1, 4)->setProperty("Value", "ADRESSE");
     worksheet->querySubObject("Cells(int,int)", 1, 5)->setProperty("Value", "NUMERO_TELEPHONE");
     worksheet->querySubObject("Cells(int,int)", 1, 6)->setProperty("Value", "MAIL_PATIENT");


     QSqlQuery qry;
     qry.prepare("SELECT * FROM PATIENT "  );
     if (qry.exec()) {

         int row = 2;
         while (qry.next()) {
         worksheet->querySubObject("Cells(int,int)", row, 1)->setProperty("Value", qry.value(0).toString());
         worksheet->querySubObject("Cells(int,int)", row, 2)->setProperty("Value", qry.value(1).toString());
         worksheet->querySubObject("Cells(int,int)", row, 3)->setProperty("Value", qry.value(2).toString());
         worksheet->querySubObject("Cells(int,int)", row, 4)->setProperty("Value", qry.value(3).toString());
         worksheet->querySubObject("Cells(int,int)", row, 5)->setProperty("Value", qry.value(4).toString());
         worksheet->querySubObject("Cells(int,int)", row, 6)->setProperty("Value", qry.value(5).toString());
         worksheet->querySubObject("Cells(int,int)", row, 7)->setProperty("Value", qry.value(6).toString());
         worksheet->querySubObject("Cells(int,int)", row, 8)->setProperty("Value", qry.value(7).toString());
         row++;
         }


         QAxObject* usedRange = worksheet->querySubObject("UsedRange");
         QAxObject* columns = usedRange->querySubObject("Columns");

         columns->dynamicCall("AutoFit");


         QString filePath = "C:/Users/youssef/Desktop/Benif.xlsx";
         QVariant result = workbook->dynamicCall("SaveAs(const QString&)", filePath);
         if (result.isNull()) {

             QString errorMessage = "Error: " + workbook->property("LastError").toString();

         }


         workbook->dynamicCall("Close()");
         excel->dynamicCall("Quit()");
     }

 }catch (const std::exception& e) {

         QString errorMessage = "Error: " + QString(e.what());
         QMessageBox::critical(nullptr, "Error", errorMessage);
         }


 }
