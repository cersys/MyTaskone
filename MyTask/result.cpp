#include "_result.h"
#include "ui_result.h"

result::result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);
}

result::~result()
{
    delete ui;
}

void result::on_pushButton_clicked()
{
    this->hide();
    m.show();
}

void result::on_pushButton_2_clicked()
{
    this->hide();
    return ;
}
