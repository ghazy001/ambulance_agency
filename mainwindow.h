#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ambulance.h"

#include <QMainWindow>
#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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





    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_5_clicked();

    void on_updateNote_clicked();

    void on_deleteNote_clicked();

    void on_btn_add_clicked();



private:
    Ui::MainWindow *ui;
    ambulance A;
    QString apikey="PfQGOhn3oe6WXawwZWA2CWgobAGg";
    QStandardItemModel  *m_playListModel;   // Data Model for Playlist
       QMediaPlayer        *m_player;
       QMediaPlaylist      *m_playlist;
};
#endif // MAINWINDOW_H
