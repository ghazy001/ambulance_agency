#include "employee.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QString>
employee::employee()
{id=0;
 nom="";
 prenom="";
 salaire=0;
 mail="";
}

employee::employee(int id,QString nom, QString prenom, int salaire, QString mail)
{
 this->id=id;
this->nom=nom;
this->prenom=prenom;
this->salaire=salaire;
this->mail=mail;

}
int employee::getid(){return id;}
QString employee::getnom(){return nom;}
QString employee::getprenom(){return prenom;}
int employee::getsal(){return salaire;}
QString employee::getmail(){return mail;}

void employee::setid(int id){this->id=id;};
void employee::setnom(QString nom){this->nom=nom;}
void employee::setprenom(QString prenom){this->prenom=prenom;}
void employee::setsal(int salaire){this->salaire=salaire;}
void employee::setmail(QString mail){this->mail=mail;}


QSqlQueryModel* employee::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT* FROM Employe");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));

return model;

}

bool employee::ajouter()
{
    QSqlQuery query;
    QString num_string= QString::number(id);
    QString salstring=QString::number(salaire);
         query.prepare("INSERT INTO Employe (ID_EMPLOYE, NOM, PRENOM, SALAIRE, adresse_mail) "
                       "VALUES (:id, :forename, :surname, :salaire,:mail)");
         query.bindValue(":id", num_string);
         query.bindValue(":forename", nom);
         query.bindValue(":surname", prenom);
         query.bindValue(":salaire", salstring);
         query.bindValue(":mail", mail);

         return query.exec();

}
bool employee::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from Employe where ID_EMPLOYE= :id");
    query.bindValue(":id",res);
    return query.exec();
}

bool employee::modifier(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString sal_string=QString::number(salaire);

    query.prepare("update EMPLOYE set ID_EMPLOYE='"+id_string+"', NOM='"+nom+"',PRENOM='"+prenom+"',SALAIRE='"+sal_string+"',   ADRESSE_MAIL='"+mail+"' WHERE ID_EMPLOYE='"+id_string+"'");
    query.bindValue(":id", id_string);
    query.bindValue(":forename", nom);
    query.bindValue(":surname", prenom);
    query.bindValue(":salaire",sal_string );
    query.bindValue(":mail", mail);



          return    query.exec();
}

QSqlQueryModel * employee::recherche(QString search )
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("SELECT * FROM EMPLOYE WHERE  ID_EMPLOYE LIKE '" + search + "'or nom like '%"+search+"%' or prenom like '%"+search+"%' or salaire like '%"+search+"%' or ADRESSE_MAIL like '%"+search+"%'");


        return model;



}



QSqlQueryModel * employee::tri_N_Passeport()
   {QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("select * from EMPLOYE order by ID_EMPLOYE");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));

       return model;
   }
QSqlQueryModel * employee::triNOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM EMPLOYE order by NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
    return model;

}

QChart *employee::statistique_chart()
{
    QSqlQuery query0, query1, query2, query3, query4;

    qreal c1_1 = 0, c1_2 = 0, c1_3 = 0, c1_4 = 0;

    int totale = 0;

    query0.prepare("SELECT * FROM EMPLOYE");
    query0.exec();

    query1.prepare("SELECT * FROM EMPLOYE WHERE SALAIRE>'5000' ");
    query1.exec();

    query2.prepare("SELECT *  FROM EMPLOYE WHERE SALAIRE>'1700' AND SALAIRE<'3000'");
    query2.exec();

    query3.prepare("SELECT * FROM EMPLOYE WHERE SALAIRE>'800' AND SALAIRE<'1500' ");
    query3.exec();

    query4.prepare("SELECT * FROM EMPLOYE WHERE SALAIRE<'800'");
    query4.exec();

    while (query0.next()) {
        totale++;
    }

    while (query1.next()) { //c1_1 contiendra le nombre d'employés qui ont un salaire supérieur à 5000.
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

   QBarSet *set0 = new QBarSet("PDG");
    QBarSet *set1 = new QBarSet("RH");
    QBarSet *set2 = new QBarSet("chauffeur");
    QBarSet *set3 = new QBarSet("ouvrier");

    *set0 << (c1_1 / totale) * 100;  // ajoute un élément à l'ensemble de données set0
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
    chart->setTitle("Statistique des Salaires ");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeLight);



    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d%"); //  format pourcentage
    axisY->setRange(0, 100); // set y-axis range to 0-100
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);

    return chart;
}

QChart *employee::statistique_chart1()
{
    QSqlQuery query0, query1, query2, query3, query4;

    qreal c1_1 = 0, c1_2 = 0, c1_3 = 0, c1_4 = 0;

    int totale = 100;

    query0.prepare("SELECT * FROM EMPLOYE");
    query0.exec();

    query1.prepare("SELECT * FROM EMPLOYE WHERE SALAIRE>'5000' ");
    query1.exec();

    query2.prepare("SELECT *  FROM EMPLOYE WHERE SALAIRE>'1500' AND SALAIRE<'3000'");
    query2.exec();

    query3.prepare("SELECT * FROM EMPLOYE WHERE SALAIRE>'800' AND SALAIRE<'1500' ");
    query3.exec();

    query4.prepare("SELECT * FROM EMPLOYE WHERE SALAIRE<'800'");
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

    QPieSeries *series = new QPieSeries();

    series->append("PDG", (c1_1 / totale) * 100); // ajoute PDG à l'ensemble de données set0
    series->append("RH", (c1_2 / totale) * 100);
    series->append("chauffeur", (c1_3 / totale) * 100);
    series->append("ouvrier", (c1_4 / totale) * 100);

    series->setPieSize(8);
    series->setPieStartAngle(300);
    series->setHoleSize(0);

    QChart *chart1 = new QChart();
    chart1->addSeries(series);
    chart1->setTitle("Statistique des Salaires");
    chart1->setAnimationOptions(QChart::AllAnimations);
    chart1->setTheme(QChart::ChartThemeDark);

    QPieSlice *slice0 = series->slices().at(0); //on récupère la première tranche du graphique
    slice0->setColor(QColor("#008CBA"));

    QPieSlice *slice1 = series->slices().at(1);
    slice1->setColor(QColor("#E91E63"));

    QPieSlice *slice2 = series->slices().at(2);
    slice2->setColor(QColor("#FFC107"));

    QPieSlice *slice3 = series->slices().at(3);
    slice3->setColor(QColor("#4CAF50"));

    return chart1;
}
/*
QPieSeries *series = new QPieSeries();

// ajouter des tranches avec des pourcentages calculés
series->append("PDG", (c1_1 / totale) * 100);
series->append("RH", (c1_2 / totale) * 100);
series->append("chauffeur", (c1_3 / totale) * 100);
series->append("ouvrier", (c1_4 / totale) * 100);

// Calculer la somme des pourcentages
qreal totalPercentage = series->sum();

// Ajuster la valeur de la dernière tranche si nécessaire
if (totalPercentage != 100.0) {
    qreal diff = 100.0 - totalPercentage;
    QPieSlice *lastSlice = series->slices().last();
    lastSlice->setValue(lastSlice->value() + diff);
}

// Définir la taille de la tarte à 100%
series->setPieSize(1.0);

// Définir la taille du trou à 0 pour avoir une tarte pleine
series->setHoleSize(0);

// Créer le graphique
QChart *chart1 = new QChart();
chart1->addSeries(series);
chart1->setTitle("Statistique des Salaires");
chart1->setAnimationOptions(QChart::AllAnimations);
chart1->setTheme(QChart::ChartThemeDark);

// Définir les couleurs des tranches
QPieSlice *slice0 = series->slices().at(0);
slice0->setColor(QColor("#008CBA"));

QPieSlice *slice1 = series->slices().at(1);
slice1->setColor(QColor("#E91E63"));

QPieSlice *slice2 = series->slices().at(2);
slice2->setColor(QColor("#FFC107"));

QPieSlice *slice3 = series->slices().at(3);
slice3->setColor(QColor("#4CAF50"));

return chart1;
}*/
