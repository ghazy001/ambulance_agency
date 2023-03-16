#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <equipement.h>

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



   // void on_pushButton_clicked();

    void on_ajouter_e_clicked(bool checked);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    equipement eq;
};

#endif // MAINWINDOW_H
