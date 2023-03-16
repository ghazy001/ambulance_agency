#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "hopitaux.h"
#include "connection.h"
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

private slots:
    void on_boutton_ajouter_clicked();

    void on_boutton_supprimer_clicked();

    void on_boutton_modifier_clicked();

private:
    Ui::MainWindow *ui;
    Hopitaux H;
};

#endif // MAINWINDOW_H
