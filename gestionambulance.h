#ifndef GESTIONAMBULANCE_H
#define GESTIONAMBULANCE_H
#include "ambulance.h"
#include "arduino.h"
#include <QMainWindow>
#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDialog>

namespace Ui {
class gestionAmbulance;
}

class gestionAmbulance : public QDialog
{
    Q_OBJECT

public:
    explicit gestionAmbulance(QWidget *parent = nullptr);
    ~gestionAmbulance();
public slots:
    void gestionArduino();
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
    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_5_clicked();

    void on_updateNote_clicked();

    void on_deleteNote_clicked();

    void on_btn_add_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::gestionAmbulance *ui;
    ambulance A;
    QString apikey="PfQGOhn3oe6WXawwZWA2CWgobAGg";
    QStandardItemModel  *m_playListModel;   // Data Model for Playlist
       QMediaPlayer        *m_player;
       QMediaPlaylist      *m_playlist;
       Arduino AR;
           QString datafromArduino;
           QMetaObject::Connection A_connection;
};

#endif // GESTIONAMBULANCE_H
