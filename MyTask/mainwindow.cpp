#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_click1()));
    this->setWindowTitle("主菜单");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: on_click1()
{
    QString n1 = ui->lineEdit->text();
    this->num = n1.toInt();
    this->hide();
    c.count = this->num;
    c.type = 2;
    c.n = 0;
    c.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString n1 = ui->lineEdit->text();
    this->num = n1.toInt();
    this->hide();
    c.count = this->num;
    c.type = 1;
    c.n = 0;
    c.show();
}



void MainWindow::on_pushButton_3_clicked()
{
    QString n1 = ui->lineEdit->text();
    this->num = n1.toInt();
    this->hide();
    c.count = this->num;
    c.type = 3;
    c.n = 0;
    c.show();
}
