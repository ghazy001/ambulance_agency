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

    void on_deleteButton_clicked();

    void on_pushButton_clicked();



    void on_pushButton_2_clicked();

    void on_tab_ambulance_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    ambulance A;
};
#endif // MAINWINDOW_H
