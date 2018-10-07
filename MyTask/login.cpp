#include "login.h"
#include "ui_login.h"
#include "regwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(on_clicked2()));
    this->setWindowTitle("中小学生出题系统");
}

login::~login()
{
    //delete ui;
}

void login::on_clicked(){
    QString dirNow = qApp->applicationDirPath();
    dirNow += "\\account.txt";
    QFile file(dirNow);
     if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
         bool flag = true;
           while(!file.atEnd()){
                QByteArray ph = file.readLine();
                QByteArray pwd = file.readLine();
                QString strph(ph); QString strpwd(pwd);
                QString tempph = ui->lineEdit->text() + "\n";
                QString tempwd = ui->lineEdit_2->text() + "\n";
                if(tempph == strph && tempwd == strpwd){
                    file.close();
                    flag = false;
                    this->hide();
                    q.show();
                }

           }
           if(flag){
               QMessageBox warnning;
               warnning.setText("账户或密码错误");
               warnning.exec();
               ui->lineEdit->clear();
               ui->lineEdit_2->clear();
           }
     }
}

void login::on_clicked2(){
    this->hide();
    r = new regWindow();
    r->show();
}
