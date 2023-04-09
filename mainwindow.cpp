#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ambulance.h"
#include <QValidator>
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QIntValidator>
#include<QtPrintSupport/QPrinter>
#include<QPainter>
#include<QTextDocument>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QFileDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include<QImage>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <QStackedWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->matricule1->setValidator(new QIntValidator(0,999999,this));
   ui->km->setValidator(new QIntValidator(0,999999,this));
   //ui->matricule_supp->setValidator(new QIntValidator(0,999999,this));
   ui->tab_ambulance->setModel(A.afficher());
QChart *chart=new QChart();
chart=A.statistique_chart();
QChartView * Cview=new QChartView(chart,ui->STAT);
Cview->resize(650,330);
Cview->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_insertButton_2_clicked()
{
    QMessageBox msgBox;
    int matricule=ui->matricule1->text().toInt();
    QString marque=ui->marque->text();
    QString Modele=ui->modele->currentText();
    QString etat=ui->etat->currentText();
    int KM=ui->km->text().toInt();
    QString matricule_string=QString::number(matricule);
  if (!A.existance(matricule_string)){
   ambulance A( matricule,marque,Modele,etat,KM);

   bool test=A.ajouter();

   if( test){
       msgBox.setText("Informations has been added");
       ui->tab_ambulance->setModel(A.afficher());
             msgBox.exec();
   } }
   else {
       msgBox.setText("Informations has been failed");
             msgBox.exec();
   }


}

void MainWindow::on_deleteButton_clicked()
{
ambulance A1;
A1.setmatricule(ui->matricule1->text().toInt());

bool test=A1.supprimer(A1.getmatricule());
QMessageBox msgBox;
if( test){
    msgBox.setText("Removed");
    ui->tab_ambulance->setModel(A.afficher());
         msgBox.exec();
}
else {
    msgBox.setText("Failed");
          msgBox.exec();
}
}

void MainWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://wa.me/+21626864405",QUrl::TolerantMode));
}



void MainWindow::on_pushButton_2_clicked()
{
    //Update

    int matricule=ui->matricule1->text().toInt();
    QString marque=ui->marque->text();
    QString Modele=ui->modele->currentText();
    QString etat=ui->etat->currentText();
    int KM=ui->km->text().toInt();
    ambulance A( matricule,marque,Modele,etat,KM);
/*
    QString matricule_string=QString::number(matricule);
    QString km_string=QString::number(KM);
*/
       /* QSqlQuery quer;
        quer.prepare("update AMBULANCE set MATRICULE='"+matricule_string+"', MARQUE='"+marque+"',MODELE='"+Modele+"',KILOMETRAGE='"+km_string+"',   ETAT='"+etat+"' WHERE MATRICULE='"+matricule_string+"' ");
        if(quer.exec())
        {
            ui->tab_ambulance->setModel(A.afficher());
            QMessageBox::information(nullptr,QObject::tr("OK"), QObject::tr("modification effectué \n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("not OK"),  QObject::tr("modification non effectué \n"  "Click Cancel to exit."),QMessageBox::Cancel);
*/

    bool test=A.update();
    QMessageBox msgBox;
    if( test){
        msgBox.setText("updated");
        ui->tab_ambulance->setModel(A.afficher());
             msgBox.exec();
    }
    else {
        msgBox.setText("Failed");
              msgBox.exec();
    }
    }


bool MainWindow::postrequest(QString smsmsg,QString phonenumber)
{
    bool tried=false;
 // create custom temporary event loop on stack
       QEventLoop eventLoop;

       // "quit()" the event-loop, when the network request "finished()"
       QNetworkAccessManager mgr;
       QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

       // the HTTP request
       QNetworkRequest req( QUrl( QString("https://api.orange.com/smsmessaging/v1/outbound/tel%3A%2B322804/requests") ) );

      req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


        QString api= "Bearer " + apikey;
        req.setRawHeader("Authorization", api.toUtf8());
        QJsonObject msg;
        msg["message"] = smsmsg;
        QJsonObject obj;
        obj["address"] = "tel:"+phonenumber;
        obj["senderAddress"] = "tel:+322804";
        obj["outboundSMSTextMessage"] = msg;
        QJsonObject body;
        body["outboundSMSMessageRequest"] = obj;
        QJsonDocument doc(body);
        QByteArray data = doc.toJson();
       QNetworkReply *reply = mgr.post(req,data);
       eventLoop.exec(); // blocks stack until "finished()" has been called

       if (reply->error() == QNetworkReply::NoError) {
           //success
           qDebug() << "Success" ;
           delete reply;
           return true;
       }
       else {
           //failure
           qDebug() << "Failure" << reply->error();
           if (reply->errorString()=="Host requires authentication")
           {
               if (!tried)
               {
               apikey = QInputDialog::getText(0, "API Key dialog",
                                              "API Key expired, Set a new one :", QLineEdit::Normal,
                                              "", nullptr);
               if (postrequest(smsmsg,phonenumber))
               {
                   return true;
               }

               }
               tried = true;

           }
           delete reply;
           return false;
       }

}


void MainWindow::on_tab_ambulance_clicked(const QModelIndex &index)
//£££££££Remp
{
    int val=ui->tab_ambulance->model()->data(index).toInt();
    QString val_string=QString::number(val);
        QSqlQuery qry;

        qry.prepare("select * from AMBULANCE where MATRICULE=:v ");
        qry.bindValue(":v",val_string);
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->matricule1->setText(qry.value(0).toString());
                ui->marque->setText(qry.value(1).toString());
                ui->modele->setCurrentText(qry.value(2).toString());
                ui->km->setText(qry.value(3).toString());
                ui->etat->setCurrentText(qry.value(4).toString());

            }

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if (arg1=="matricule")
        ui->tab_ambulance->setModel(A.trier(1));
    if (arg1=="modele")
        ui->tab_ambulance->setModel(A.trier(2));
    if (arg1=="kilometrage")
        ui->tab_ambulance->setModel(A.trier(3));
}

void MainWindow::on_pushButton_3_clicked()
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
            painter.drawText(1700,1200,"LISTES DES AMBULANCES");
            painter.setPen(Qt::black);
            painter.setFont(QFont("Cambria",14));
            painter.drawRect(0,3000,9600,500);
            painter.setFont(QFont("Cambria",11));
            painter.drawText(400,3300,"MATRICULE");
            painter.drawText(1600,3300,"MARQUE");
            painter.drawText(3400,3300,"MODELE");
            painter.drawText(4800,3300,"ETAT");
            painter.drawText(6600,3300,"KILOMETRAGE");
            // Add signature to the PDF
            painter.setFont(QFont("Cambria",12, QFont::Bold));
            painter.drawText(7000, 9600, "Signature:");
            painter.drawLine(7400, 9650, 9200, 9650);


             //date

            QDateTime now = QDateTime::currentDateTime();
            painter.setFont(QFont("Cambria", 11));
            painter.drawText(7900, 480, QString("Date: %1").arg(now.toString("yyyy-MM-dd")));


            QSqlQuery query;
            query.prepare("select * from AMBULANCE");
            query.exec();
            while (query.next())
            {
                painter.drawText(400,i,query.value(0).toString());
                painter.drawText(1600,i,query.value(1).toString());
                painter.drawText(3400,i,query.value(2).toString());
                painter.drawText(4800,i,query.value(3).toString());
                painter.drawText(6900,i,query.value(4).toString());
                i = i + 500;
            }


            // image
            QImage image(":/new/prefix1/aaaa.png");
            painter.drawImage(QRect(100, 100, 600, 600), image);



            doc.print(&printer);





}

void MainWindow::on_pushButton_4_clicked()

{
     QMessageBox msgBox;
     QString Num=ui->SMSTEXT->text();
     postrequest("Bonjour,l'ambulance va arriver dans quelques minutes",Num);
     msgBox.setText("SMS has been sent");
     msgBox.exec();
}

void MainWindow::on_chercher_textEdited(const QString &arg1)
{
    QString a=ui->chercher->text();

    ui->tab_ambulance->setModel(A.recherche(arg1,arg1,arg1,arg1));

}

