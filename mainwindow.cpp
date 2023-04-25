#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QTextStream>
#include <QTextDocument>
#include <QDataStream>
#include <QSqlQuery>
#include <QApplication>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegularExpression>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPdfWriter>
#include <QFileDialog>
#include <QDate>
#include "smtp.h"
#include <QtDebug>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QtGui/QPixmap>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QChart>

#include "authentification.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QSqlQueryModel* model = aut.afficher1();


    ui->tab_employe->setModel(emp.afficher());
     ui->tab_employe_2->setModel(aut.afficher1());
    ui->id_e->setValidator(new QIntValidator(0, 9999999, this));
    ui->salaire_e->setValidator(new QIntValidator(0, 10000, this));
    ui->id_e_2->setValidator(new QIntValidator(0, 9999999, this));
    ui->salaire_e_2->setValidator(new QIntValidator(0, 10000, this));
     ui->id_e_s->setValidator(new QIntValidator(0, 9999999, this));
     QRegExp
         regExp("^[A-Za-z]*$");
     ui->nom_e->setValidator(new QRegExpValidator(regExp, this));
 ui->prenom_e->setValidator(new QRegExpValidator(regExp, this));
     ui->nom_e_2->setValidator(new QRegExpValidator(regExp, this));
      ui->prenom_e_2->setValidator(new QRegExpValidator(regExp, this));

       QRegExp
               mailREX("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z]{2,4}\\b");
        ui->mail_e->setValidator(new QRegExpValidator(mailREX, this));




        QChart *chart1=new QChart();
         chart1 =emp.statistique_chart1();
       QChartView * ChartView1=new QChartView(chart1,ui->stats);
       ChartView1->resize(420,360);
       ChartView1->setRenderHint(QPainter::Antialiasing);
       QChart *chart = new QChart();


     chart =emp.statistique_chart();
            QChartView * ChartView=new QChartView(chart,ui->stats_2);
            ChartView->resize(420,360);
            ChartView->setRenderHint(QPainter::Antialiasing);






}






MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_e_clicked()
{
    int id=ui->id_e->text().toInt();
    ui->tab_employe->setModel(emp.afficher());
        QString nom=ui->nom_e->text();
        QString prenom=ui->prenom_e->text();
        int salaire=ui->salaire_e->text().toInt();
        QString mail=ui->mail_e->text();

        employee emp(id,nom,prenom,salaire,mail);
        bool test=emp.ajouter();
        if(test)
       {
            ui->tab_employe->setModel(emp.afficher());

          QMessageBox::information(nullptr, QObject::tr("ok"),
          QObject::tr("ajout effectuee.\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);


       }
        else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("ajout non effectue.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);

}




void MainWindow::on_UPDATE_clicked()
{
int id=ui->id_e_2->text().toInt();
        QString nom=ui->nom_e_2->text();
        QString prenom=ui->prenom_e_2->text();
        int salaire=ui->salaire_e_2->text().toInt();
        QString mail=ui->mail_e_2->text();
        QString id_string=QString::number(id);
        QString sal_string=QString::number(salaire);

        employee emp(id,nom,prenom,salaire,mail);
        bool test=emp.modifier(id);
        if(test)
       {

      ui->tab_employe->setModel(emp.afficher());

          QMessageBox::information(nullptr, QObject::tr("ok"),
          QObject::tr(" A jour .\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);


         /* delete ui->stats_2;

          // Créer et afficher la nouvelle vue de chart
          QChart *chart = emp.statistique_chart();
          QChartView *chartView = new QChartView(chart, ui->stats_2);
          chartView->setRenderHint(QPainter::Antialiasing);
          chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
         chartView->setChart(chart);
         chartView->setRenderHint(QPainter::Antialiasing);

         /* // Supprimer l'ancien graphique
          delete ui->stats_2->chart();

          // Créer un nouveau graphique mis à jour
          QChart *newChart = emp.statistique_chart();

          // Créer une vue de graphique et la redimensionner
          QChartView *chartView = new QChartView(newChart, ui->stats_2);
          chartView->resize(420, 360);
          chartView->setRenderHint(QPainter::Antialiasing);

          // Afficher le nouveau graphique
          ui->stats_2->setChart(newChart);
          ui->stats_2->setRenderHint(QPainter::Antialiasing);


          /  QChart *chart=new QChart();
          chart =emp.statistique_chart();
          QChartView * ChartView=new QChartView(chart,ui->stats_2);
*/
//updateChart();

       }
        else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("ajout non effectue.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);


        }

void MainWindow::on_supprimer_e_clicked()
{
    employee emp;
emp.setid(ui->id_e_s->text().toInt());
aut.setLOGIN((ui->idajout->text()));
bool test=emp.supprimer(emp.getid());
bool test1=aut.supprimer1(aut.getLOGIN());
QMessageBox msgBox;
if( test || test1){
    msgBox.setText("Removed");
    ui->tab_employe->setModel(emp.afficher());
    ui->tab_employe_2->setModel(aut.afficher1());
         msgBox.exec();
}
else {
    msgBox.setText("Failed");
          msgBox.exec();
}
}

void MainWindow::on_tab_employe_clicked(const QModelIndex &index)
{
    int val=ui->tab_employe->model()->data(index).toInt();
      QString val_string=QString::number(val);

          QSqlQuery qry;

          qry.prepare("select * from Employe where ID_EMPLOYE=:v ");
          qry.bindValue(":v",val_string);
          if(qry.exec())
          {
              while(qry.next())
              {ui->id_e_2->setText(qry.value(0).toString());
                  ui->nom_e_2->setText(qry.value(1).toString());
                  ui->prenom_e_2->setText(qry.value(2).toString());
                  ui->salaire_e_2->setText(qry.value(3).toString());
                  ui->mail_e_2->setText(qry.value(4).toString());

                  ui->id_e_s->setText(qry.value(0).toString());



              }

          }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
          }
}



void MainWindow::on_pushButton_clicked()
{
    QString e=ui->lineEdit_5->text();
    ui->tab_employe->setModel(emp.recherche(e));

}
void MainWindow::on_tab_employe_2_clicked(const QModelIndex &index)
{

        //int val=ui->tab_employe_2->model()->data(index).toInt();
          //QString log=QString::number(val);
         // QString val = ui->tab_employe_2->model()->index.data().toString(); // retrieves the value of the second column (i.e., column 1)
          QString val= ui->tab_employe_2->model()->data(index.sibling(index.row(), 0)).toString(); // récupère la valeur de la colonne 1 (c'est-à-dire la deuxième colonne)

          QSqlQuery qry;

              qry.prepare("select * from AUTHENTIFICATION where LOGIN=:v ");
              qry.bindValue(":v",val);
              if(qry.exec())
              {
                  while(qry.next())
                  {ui->idajout->setText(qry.value(0).toString());
                      ui->mpajout->setText(qry.value(1).toString());




                  }

              }
              else
              {
                  QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
              }
    }

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_employe->setModel(emp.tri_N_Passeport());

}



void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                              QObject::tr("tri effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
                             ui->tab_employe->setModel(emp.triNOM());

}



void MainWindow::on_pushButton_4_clicked()
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
            int i = 4000; //  pos du txt





            painter.setPen(Qt::blue);//titre
            painter.setFont(QFont("Cambria", 30));
            painter.drawText(1700,1200,"LISTES DES EMPLOYEES");

            painter.setPen(Qt::black);
               painter.setFont(QFont("Cambria",14));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Cambria",11));
               painter.drawText(200,3300,"ID_EMPLOYE ");
               painter.drawText(1800,3300, "NOM");
               painter.drawText(3000,3300,"PRENOM");
               painter.drawText(4500,3300,"SALAIRE ");
               painter.drawText(6000,3300,"MAIL");
            // Get the current date and format it as a string
            QDateTime currentDate = QDateTime::currentDateTime();
            QString dateString = currentDate.toString("dd/MM/yyyy");

            // Draw the current date at the top-right corner of the page
            painter.setFont(QFont("Cambria",11));
            painter.drawText(8200,2000, dateString);

            QSqlQuery query;
            query.prepare("select * from EMPLOYE");
            query.exec();
            while (query.next())
            {
                painter.drawText(200,i,query.value(0).toString()); //id
                painter.drawText(1800,i,query.value(1).toString());
                painter.drawText(3000,i,query.value(2).toString());
                painter.drawText(4500,i,query.value(3).toString());
                painter.drawText(6000,i,query.value(4).toString());

                i = i + 500;

                QImage image(":/new/prefix1/icons/smart-ambulance-cartoon-character-design-playing-vector-32647342-removebg-preview (1).png");
                            painter.drawImage(QRect(240, 100, 600, 600), image);
                           /* QImage logo(":/new/prefix1/icons/logo.png");
                                        painter.drawImage(QRect(130, 100, 600, 600), logo);

                                    */
            }

            doc.print(&printer);


    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("pdf done.\n"
                              "Click ok to exit."), QMessageBox::Ok);


}








void MainWindow::on_lineEdit_5_cursorPositionChanged(int arg1, int arg2)
{
    ui->tab_employe->setModel(emp.recherche(ui->lineEdit_5->text()));

        QString test =ui->lineEdit_5->text();

        if(test=="")
        {
            ui->tab_employe->setModel(emp.afficher());//refresh
        }
}

void MainWindow::on_sendBtn_clicked()
{

    Smtp* smtp = new Smtp("iheb.zeddini@esprit.tn",ui->mail_pass->text(), "Smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("iheb.zeddini@esprit.tn", ui->rcpt->text() ,ui->sujet->text(), ui->msg->toPlainText(), files );
    else
        smtp->sendMail("iheb.zeddini@esprit.tn", ui->rcpt->text() ,ui->sujet->text(),ui->msg->toPlainText());


}


void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->sujet->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void MainWindow::on_browseBtn_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}


void MainWindow::on_pushButton_8_clicked()
{

        ui->tab_employe_2->setModel(aut.afficher1());
            QString LOGIN=ui->idajout->text();
            QString MDP=ui->mpajout->text();

            authentification aut(LOGIN,MDP);
            bool test=aut.ajouter();
            if(test)
           {ui->mpajout->setEchoMode(QLineEdit::Password);

                ui->tab_employe_2->setModel(aut.afficher1());
                //ui->mpajout->setEchoMode(QLineEdit::Password);

              QMessageBox::information(nullptr, QObject::tr("ok"),
              QObject::tr("ajout effectuee.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);

           }
            else
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
             QObject::tr("ajout non effectue.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);


}



