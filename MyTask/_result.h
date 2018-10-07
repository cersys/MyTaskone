#ifndef RESULT_H
#define RESULT_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class result;
}

class result : public QDialog
{
    Q_OBJECT

public:
    explicit result(QWidget *parent = 0);
    ~result();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::result *ui;

public:
    MainWindow m;
};

#endif // RESULT_H
