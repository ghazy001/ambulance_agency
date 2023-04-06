#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <employee.h>

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



    void on_UPDATE_clicked();

    void on_tab_employe_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    employee emp;
};

#endif // MAINWINDOW_H
