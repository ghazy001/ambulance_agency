#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <equipement.h>
#include <arduino.h>
#include "connection.h"
#include <QMainWindow>
#include<gestionemploye.h>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QSound>
#include <QMainWindow>
#include <QPainter>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QTextEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>

#include "NotificationLayout.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void update_label();
private slots:


    void on_ajouter_e_clicked();

    void on_supprimer_e_clicked();



   // void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_tab_equipement_clicked(const QModelIndex &index);


    void on_pushButton_clicked();

    void on_qrcodegen_3_clicked();

    void on_lineEditchercher_cursorPositionChanged(int arg1, int arg2);
    void on_pushButton_success_clicked();
void on_pushButton_error_clicked();

void on_pushButton_success1_clicked();
void on_pushButton_error1_clicked();
void on_pushButton_error5_clicked();
void on_pushButton_success2_clicked();
void on_pushButton_error2_clicked();
void on_pushButton_success3_clicked();
void on_pushButton_success4_clicked();
void on_pushButton_success10_clicked();
void on_pushButton_error10_clicked();

void on_comboBox_activated(const QString &arg1);

void on_pushButton_3_clicked();

void on_stats_customContextMenuRequested(const QPoint &pos);

void on_pushButton_4_clicked();

void on_ok_clicked();

private:
    Ui::MainWindow *ui;
    equipement eq;
    NotificationLayout notificationLayout;
    Arduino A;
    QByteArray data;
};

#endif // MAINWINDOW_H
