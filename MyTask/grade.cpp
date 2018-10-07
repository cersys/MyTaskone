#include "grade.h"
#include "ui_grade.h"
#include <QDebug>

grade::grade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::grade)
{
    ui->setupUi(this);
    this->setWindowTitle("中小学生出题系统");
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_clicked()));
}

grade::~grade()
{
    delete ui;
}




void grade::on_pushButton_2_clicked()
{
    this->hide();
}

void grade::on_pushButton_clicked()
{
    ui->lineEdit->setText(QString::number(fshu*100));
}
