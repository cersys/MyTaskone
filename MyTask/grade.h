#ifndef GRADE_H
#define GRADE_H

#include <QDialog>

namespace Ui {
class grade;
}

class grade : public QDialog
{
    Q_OBJECT

public:
    double fshu=0.0;
    explicit grade(QWidget *parent = 0);
    ~grade();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::grade *ui;

};

#endif // GRADE_H
