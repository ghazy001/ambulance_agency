#ifndef GESTIONEMPLOYE_H
#define GESTIONEMPLOYE_H

#include <QDialog>

#include <QMainWindow>
#include <employee.h>
#include <authentification.h>
#include"arduino.h"
namespace Ui {
class gestionemploye;
}

class gestionemploye : public QDialog
{
    Q_OBJECT

public:
    explicit gestionemploye(QWidget *parent = nullptr);
    ~gestionemploye();

private slots:


    void on_ajouter_e_clicked();

    void on_supprimer_e_3_clicked();

void updateChart() ;

    void on_UPDATE_3_clicked();

    void on_tab_employe_5_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();



    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();
void on_pushButton_13_clicked();
    void update_label();
    void on_lineEdit_7_cursorPositionChanged(int arg1, int arg2);

    void on_sendBtn_3_clicked();

    void on_browseBtn_3_clicked();

    void on_tab_employe_activated(const QModelIndex &index);

    void on_pushButton_8_clicked();

    void on_tab_employe_6_clicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_ajouter_e_3_clicked();

    void on_pushButton_15_clicked();

private:
    Ui::gestionemploye *ui;
    employee emp;
    authentification aut;
    QStringList files;
    void mailSent(QString);
    Arduino A ;
    QByteArray data;


};


#endif // GESTIONEMPLOYE_H
