#ifndef GESTIONHOPITAUX_H
#define GESTIONHOPITAUX_H

#include <QDialog>
#include "hopitaux.h"
#include "connection.h"
#include "arduino.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpServer>

namespace Ui {
class gestionhopitaux;
}
class QTcpSocket;


class gestionhopitaux : public QDialog
{
    Q_OBJECT

public:
    explicit gestionhopitaux(QWidget *parent = nullptr);
    ~gestionhopitaux();

private slots:
    bool update_label();

    void on_boutton_ajouter_clicked();

    void on_boutton_supprimer_clicked();

    void on_boutton_modifier_clicked();

    void on_tab_hopitaux_2_clicked(const QModelIndex &index);

    void on_tab_hopitaux_3_clicked(const QModelIndex &index);

    void on_search_button_clicked();

    void on_button_pdf_clicked();

    void on_search_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_activated(const QString &arg1);

    void on_send_clicked();

    void on_bind_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::gestionhopitaux *ui;
    Hopitaux H;
    QTcpSocket *mSocket;
    QByteArray data;
    QByteArray getTemp;
    Arduino A;
    QSerialPort serialport;
};

#endif // GESTIONHOPITAUX_H


