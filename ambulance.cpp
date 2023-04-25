#include "ambulance.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QObject>
#include <QCollator>
#include <QCoreApplication>

ambulance::ambulance(){
    matricule=0;
    marque=" ";
    Modele=" ";
    etat=" ";
    KM=0;

}
ambulance::ambulance(int matricule,QString marque,QString Modele ,QString etat,int KM){
    this->matricule=matricule;
    this->marque=marque;
    this->Modele=Modele;
    this->etat=etat;
    this->KM=KM;

}
int ambulance::getmatricule(){
    return matricule;
}
QString ambulance::getmarque(){
    return marque;
}
QString ambulance::getmodele(){
    return Modele;
}
QString ambulance::getetat(){
    return etat;
}

int ambulance::getkm(){
    return KM;
}

void ambulance::setmatricule(int matricule){
    this->matricule=matricule;
}
void ambulance::setmodele(QString Modele){
    this->Modele=Modele;

}
void ambulance::setmarque(QString marque){
    this->marque=marque;

}
void ambulance::setkm(int KM){
    this->KM=KM;
}
void ambulance::setetat(QString etat){
    this->etat=etat;
}

bool ambulance::ajouter(){

    QSqlQuery query;
    QString matricule_string=QString::number(matricule);
    QString km_string=QString::number(KM);
    query.prepare("INSERT INTO AMBULANCE (MATRICULE, MARQUE, MODELE, ETAT, KILOMETRAGE) "
                  "VALUES (:matricule, :marque, :Modele, :etat, :KM)");
    query.bindValue(":matricule", matricule_string);
    query.bindValue(":marque", marque);
    query.bindValue(":Modele", Modele);
    query.bindValue(":etat", etat);
    query.bindValue(":KM", km_string);


    return query.exec();
}


bool ambulance::supprimer(int matricule){
    QSqlQuery query;
    query.prepare("DELETE FROM AMBULANCE WHERE MATRICULE=:matricule ");
    query.bindValue(":matricule", matricule);

    return query.exec();


}

bool ambulance::update(){

    QString matricule_string=QString::number(matricule);
    QString km_string=QString::number(KM);

    QSqlQuery quer;
    quer.prepare("update AMBULANCE set MATRICULE='"+matricule_string+"', MARQUE='"+marque+"',MODELE='"+Modele+"',KILOMETRAGE='"+km_string+"',   ETAT='"+etat+"' WHERE MATRICULE='"+matricule_string+"' ");
    return quer.exec();

}



QSqlQueryModel * ambulance::afficher(){


    QSqlQueryModel *model =new QSqlQueryModel();


          model->setQuery("SELECT * FROM AMBULANCE");

      /*    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Modele"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Kilometrage"));


*/

    return model;
}

bool ambulance::existance(QString id)
{
    QMessageBox msgBox;
    QSqlQuery query;
    int count=0;
    query.prepare("SELECT * FROM AMBULANCE WHERE MATRICULE= ?");
    query.addBindValue(id);
    if(query.exec() )
    {
        while (query.next())
        {
            count ++;
        }
        if(count>=1)
        {
            msgBox.setText("matricule deja existe");
            msgBox.exec();
            return 1;
        }

    }
    return 0;
}

QSqlQueryModel * ambulance::recherche(QString id ,QString marque,QString modele,QString etat)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM AMBULANCE WHERE MATRICULE LIKE '%" + id + "%' OR MARQUE LIKE '%" + marque + "%'  OR MODELE LIKE '%" + modele + "%' OR ETAT LIKE '%" + etat + "%' ");

    return model;
}



QSqlQueryModel * ambulance::trier(int test)
{

    QSqlQueryModel *model=new QSqlQueryModel() ;
    QSqlQuery query ;

    if(test==1)
    {
        query.prepare("SELECT *  FROM AMBULANCE ORDER BY MATRICULE  ") ;
    }
    else if(test==2)
    {
        query.prepare("SELECT *  FROM AMBULANCE ORDER BY MODELE  ") ;
    }
    else if(test==3)
    {
        query.prepare("SELECT *  FROM AMBULANCE ORDER BY KILOMETRAGE  ") ;
    }

    if (query.exec()&&query.next())
    {
        model->setQuery(query) ;
    }
        return model;

    }

QChart *ambulance::statistique_chart()
{
   /*
    QSqlQuery query0,query1,query2,query3,query4;

        qreal c1_1=0,c1_2=0,c1_3=0,c1_4=0;

        int totale=0;

        query0.prepare("SELECT * FROM AMBULANCE");
        query0.exec();

        query1.prepare("SELECT * FROM AMBULANCE WHERE ETAT='NEW'");
        query1.exec();

        query2.prepare("SELECT * FROM AMBULANCE WHERE ETAT='OLD'");
        query2.exec();

        query3.prepare("SELECT * FROM AMBULANCE WHERE MODELE='FERRARI'");
        query3.exec();

        query4.prepare("SELECT * FROM AMBULANCE WHERE MODELE='BMW'");
        query4.exec();



        while (query0.next()){totale++;}

        while (query1.next()){c1_1++;}
        while (query2.next()){c1_2++;}
        while (query3.next()){c1_3++;}
        while (query4.next()){c1_4++;}

       totale=totale/2;

        QBarSet *set0 = new QBarSet("MODELE:KIA");
        QBarSet *set1 = new QBarSet("MODELE:JEEP");
        QBarSet *set2 = new QBarSet("MODELE:FERRARI");
        QBarSet *set3 = new QBarSet("MODELE:BMW");

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
        chart->setTitle("Statistique des ambulance par rapport des modeles");
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->setTheme(QChart::ChartThemeBlueCerulean);

        QStringList MODELEs = {"KIA", "JEEP", "FERRARI", "BMW"};
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

*/


    QSqlQuery query1("SELECT COUNT(*) FROM AMBULANCE WHERE MODELE='KIA'");
    QSqlQuery query2("SELECT COUNT(*) FROM AMBULANCE WHERE MODELE='JEEP'");
    QSqlQuery query3("SELECT COUNT(*) FROM AMBULANCE WHERE MODELE='FERRARI'");
    QSqlQuery query4("SELECT COUNT(*) FROM AMBULANCE WHERE MODELE='BMW'");
    QSqlQuery query5("SELECT COUNT(*) FROM AMBULANCE WHERE MODELE='BUGATTI'");
    QSqlQuery query6("SELECT COUNT(*) FROM AMBULANCE WHERE MODELE='RENAULT'");

    qreal c1_1=0,c1_2=0,c1_3=0,c1_4=0,c1_5=0,c1_6=0;

    query1.next();c1_1=query1.value(0).toDouble();
    query2.next();c1_2=query2.value(0).toDouble();
    query3.next();c1_3=query3.value(0).toDouble();
    query4.next();c1_4=query4.value(0).toDouble();
    query5.next();c1_5=query5.value(0).toDouble();
    query6.next();c1_6=query6.value(0).toDouble();

    qreal total = c1_1 + c1_2 + c1_3 + c1_4 + c1_5 + c1_6;

    QPieSeries *series = new QPieSeries();
    series->append("KIA: " + QString::number(c1_1) + " (" + QString::number(c1_1/total*100, 'f', 2) + "%)", c1_1);
    series->append("JEEP: " + QString::number(c1_2) + " (" + QString::number(c1_2/total*100, 'f', 2) + "%)", c1_2);
    series->append("FERRARI: " + QString::number(c1_3) + " (" + QString::number(c1_3/total*100, 'f', 2) + "%)", c1_3);
    series->append("BMW: " + QString::number(c1_4) + " (" + QString::number(c1_4/total*100, 'f', 2) + "%)", c1_4);
    series->append("BUGATTI: " + QString::number(c1_5) + " (" + QString::number(c1_5/total*100, 'f', 2) + "%)", c1_5);
    series->append("RENAULT: " + QString::number(c1_6) + " (" + QString::number(c1_6/total*100, 'f', 2) + "%)", c1_6);

    series->setLabelsVisible();

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique des ambulances par rapport des modeles");

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeBlueCerulean);
        //$$$$$$$$$$$
        series->slices().at(0)->setColor(QColor("#FFC300"));
        series->slices().at(1)->setColor(QColor("#FF5733"));
        series->slices().at(2)->setColor(QColor("#C70039"));
        series->slices().at(3)->setColor(QColor("#900C3F"));
        series->slices().at(4)->setColor(QColor("#0BD7DA"));
        series->slices().at(5)->setColor(QColor("#0BDA5D"));

        //$$$$$$$$$$$
        chart->setTitleFont(QFont("Arial", 17, QFont::Bold));








        return chart;

    }










