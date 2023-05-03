#ifndef GESTIONPATIENT_H
#define GESTIONPATIENT_H

#include <QDialog>

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <string>










#include <QMainWindow>
#include <QSqlQueryModel>
#include "patient.h"




#include <QDialog>

#include <QMainWindow>

#include <authentification.h>
#include"arduino.h"


namespace Ui {
class gestionpatient;
}


class gestionpatient : public QDialog
{
    Q_OBJECT

public:
    explicit gestionpatient(QWidget *parent = nullptr);
    ~gestionpatient();

private slots:






    void on_tabpatient_clicked(const QModelIndex &index);



    void on_tri_clicked();

    void on_mod6_cursorPositionChanged(int arg1, int arg2);


    void on_pdf_clicked();

    void on_captcha_clicked();

    void on_tabpatient_activated(const QModelIndex &index);

    void on_tableView_activated(const QModelIndex &index);

    void on_malek_clicked();

    void on_tableView12_activated(const QModelIndex &index);

    void on_tabpatient_2_activated(const QModelIndex &index);

    void on_mod6_3_returnPressed();

    void on_salma_activated(const QModelIndex &index);

    void on_malek_2_activated(const QModelIndex &index);

    void on_excel_clicked();

    void on_label_2_linkActivated(const QString &link);

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_malek12_clicked();

    void on_lineEdit45_textEdited(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_insert_2_clicked();

    void on_suppbuton_2_clicked();

    void on_modifer_2_clicked();

private:
    Ui::gestionpatient *ui;
    Patient E;

};

#endif // MAINWINDOW_H
