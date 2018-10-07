#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QDialog>
#include "login.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QString>

namespace Ui {
class regWindow;
}

class regWindow : public QDialog
{
    Q_OBJECT

public:
    explicit regWindow(QWidget *parent = 0);
    ~regWindow();
    bool reg();
    QNetworkAccessManager *nam;
    QString yzm;

private slots:
    void on_message_clicked();
    void on_reg_clicked();
    void finishedSlot(QNetworkReply *reply);
private:
    Ui::regWindow *ui;

    login l;
};

#endif // REGWINDOW_H
