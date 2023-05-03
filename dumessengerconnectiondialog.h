#ifndef DUMESSENGERCONNECTIONDIALOG_H
#define DUMESSENGERCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DuMessengerConnectionDialog;
}


class DuMessengerConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DuMessengerConnectionDialog(QWidget *parent = nullptr);
    ~DuMessengerConnectionDialog();
    QString hostname() const;
    quint16 port() const;

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::DuMessengerConnectionDialog *ui;
    QString mHostname;
    quint16 mPort;
};

inline QString DuMessengerConnectionDialog::hostname() const
{
    return mHostname;
}

inline quint16 DuMessengerConnectionDialog::port() const
{
    return  mPort;
}

#endif // DUMESSENGERCONNECTIONDIALOG_H
