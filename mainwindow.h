#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ambulance.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_insertButton_2_clicked();
    bool postrequest(QString smsmsg,QString phonenumber);
    void on_deleteButton_clicked();

    void on_pushButton_clicked();



    void on_pushButton_2_clicked();

    void on_tab_ambulance_clicked(const QModelIndex &index);



    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_chercher_textEdited(const QString &arg1);



private:
    Ui::MainWindow *ui;
    ambulance A;
    QString apikey="JUAkmCxtVs9zL422RVDQY6sHahL3";
};
#endif // MAINWINDOW_H
