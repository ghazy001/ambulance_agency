#include "gestionpatient.h"
#include "ui_gestionpatient.h"
#include "ui_gestionpatient.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QTextStream>
#include <QTextDocument>
#include <QDataStream>
#include <QSqlQuery>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPdfWriter>
#include <QFileDialog>

#include <QtWidgets>


#include <ActiveQt/QAxObject>
#include <QStandardItemModel>

#include <QtWidgets>
#include <QtSql>





gestionpatient::gestionpatient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionpatient)
{
    ui->setupUi(this);



     ui->tabpatient->setModel(E.afficher());


      ui->male->setText(E.CaptchaGenerator());



   ui->lineEdit_17->setValidator(new QIntValidator(0, 999, this));
   ui->lineEdit_21->setValidator(new QIntValidator(1111111, 99999999, this));

   ui->idsup_3->setValidator(new QIntValidator(0, 999, this));
   ui->mod1_3->setValidator(new QIntValidator(0, 999, this));
   ui->mod5_3->setValidator(new QIntValidator(1111111, 99999999, this));
   QRegExp
       regExp("^[A-Za-z]*$");
       ui->lineEdit_18->setValidator(new QRegExpValidator(regExp, this));
       ui->lineEdit_19->setValidator(new QRegExpValidator(regExp, this));
       ui->lineEdit_20->setValidator(new QRegExpValidator(regExp, this));

       ui->mod2_3->setValidator(new QRegExpValidator(regExp, this));
        ui->mod2_3->setValidator(new QRegExpValidator(regExp, this));
         ui->mod2_3->setValidator(new QRegExpValidator(regExp, this));



         QChart *chart=new QChart();
         chart=E.statistique_chart();
         QChartView * Cview=new QChartView(chart,ui->STAT_3);
         Cview->resize(650,330);
         Cview->setRenderHint(QPainter::Antialiasing);





}


gestionpatient::~gestionpatient()
{
    delete ui;
}




void gestionpatient::on_insert_2_clicked()
{
    bool teste;
    int id_patient=ui->lineEdit_17->text().toInt();
    QString nom=ui->lineEdit_18->text();
    QString prenom=ui->lineEdit_19->text();
    QString adresse=ui->lineEdit_20->text();
    int num_tel=ui->lineEdit_21->text().toInt();
     QString mail=ui->lineEdit_22->text();

   Patient E(id_patient,nom,prenom,adresse,num_tel,mail);
 teste=E.ajouter();
 QMessageBox msgBox;
if (teste){

    msgBox.setText("Information has been aded.\n""Click ok to exit.");
     ui->tabpatient->setModel(E.afficher());
    msgBox.exec();

}

else {
    msgBox.setText("ECHEC\n""Click ok to exit.");
    msgBox.exec();


}

}

void gestionpatient::on_suppbuton_2_clicked()
{



    Patient E1;
    E1.setid_patient(ui->idsup_3->text().toInt());
    bool test=E1.supprimer(E1.getid_patient());
    QMessageBox msgBox;
   if (test){

       msgBox.setText("SUPPRESSION AVEC SUCCES.\n""Click ok to exit.");
        ui->tabpatient->setModel(E.afficher());
       msgBox.exec();

   }

   else
   {
       msgBox.setText("ECHEC\n""Click ok to exit.");
       msgBox.exec();


   }


}

void gestionpatient::on_modifer_2_clicked()
{
    int id_patient=ui->mod1_3->text().toInt();
    QString nom=ui->mod2_3->text();
    QString prenom=ui->mod3_3->text();
    QString adresse=ui->mod4_3->text();
    int num_tel=ui->mod5_3->text().toInt();
     QString mail=ui->mod6_3->text();

     QString id_patient_string= QString::number(id_patient);
     QString num_tel_string= QString::number(num_tel);

     Patient E(id_patient,nom , prenom, adresse, num_tel, mail);
            bool test=E.modifier(id_patient);
            if(test)
           {
                ui->tabpatient->setModel(E.afficher());

              QMessageBox::information(nullptr, QObject::tr("ok"),
              QObject::tr("modifer effectuee.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);


           }
            else
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
             QObject::tr("modifer non effectue.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);

}



void gestionpatient::on_tabpatient_clicked(const QModelIndex &index)
{
    int val=ui->tabpatient->model()->data(index).toInt();
    QString val_string=QString::number(val);
        QSqlQuery qry;

        qry.prepare("select * from Patient where ID_PATIENT=:v ");
        qry.bindValue(":v",val_string);
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->mod1_3->setText(qry.value(0).toString());
                ui->mod2_3->setText(qry.value(1).toString());
                ui->mod3_3->setText(qry.value(2).toString());
                ui->mod4_3->setText(qry.value(3).toString());
                ui->mod5_3->setText(qry.value(4).toString());
                ui->mod6_3->setText(qry.value(4).toString());

                ui->idsup_3->setText(qry.value(0).toString());

            }

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
}












void gestionpatient::on_tri_clicked()
{


    QMessageBox::information(nullptr, QObject::tr("Ok"),
                          QObject::tr("tri effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
                         ui->tabpatient->setModel(E.tri_N_Passeport());

}



void gestionpatient::on_pdf_clicked()
{

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
              if (QFileInfo(fileName).suffix().isEmpty())
              {
                  fileName.append(".pdf");
              }
              QPrinter printer(QPrinter::PrinterResolution);
              printer.setOutputFormat(QPrinter::PdfFormat);
              printer.setPaperSize(QPrinter::A4);
              printer.setOutputFileName(fileName);
              QTextDocument doc;
              QPdfWriter pdf(fileName);
              QPainter painter(&pdf);
              int i = 4000;
              painter.setPen(Qt::red);//titre
              painter.setFont(QFont("Cambria", 30));
              painter.drawText(1700,1200,"LISTES DES PATIENT");
              painter.setPen(Qt::black);
              painter.setFont(QFont("Cambria",14));
              painter.drawRect(0,3000,9600,500);
              painter.setFont(QFont("Cambria",11));
              painter.drawText(200,3300,"ID_PATIENT");
              painter.drawText(1500,3300,"NOM");
              painter.drawText(2800,3300,"PRENOM");
              painter.drawText(4100,3300,"ADRESSE");
              painter.drawText(5400,3300,"NUMERO_TELEPHONE");
              painter.drawText(7500,3300,"MAIL_PATIENT");


              QSqlQuery query;
              query.prepare("select * from patient");
              query.exec();
              while (query.next())
              {
                  painter.drawText(200,i,query.value(0).toString());
                  painter.drawText(1500,i,query.value(1).toString());
                  painter.drawText(2800,i,query.value(2).toString());
                  painter.drawText(4100,i,query.value(3).toString());

                  painter.drawText(5400,i,query.value(4).toString());
                  painter.drawText(7500,i,query.value(5).toString());

                  i = i + 500;
              }

              doc.print(&printer);

}











void gestionpatient::on_malek12_clicked()
{



       if (ui->stela->text() == ui->male->text())

                {
                   QMessageBox::information(this, "CAPTCHA Verification", "CAPTCHA verified");

                }
       else
                {
                   QMessageBox::warning(this, "CAPTCHA Verification", "CAPTCHA verification failed");

                   ui->male->setText(E.CaptchaGenerator());


                }
              ui->stela->clear();





};



void gestionpatient::on_lineEdit45_textEdited(const QString &arg1)
{

    QString e=ui->lineEdit45->text();
        ui->tabpatient->setModel(E.recherche(arg1,arg1,arg1));


}








void gestionpatient::on_comboBox_activated(const QString &arg1)
{
    if (arg1=="ID_patient")
            ui->tabpatient->setModel(E.trier(1));
        if (arg1=="Nom")
            ui->tabpatient->setModel(E.trier(2));
        if (arg1=="Prenom")
            ui->tabpatient->setModel(E.trier(3));
}

void gestionpatient::on_excel_clicked()

{
E.generer();
}





