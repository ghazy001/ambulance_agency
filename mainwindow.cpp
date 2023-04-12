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


#include <QStandardItemModel>


#include <QtWidgets>
#include <QtSql>


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
     ui->tabpatient->setModel(E.afficher());


      ui->male->setText(E.CaptchaGenerator());




   ui->lineEdit_5->setValidator(new QIntValidator(0, 999, this));
   ui->lineEdit_9->setValidator(new QIntValidator(1111111, 99999999, this));

   ui->idsup->setValidator(new QIntValidator(0, 999, this));
   ui->mod1->setValidator(new QIntValidator(0, 999, this));
   ui->mod5->setValidator(new QIntValidator(1111111, 99999999, this));
   QRegExp
       regExp("^[A-Za-z]*$");
       ui->lineEdit_6->setValidator(new QRegExpValidator(regExp, this));
       ui->lineEdit_7->setValidator(new QRegExpValidator(regExp, this));
       ui->lineEdit_8->setValidator(new QRegExpValidator(regExp, this));

       ui->mod2->setValidator(new QRegExpValidator(regExp, this));
        ui->mod2->setValidator(new QRegExpValidator(regExp, this));
         ui->mod2->setValidator(new QRegExpValidator(regExp, this));





}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_insert_clicked()
{
    bool teste;
    int id_patient=ui->lineEdit_5->text().toInt();
    QString nom=ui->lineEdit_6->text();
    QString prenom=ui->lineEdit_7->text();
    QString adresse=ui->lineEdit_8->text();
    int num_tel=ui->lineEdit_9->text().toInt();
     QString mail=ui->lineEdit_10->text();

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

void MainWindow::on_suppbuton_clicked()
{
  Patient E1;
  E1.setid_patient(ui->idsup->text().toInt());
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

void MainWindow::on_modifer_clicked()
{
    int id_patient=ui->mod1->text().toInt();
    QString nom=ui->mod2->text();
    QString prenom=ui->mod3->text();
    QString adresse=ui->mod4->text();
    int num_tel=ui->mod5->text().toInt();
     QString mail=ui->mod6->text();

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




void MainWindow::on_tabpatient_clicked(const QModelIndex &index)
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
                ui->mod1->setText(qry.value(0).toString());
                ui->mod2->setText(qry.value(1).toString());
                ui->mod3->setText(qry.value(2).toString());
                ui->mod4->setText(qry.value(3).toString());
                ui->mod5->setText(qry.value(4).toString());
                ui->mod6->setText(qry.value(4).toString());

                ui->idsup->setText(qry.value(0).toString());

            }

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
}








void MainWindow::on_re_clicked()
{
    QString e=ui->lineEdit45->text();
        ui->tabpatient->setModel(E.recherche(e,e,e));
}




void MainWindow::on_tri_clicked()
{


    QMessageBox::information(nullptr, QObject::tr("Ok"),
                          QObject::tr("tri effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
                         ui->tabpatient->setModel(E.tri_N_Passeport());

}



void MainWindow::on_pdf_clicked()
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











void MainWindow::on_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export excel", QString(), "*.excel");
              if (QFileInfo(fileName).suffix().isEmpty())
              {
                  fileName.append(".excel");
              }
               QTextDocument doc;
               QPrinter printer(QPrinter::PrinterResolution);
               printer.setOutputFormat(QPrinter::PdfFormat);
               printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);
               QPdfWriter pdf(fileName);
               QPainter painter(&pdf);
                painter.setFont(QFont("Cambria", 30));


              QSqlQuery query("SELECT * FROM patient");
                     QStringList header;
                     QList<QStringList> donnees;
                     while (query.next()) {
                         QStringList ligne;
                         ligne << query.value(0).toString();
                         ligne << query.value(1).toString();
                         ligne << query.value(2).toString();
                         donnees.append(ligne);
                     }
                     header << "Colonne 1" << "Colonne 2" << "Colonne 3";

                     // Écriture des données dans un fichier Excel
                     QFile file("donnees.xls");
                     if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                         QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier !");
                         return;
                     }

                     QTextStream out(&file);
                     // Écrire les en-têtes
                     for (int i = 0; i < header.size(); i++) {
                         out << header.at(i) << "\t";
                     }
                     out << "\n";
                     // Écrire les données
                     foreach (const QStringList &ligne, donnees) {
                         for (int i = 0; i < ligne.size(); i++) {
                             out << ligne.at(i) << "\t";
                         }
                         out << "\n";
                     }

                     // Fermeture du fichier
                     file.close();

                     // Affichage d'un message de confirmation
                     QMessageBox::information(this, "Exportation réussie", "Les données ont été exportées vers le fichier Excel.");

doc.print(&printer);
             }







void MainWindow::on_malek12_clicked()
{



       if (ui->stela->text() == ui->male->text())

                {
                   QMessageBox::information(this, "CAPTCHA Verification", "CAPTCHA verified");
                }
       else
                {
                   QMessageBox::warning(this, "CAPTCHA Verification", "CAPTCHA verification failed");
                }
              ui->stela->clear();

};


