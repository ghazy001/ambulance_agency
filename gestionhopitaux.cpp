#include "gestionhopitaux.h"
#include "ui_gestionhopitaux.h"
#include "hopitaux.h"
#include "connection.h"
#include "dumessengerconnectiondialog.h"
#include <QApplication>
#include <QValidator>
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QFileDialog>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QTcpSocket>
#include <QTextStream>
#include <QUrl>
#include <QDebug>


gestionhopitaux::gestionhopitaux(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionhopitaux)
{
    ui->setupUi(this);
    ui->id_hopital->setValidator(new QIntValidator(0,9999999,this));
    ui->capacite->setValidator(new QIntValidator(0,9999999,this));
    ui->id_hopital_2->setValidator(new QIntValidator(0,9999999,this));
    ui->id_hopital_3->setValidator(new QIntValidator(0,9999999,this));
    ui->capacite_2 ->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_hopitaux->setModel(H.afficher());
    ui->tab_hopitaux_2->setModel(H.afficher());
    ui->tab_hopitaux_3->setModel(H.afficher());

    QRegExp
        regExp("^[A-Za-z]*$");
        ui->nom_hopital->setValidator(new QRegExpValidator(regExp, this));
        ui->nom_hopital_2->setValidator(new QRegExpValidator(regExp, this));

        QPieSeries *series = new QPieSeries();
            series->setHoleSize(0);
            series->setPieSize(1.2);
            series->setLabelsVisible(true);
            series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

            QSqlQuery query("SELECT ADRESSE, COUNT(*) FROM HOPITAUX GROUP BY ADRESSE");
            while (query.next()) {
                QString adresse = query.value(0).toString();
                int count = query.value(1).toInt();

                QPieSlice *slice = series->append(adresse, count);
                    int r = qrand() % 256;
                    int g = qrand() % 256;
                    int b = qrand() % 256;
                    slice->setLabel(QString("ADRESSE : %1->%2").arg(adresse).arg(count));
                slice->setColor(QColor(r, g, b));
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Hôpitaux par Adresse");
            chart->setAnimationOptions(QChart::SeriesAnimations);

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setParent(ui->horizontalFrame);
            chartView->resize(ui->horizontalFrame->size());


      mSocket = new QTcpSocket(this);
      connect(mSocket, &QTcpSocket::readyRead, [&]() {
          QTextStream T(mSocket);
          auto text = T.readAll();
          ui->textEdit->append(text);
      });

/*///////////Arduino////////*/
      int ret=A.connect_arduino();
      switch (ret) {
      case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
          break;
      case(1):qDebug()<< "arduino is available but not connected to : "<< A.getarduino_port_name();
          break;
      case(-1):qDebug()<< "arduino is not available";
      }
      QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

gestionhopitaux::~gestionhopitaux()
{
    delete ui;
}



void gestionhopitaux::on_boutton_ajouter_clicked()
{
    int id_hopital=ui->id_hopital->text().toInt();
    QString nom_hopital=ui->nom_hopital->text();
    QString adresse=ui->adresse->text();
    int capacite=ui->capacite->text().toInt();
    QWidget window;
    QString fileName = QFileDialog::getOpenFileName(&window, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
    QPixmap pixmap(fileName);
    ui->label_17->setPixmap(pixmap);
    QImage imageData = pixmap.toImage();
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    imageData.save(&buffer, "PNG"); // Écrire l'image dans le buffer
    buffer.close();

    // Charger l'image à partir du buffer
    QImage image;
    image.loadFromData(byteArray, "PNG");

    Hopitaux H(id_hopital,nom_hopital,adresse,capacite,image);

    bool test=H.ajouter();

    if(test)
    {
        ui->tab_hopitaux->setModel(H.afficher());
        ui->tab_hopitaux_2->setModel(H.afficher());
        ui->tab_hopitaux_3->setModel(H.afficher());
        QMessageBox::information(nullptr, QObject::tr("Succée"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    QPieSeries *series = new QPieSeries();
        series->setHoleSize(0);
        series->setPieSize(1.2);
        series->setLabelsVisible(true);
        series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

        QSqlQuery query("SELECT ADRESSE, COUNT(*) FROM HOPITAUX GROUP BY ADRESSE");
        while (query.next()) {
            QString adresse = query.value(0).toString();
            int count = query.value(1).toInt();

            QPieSlice *slice = series->append(adresse, count);
                int r = qrand() % 256;
                int g = qrand() % 256;
                int b = qrand() % 256;
                slice->setLabel(QString("ADRESSE : %1->%2").arg(adresse).arg(count));
            slice->setColor(QColor(r, g, b));
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Hôpitaux par Adresse");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setParent(ui->horizontalFrame);
        chartView->resize(ui->horizontalFrame->size());

}

void gestionhopitaux::on_boutton_supprimer_clicked()
{
    int id_hopital=ui->id_hopital_2->text().toInt();
    bool test=H.supprimer(id_hopital);
    if(test)
    {
        ui->tab_hopitaux->setModel(H.afficher());
        ui->tab_hopitaux_2->setModel(H.afficher());
        ui->tab_hopitaux_3->setModel(H.afficher());
        QMessageBox::information(nullptr, QObject::tr("Succée"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Echec"),
                    QObject::tr("Suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    QPieSeries *series = new QPieSeries();
        series->setHoleSize(0);
        series->setPieSize(1.2);
        series->setLabelsVisible(true);
        series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

        QSqlQuery query("SELECT ADRESSE, COUNT(*) FROM HOPITAUX GROUP BY ADRESSE");
        while (query.next()) {
            QString adresse = query.value(0).toString();
            int count = query.value(1).toInt();

            QPieSlice *slice = series->append(adresse, count);
                int r = qrand() % 256;
                int g = qrand() % 256;
                int b = qrand() % 256;
                slice->setLabel(QString("ADRESSE : %1->%2").arg(adresse).arg(count));
            slice->setColor(QColor(r, g, b));
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Hôpitaux par Adresse");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setParent(ui->horizontalFrame);
        chartView->resize(ui->horizontalFrame->size());
}


void gestionhopitaux::on_boutton_modifier_clicked()
{


        int id_hopital =ui->id_hopital_3->text().toInt();
        QString nom_hopital=ui->nom_hopital_2->text();
        QString adresse=ui->adresse_2->text();
        int capacite=ui->capacite_2->text().toInt();
        QImage image;
        Hopitaux H(id_hopital,nom_hopital,adresse,capacite,image);


        bool test=H.modifier();
        if(test)
        {
            ui->tab_hopitaux->setModel(H.afficher());
            ui->tab_hopitaux_2->setModel(H.afficher());
            ui->tab_hopitaux_3->setModel(H.afficher());
            QMessageBox::information(nullptr,QObject::tr("Succée"), QObject::tr("Modification effectué \n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else {
            QMessageBox::critical(nullptr,QObject::tr("Echec"),  QObject::tr("Modification non effectué \n"  "Click Cancel to exit."),QMessageBox::Cancel);

        }

        QPieSeries *series = new QPieSeries();
            series->setHoleSize(0);
            series->setPieSize(1.2);
            series->setLabelsVisible(true);
            series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

            QSqlQuery query("SELECT ADRESSE, COUNT(*) FROM HOPITAUX GROUP BY ADRESSE");
            while (query.next()) {
                QString adresse = query.value(0).toString();
                int count = query.value(1).toInt();

                QPieSlice *slice = series->append(adresse, count);
                    int r = qrand() % 256;
                    int g = qrand() % 256;
                    int b = qrand() % 256;
                    slice->setLabel(QString("ADRESSE : %1->%2").arg(adresse).arg(count));
                slice->setColor(QColor(r, g, b));
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Hôpitaux par Adresse");
            chart->setAnimationOptions(QChart::SeriesAnimations);

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setParent(ui->horizontalFrame);
            chartView->resize(ui->horizontalFrame->size());



}


void gestionhopitaux::on_tab_hopitaux_2_clicked(const QModelIndex &index)
{

        int val=ui->tab_hopitaux_2->model()->data(index).toInt();
        QString val_string=QString::number(val);
            QSqlQuery qry;

            qry.prepare("select * from HOPITAUX where ID_HOPITAUX=:v ");
            qry.bindValue(":v",val_string);
            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->id_hopital_3->setText(qry.value(0).toString());
                    ui->nom_hopital_2->setText(qry.value(1).toString());
                    ui->adresse_2->setText(qry.value(2).toString());
                    ui->capacite_2->setText(qry.value(3).toString());

                }

            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }

}
void gestionhopitaux::on_tab_hopitaux_3_clicked(const QModelIndex &index)
{

        int val=ui->tab_hopitaux_3->model()->data(index).toInt();
        QString val_string=QString::number(val);
            QSqlQuery qry;

            qry.prepare("select * from HOPITAUX where ID_HOPITAUX=:v ");
            qry.bindValue(":v",val_string);
            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->id_hopital_2->setText(qry.value(0).toString());

                }

            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }

}



void gestionhopitaux::on_search_button_clicked()
{
    int h=ui->search->text().toInt();
    QString o=ui->search->text();
    QString p=ui->search->text();
    int i=ui->search->text().toInt();

    ui->tab_hopitaux->setModel(H.recherchee(h,o,p,i));
}





void gestionhopitaux::on_button_pdf_clicked()
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
                painter.drawText(1700,1200,"LISTES DES HOPITAUX");
                painter.setPen(Qt::darkBlue);//titre
                painter.setFont(QFont("Cambria", 20));
                painter.drawText(2300,1500,"Smart Ambulance Agency");
                painter.setFont(QFont("Cambria", 10));
                painter.drawText(3000,1800,"Emergency Respnse Unit (E.R.U)");
                painter.setPen(Qt::black);
                painter.setFont(QFont("Cambria", 10));
                painter.drawText(0,2500,"Responsable des Hopitaux: Mohamed Rayan Fathallah");
                painter.setPen(Qt::black);
                painter.setFont(QFont("Cambria",14));
                painter.drawRect(0,3000,9600,500);
                painter.setFont(QFont("Cambria",11));
                painter.drawText(200,3300,"ID_HOPITAUX");
                painter.drawText(1300,3300,"NOM");
                painter.drawText(2700,3300,"ADRESSE");
                painter.drawText(4000,3300,"CAPACITE");
                painter.drawText(5400,3300,"IMAGE");

                QSqlQuery query;
                query.prepare("select * from HOPITAUX");
                query.exec();
                while (query.next())
                {
                    painter.drawText(200,i,query.value(0).toString());
                    painter.drawText(1300,i,query.value(1).toString());
                    painter.drawText(2700,i,query.value(2).toString());
                    painter.drawText(4000,i,query.value(3).toString());
                    painter.drawText(5400,i,query.value(4).toString());



                    i = i + 500;
                }

                QImage image(":/new/prefix1/ambulancee.png");
                                        painter.drawImage(QRect(100, 100, 600, 600), image);

                doc.print(&printer);
}



void gestionhopitaux::on_search_cursorPositionChanged(int , int )
{
    ui->tab_hopitaux->setModel(H.recherche(ui->search->text()));

            QString test =ui->search->text();

            if(test=="")
            {
                ui->tab_hopitaux->setModel(H.afficher());//refresh
            }
}





void gestionhopitaux::on_comboBox_activated(const QString &arg1)
{
    if (arg1=="ID_HOPITAUX")
            ui->tab_hopitaux->setModel(H.trier(1));
        if (arg1=="NOM")
            ui->tab_hopitaux->setModel(H.trier(2));
        if (arg1=="ADRESSE")
            ui->tab_hopitaux->setModel(H.trier(3));
}



void gestionhopitaux::on_send_clicked()
{
    QTextStream T(mSocket);
    T << ui->nickname->text() << ": " << ui->message->text();
    mSocket->flush();
    ui->message->clear();
}

void gestionhopitaux::on_bind_clicked()
{
    DuMessengerConnectionDialog D(this);
    if (D.exec() == QDialog::Rejected) {
        return;
    }
    mSocket->connectToHost(D.hostname(), D.port());
}

bool gestionhopitaux::update_label()
{
    data=A.read_from_arduino();
    getTemp=A.read_from_arduino();

    if(data=="1")
     {
        ui->label_14->setText("ON");
        QSqlQuery query;
        query.prepare("INSERT INTO HISTORIQUE (ALARME,TEMPERATURE) ""VALUES ('branchement ouvert 27/4/2023','')");



        return query.exec();

     }
    else if (data=="0")
     {
        ui->label_14->setText("OFF");
     }
ui->tab_hopitaux_4->setModel(H.afficher_pointage());



}









void gestionhopitaux::on_pushButton_clicked()
{
    A.write_to_arduino("1");
}

void gestionhopitaux::on_pushButton_2_clicked()
{
    A.write_to_arduino("0");
}



void gestionhopitaux::on_pushButton_3_clicked()
{
    QWidget window;
    QString fileName = QFileDialog::getOpenFileName(&window, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
            if (!fileName.isEmpty()) {
                QPixmap pixmap(fileName);
                ui->label_17->setPixmap(pixmap);
            }
}
