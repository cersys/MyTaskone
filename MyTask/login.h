#ifndef LOGIN_H
#define LOGIN_H

class regWindow;
#include <QDialog>
#include "mainwindow.h"




namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private:
    Ui::login *ui;

public slots:
    void on_clicked();
    void on_clicked2();

private:
    MainWindow q;
    regWindow *r;
};

#endif // LOGIN_H
