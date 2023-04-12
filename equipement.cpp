#include "equipement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QString>
equipement::equipement()
{id_equipement=0;
    reference="";
    prix=0;
    nom_equipement="";

}
equipement::equipement(int id_equipement, QString reference, int prix, QString nom_equipement)
{
 this->id_equipement=id_equipement;
this->reference=reference;
this->prix=prix;
this->nom_equipement=nom_equipement;

}
int equipement::getid_equipement(){return id_equipement;}
QString equipement::getreference(){return reference;}
int equipement::getprix(){return prix;}
QString equipement::getnom_equipement(){return nom_equipement;}

void equipement::setid_equipement(int id_equipement){this->id_equipement=id_equipement;};
void equipement::setreference(QString reference){this->reference=reference;}
void equipement::setprix(int prix){this->prix=prix;}
void equipement::setnom_equipement(QString nom_equipement){this->nom_equipement=nom_equipement;}
QSqlQueryModel* equipement::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT* FROM equipement");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_equipement"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("reference"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_equipement"));


return model;

}
bool equipement::ajouter()
{
    QSqlQuery query;
    QString num_string= QString::number(id_equipement);
         query.prepare("INSERT INTO Equipement (id_equipement, reference, prix, nom_equipement) "
                       "VALUES (:id_equipement, :reference, :prix,:nom_equipement)");
         query.bindValue(":id_equipement", num_string);
         query.bindValue(":reference", reference);
         query.bindValue(":prix", prix);
         query.bindValue(":nom_equipement", nom_equipement);

         return query.exec();

}
bool equipement::supprimer(int id_equipement)
{
    QSqlQuery query;
 //   QString res=QString::number(id_equipement);
    query.prepare("Delete from equipement where id_equipement= :id_equipement");
    query.bindValue(":id_equipement",id_equipement);
    return query.exec();
}
bool equipement::modifier(){
    QSqlQuery quer;
    QString id_string = QString::number(id_equipement) ;
    QString prix_string = QString::number(prix) ;
    quer.prepare("update EQUIPEMENT set ID_EQUIPEMENT='"+id_string+"',REFERENCE='"+reference+"',PRIX='"+prix_string+"',   NOM_EQUIPEMENT='"+nom_equipement+"' WHERE ID_EQUIPEMENT='"+id_string+"'");
    return quer.exec();
}




QSqlQueryModel* equipement::rechercher(QString rech)
  {
      QSqlQueryModel * model= new QSqlQueryModel();
          QString recher="select * from EQUIPEMENT where NOM_EQUIPEMENT like '%"+rech+"%' or REFERENCE like '%"+rech+"%'or PRIX like '%"+rech+"%'or NOM_EQUIPEMENT like '%"+rech+"%'   ";
          model->setQuery(recher);
          return model;
  }





QSqlQueryModel * equipement::trier(int test)
{

    QSqlQueryModel *model=new QSqlQueryModel() ;
    QSqlQuery query ;

    if(test==1)
    {
        query.prepare("SELECT *  FROM EQUIPEMENT ORDER BY ID_EQUIPEMENT  ") ;
    }
    else if(test==2)
    {
        query.prepare("SELECT *  FROM EQUIPEMENT ORDER BY REFERENCE  ") ;
    }
    else if(test==3)
    {
        query.prepare("SELECT *  FROM EQUIPEMENT ORDER BY PRIX  ") ;
    }

    if (query.exec()&&query.next())
    {
        model->setQuery(query) ;
    }
        return model;

    }

QChart *equipement::statistique_chart()
{
    QSqlQuery query0, query1, query2, query3, query4;

    qreal c1_1 = 0, c1_2 = 0, c1_3 = 0, c1_4 = 0;

    int totale = 0;

    query0.prepare("SELECT * FROM EQUIPEMENT");
    query0.exec();

    query1.prepare("SELECT * FROM EQUIPEMENT WHERE nom_equipement='pansement'");
    query1.exec();

    query2.prepare("SELECT * FROM EQUIPEMENT WHERE NOM_EQUIPEMENT='seringue'");
    query2.exec();

    query3.prepare("SELECT * FROM EQUIPEMENT WHERE NOM_EQUIPEMENT='thermometre'");
    query3.exec();

    query4.prepare("SELECT * FROM EQUIPEMENT WHERE NOM_EQUIPEMENT='stethoscope'");
    query4.exec();

    while (query0.next()) {
        totale++;
    }

    while (query1.next()) {
        c1_1++;
    }
    while (query2.next()) {
        c1_2++;
    }
    while (query3.next()) {
        c1_3++;
    }
    while (query4.next()) {
        c1_4++;
    }

    QBarSet *set0 = new QBarSet("pansement");
    QBarSet *set1 = new QBarSet("seringue");
    QBarSet *set2 = new QBarSet("thermometre");
    QBarSet *set3 = new QBarSet("stethoscope");

    *set0 << (c1_1 / totale) * 100;
    *set1 << (c1_2 / totale) * 100;
    *set2 << (c1_3 / totale) * 100;
    *set3 << (c1_4 / totale) * 100;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique des equipements ");
    chart->setAnimationOptions(QChart::AllAnimations);
    //chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->setTheme(QChart::ChartThemeBlueNcs);
    /*
     *
ChartThemeLight: A light theme with pastel colors.
ChartThemeDark: A dark theme with contrasting colors.
ChartThemeBrownSand: A theme with warm brown and sand colors.
ChartThemeBlueNcs: A theme with shades of blue.
ChartThemeHighContrast: A high-contrast theme with black and white colors.
*/

    QStringList MODELEs = { "","", "", "" };
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(MODELEs);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d%");
    axisY->setRange(0, 100); // set y-axis range to 0-100
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);

    return chart;
}
