#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "createproblems.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_click1();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

public:
    int num;
    createProblems c;
};

#endif // MAINWINDOW_H
