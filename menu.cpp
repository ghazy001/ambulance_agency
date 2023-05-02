#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"
#include "gestionambulance.h"

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_2_clicked()
{
    MainWindow *w;
    w = new MainWindow(this);
    w -> show();
}

void menu::on_pushButton_clicked()
{
    gestionAmbulance *w;
    w = new gestionAmbulance(this);
    w -> show();
}

void menu::on_pushButton_3_clicked()
{
    gestionemploye *w;
    w = new gestionemploye(this);
    w -> show();
}
