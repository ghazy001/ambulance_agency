#include "dumessengerconnectiondialog.h"
#include "ui_dumessengerconnectiondialog.h"


DuMessengerConnectionDialog::DuMessengerConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuMessengerConnectionDialog)
{
    ui->setupUi(this);
}

DuMessengerConnectionDialog::~DuMessengerConnectionDialog()
{
    delete ui;
}

void DuMessengerConnectionDialog::on_ok_clicked()
{
    mHostname = ui->hostname->text();
    mPort = ui->port->value();
    accept();
}

void DuMessengerConnectionDialog::on_cancel_clicked()
{
    reject();
}

