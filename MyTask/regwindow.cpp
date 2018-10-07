#include "regwindow.h"
#include "ui_regwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QTimer>
#include <QCoreApplication>


using namespace std;
regWindow::regWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("中小学生出题系统");
    nam = new QNetworkAccessManager(this);
    QObject::connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(finishedSlot(QNetworkReply*)));
}

regWindow::~regWindow()
{
    delete ui;
}




//发送获取短信验证码，post请求

void regWindow::on_message_clicked()
{
    QMessageBox info;
    info.setText("正在发送验证码");
    info.exec();
    int seed = QDateTime::currentDateTime().time().second();
    srand(seed);
    QUrl url("http://api.tms.im/sendsms");
    QByteArray data;
    data.append("phone=");
    data.append(ui->lineEdit_2->text());
    data.append("&pass=wdz123456&templateId=20167&body=%7b%22%25code%25%22%3a%22");
    for(int i=0; i<5; ++i) yzm.append(QString::number(rand()%10));
    data.append(yzm);
    data.append("%22%7d");
    QNetworkRequest request = QNetworkRequest(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    QNetworkReply* reply = nam->post(request,data);
}

//一个单纯的测试post请求的返回函数
void regWindow::finishedSlot(QNetworkReply *reply)
{

     // Reading attributes of the reply
     // e.g. the HTTP status code
     QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
     // Or the target URL if it was a redirect:
     QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

     if (reply->error() == QNetworkReply::NoError)
     {
         QByteArray bytes = reply->readAll();  // bytes
         QString string = QString::fromUtf8(bytes);

//         ui->lineEdit_4->setText(string);
     }
     else
     {
 //
     }

     reply->deleteLater();
}

//注册函数，包含检测号码是否被注册过，验证码是否正确
bool regWindow::reg(){
    bool ret = false;
    QString dirNow = qApp->applicationDirPath();
    dirNow += "\\account.txt";
    QFile file(dirNow);
    bool exits =file.exists();
    if(!exits){
       file.open(QIODevice::WriteOnly | QIODevice::Text);
       file.close();
    }
        QString username = ui->lineEdit->text();
        QString phone = ui->lineEdit_2->text();
        QString password = ui->lineEdit_3->text();

        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            bool flag = true;
            while(!file.atEnd()){
                QByteArray line = file.readLine();
                QString str(line);
                QString tempph = phone + "\n";
                if(tempph == str){
                    QMessageBox warnning;
                    warnning.setText("该手机号已被注册");
                    warnning.exec();
                    ui->lineEdit_2->clear();
                    file.close();
                    flag = false;
                    break;
                }

            }
          //  qDebug()<<yzm<<" "<<ui->lineEdit_4->text()<<endl;
            if(yzm != ui->lineEdit_4->text() || yzm == ""){
             //  qDebug()<<"checkpoint"<<endl;
                flag = false;
                QMessageBox warnning;
                warnning.setText("验证码错误");
                warnning.exec();
                ui->lineEdit_4->clear();
            }
            if(flag){
                file.close();
                file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
                QTextStream stream(&file);
                stream << phone << "\n";
                stream << password << "\n";
                file.close();
                ret = true;
                QMessageBox info;
                info.setText("注册成功，点击跳转至登陆界面");
                info.exec();
            }
        }
        return ret;
}

//注册成功，跳转至登陆界面
void regWindow::on_reg_clicked()
{
    if(this->reg()){
        this->hide();
        l.show();
    }
}
