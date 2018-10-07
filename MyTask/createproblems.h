#ifndef CREATEPROBLEMS_H
#define CREATEPROBLEMS_H

#include <QDialog>
#include <QString>
#include "grade.h"
#include <QStack>
#include <QQueue>
#include <QButtonGroup>

namespace Ui {
class createProblems;
}

class createProblems : public QDialog
{
    Q_OBJECT

public:
    int count,n,type=1; double fs=0.0;
    QString tempPro;
    QButtonGroup *ansGroup;
    explicit createProblems(QWidget *parent = 0);
    ~createProblems();

private:
    Ui::createProblems *ui;

public slots:
    void on_next();
    void on_ansGroup();

public:
    grade g;
    QString create();

    QQueue<QString> Split(const QString& exp);          //分离前缀
    QQueue<QString> Transfer(QQueue<QString>& exp);     //将中缀队列转换为后缀队列
    QString Calculate(QQueue<QString>& exp);            //将后缀队列计算出结果

    QString Calculate(QString& l,QString& op,QString& r );
    QString ValidNum(QString str);
    QString Result(const QString& exp);
};

#endif // CREATEPROBLEMS_H
