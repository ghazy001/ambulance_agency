#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <employee.h>
#include <authentification.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_ajouter_e_clicked();

    void on_supprimer_e_clicked();

void updateChart() ;

    void on_UPDATE_clicked();

    void on_tab_employe_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();



    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();


    void on_lineEdit_5_cursorPositionChanged(int arg1, int arg2);

    void on_sendBtn_clicked();

    void on_browseBtn_clicked();

    void on_tab_employe_activated(const QModelIndex &index);

    void on_pushButton_8_clicked();

    void on_tab_employe_2_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    employee emp;
    authentification aut;
    QStringList files;
    void mailSent(QString);

};

#endif // MAINWINDOW_H
