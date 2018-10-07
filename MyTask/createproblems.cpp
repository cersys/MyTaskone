#include "createproblems.h"
#include "ui_createproblems.h"
#include "QString"
#include "QDateTime"
#include <QDebug>

createProblems::createProblems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createProblems)
{
    ui->setupUi(this);
    this->setWindowTitle("写题ing");
    ansGroup = new QButtonGroup(this);
    ansGroup->addButton(ui->radioButton,0);
    ansGroup->addButton(ui->radioButton_2,1);
    ansGroup->addButton(ui->radioButton_3,2);
    ansGroup->addButton(ui->radioButton_4,3);
   // ui->radioButton->setChecked(true);


    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_next()));
    connect(ui->radioButton,SIGNAL(clicked(bool)),this,SLOT(on_ansGroup()));
    connect(ui->radioButton_2,SIGNAL(clicked(bool)),this,SLOT(on_ansGroup()));
    connect(ui->radioButton_3,SIGNAL(clicked(bool)),this,SLOT(on_ansGroup()));
    connect(ui->radioButton_4,SIGNAL(clicked(bool)),this,SLOT(on_ansGroup()));

    QString str = create();
    ui->lineEdit_5->setText(str+" = ");
    QString ss = Result(str);
    ui->lineEdit_3->setText(ss);
    double ssint = ss.toDouble();
    ui->lineEdit->setText(QString::number(ssint+1.0));
    ui->lineEdit_2->setText(QString::number(ssint-1.0));
    ui->lineEdit_4->setText(QString::number(ssint*(-1.0)));
}

createProblems::~createProblems()
{
    delete ui;
}

QString createProblems::create(){          //生成题目
    QString op[20] = {"+","-","*","/","^2","^0.5","sin","cos","tan"};

    QString ret;
    int seed = QDateTime::currentDateTime().time().second();
    srand(seed);
    int tempn = rand()%(6-1+1)+1;
    if(this->type == 1){
        for(int i=1; i<tempn; ++i){
            ret += QString::number(rand()%101);
            ret += op[rand()%4];
        }
        ret += QString::number(rand()%101);
        tempPro = ret;
    }else if(type == 2){
        for(int i=1; i<tempn; ++i){
            double shu = rand()%101;
            ret += QString::number(shu);
            int tempop = rand()%6;
            if(tempop>=4){
                ret += op[tempop];
                if(tempop==4){
                    tempPro += QString::number(shu*shu);
                }else{
                    tempPro += QString::number(sqrt(shu));
                }
                tempop = rand()%4;
                ret += op[tempop];
                tempPro += op[tempop];
            }else {
                tempPro += QString::number(shu);
                tempPro += op[tempop];
                ret += op[tempop];
            }
        }
        double shu = rand()%101;
        ret += QString::number(shu); ret += "^2";
        tempPro += QString::number(shu*shu);
    }else{
        for(int i=1; i<tempn; ++i){
            double shu = rand()%101;
            ret += QString::number(shu);
            int tempop = rand()%9;
            if(tempop>=4 && tempop <=5){
                ret += op[tempop];
                if(tempop==4){
                    tempPro += QString::number(shu*shu);
                }else{
                    tempPro += QString::number(sqrt(shu));
                }
                tempop = rand()%4;
                ret += op[tempop];
                tempPro += op[tempop];
            }else if(tempop>5){
                int ttop = rand()%4;
                tempPro += QString::number(shu);
                ret += op[ttop]; tempPro += op[ttop];
                ret += op[tempop];
                shu = rand()%101;
                ret += QString::number(shu);
                if(tempop==6) tempPro += QString::number(sin(shu/180.0*acos(-1)));
                else if(tempop==7) tempPro += QString::number(cos(shu/180.0*acos(-1)));
                else tempPro += QString::number(tan(shu/180.0*acos(-1)));
                i++;
                tempop = rand()%4;
                ret += op[tempop]; tempPro += op[tempop];
            }else {
                tempPro += QString::number(shu);
                tempPro += op[tempop];
                ret += op[tempop];
            }
        }
        double shu = rand()%101;
        ret += "sin"; ret += QString::number(shu);
        tempPro += QString::number(sin(shu/180.0*acos(-1)));
    }
    return ret;
}

QQueue<QString> createProblems::Split(const QString& exp)          //分离前缀
{
    QQueue<QString> ret;
    QString num="";

    for(int i=0;i<exp.length();i++)
    {
        if( (exp[i]=='.') || ( (exp[i]>='0') && (exp[i]<='9') ))    //判断小数点和数字
        {
            num += exp[i];
        }

        else if(exp[i]== '(' || exp[i]== ')' || exp[i]== '*' || exp[i]== '/'  )
        {
            if(!num.isEmpty())
            {
                ret.enqueue(num);        //将数字入队列
                num.clear();
            }
            ret.enqueue(exp[i]);
        }

        else if(exp[i]== '+' || exp[i]== '-')           // + - 需要特殊处理
        {
            if(i==0)       //表达式开头,说明是正负号
            {
             num+= exp[i];
            }

            else if(exp[i-1]=='(' || exp[i-1]=='+' || exp[i-1]=='-' || exp[i-1]=='*' || exp[i-1]=='/')
            {
             num+= exp[i];
            }
            else        //否则是加减运算符
            {
                if(!num.isEmpty())
                {
                    ret.enqueue(num);        //将数字入队列
                    num.clear();
                }
             ret.enqueue(exp[i]);
            }
        }
    }

    if(!num.isEmpty())         //遍历完成,判断是否还有数字
    {
        ret.enqueue(num);
        num.clear();
    }
return ret;
}

QQueue<QString> createProblems::Transfer(QQueue<QString>& exp)     //将中缀队列转换为后缀队列
{
    QStack<QString> stack;
    QQueue<QString> ret;
    bool num_ok;
    QString symbol;

    while(!exp.isEmpty())
    {
      symbol = exp.dequeue();   //出队列
      symbol.toDouble(&num_ok);

      if(num_ok==true)          //数字
      {
           stack.push(symbol);
      }

      else if(symbol=="+"||symbol=="-")
      {
          while(!stack.isEmpty() &&(stack.top()!="("))
          {
              ret.enqueue(stack.pop());     //取出栈顶运算符并入队列
          }
          stack.push(symbol);
      }

      else if(symbol=="*"||symbol=="/")
      {
          while(!stack.isEmpty() && (stack.top()!="(") && (stack.top()!="+") && (stack.top()!="-"))
          {
              ret.enqueue(stack.pop());     //取出栈顶运算符并入队列
          }
          stack.push(symbol);
      }

      else if(symbol == "(")
      {
         stack.push(symbol);
      }

      else if(symbol ==")")
      {
          while(!stack.isEmpty() && (stack.top()!="("))
          {
              ret.enqueue(stack.pop());     //取出栈顶运算符并入队列
          }
          if(stack.top()=="(")
            stack.pop();
      }
    }

    while(!stack.isEmpty()&& (stack.top()!="("))         //遍历完成,判断栈里是否为空
    {
       ret.enqueue(stack.pop());     //取出栈顶运算符并入队列
    }return ret;
}

QString createProblems::ValidNum(QString str)
 {
    QString num;

    if(str.indexOf(".")== -1) //判断是否小数
        return str;

    while(str.length()>1)   //避免0被去掉
    {
         num=str.right(1);
         if(num=="."||num=="0")
         {
             str.chop(1);
             if(num==".")
                 return  str;
         }
         else
             return str;
    }
    return str;
}


QString createProblems::Calculate(QString& l,QString& op,QString& r )
{
    double left,right,res;
    QString ret="";
    left = l.toDouble();
    right = r.toDouble();
    if(op == "+")
    {
        res = left + right;
    }

    else if(op == "-")
    {
        res = left - right;
    }

    else if(op == "*")
    {
        res = left * right;
    }

    else if(op == "/")
    {
        if( (right>(-0.000000000000001)) && (right<(0.000000000000001)) )   //判断除数为0
            return NULL;
        else
            res = left/right;
    }

    ret.sprintf("%f",res);
    return ret;
}

QString createProblems::Calculate(QQueue<QString>& exp)            //将后缀队列计算出结果
{
    QStack<QString> stack;
    QString symbol,L,R,op,ret;
    bool num_ok;

    while(!exp.isEmpty())
    {
      symbol = exp.dequeue();   //出队列
      symbol.toDouble(&num_ok);

      if(num_ok==true)      //数字
      {
        stack.push(symbol);
      }
      else                  //运算符
      {
          if(stack.size()<2)
              return "Error";

          R= stack.pop();
          L= stack.pop();
          ret = Calculate(L,symbol,R );
          if(ret==NULL)
              return ret;

          stack.push(ret);
      }
    }
    if(stack.size()==1) //遍历完成,结果只有一个
    {
         return ValidNum(stack.pop());
    }
    else
    {return "Error";
    }
}

QString createProblems::Result(const QString& exp)
{
      QQueue<QString> q=Split(exp); //分离中缀
      q=Transfer(q);                //转换为后缀
      return Calculate(q);          //返回结果
}

void createProblems::on_ansGroup(){
    if(ansGroup->checkedId()==0) this->fs++;
}

void createProblems:: on_next(){
    tempPro.clear();
    QString problem = create();

    QString ans = Result(tempPro);
    problem += " =";
    ui->lineEdit_5->setText(problem);
    ui->lineEdit->setText(ans);
    double ansint = ans.toDouble();
    ui->lineEdit_2->setText(QString::number(ansint+1.0));
    ui->lineEdit_3->setText(QString::number(ansint-1.0));
    ui->lineEdit_4->setText(QString::number(ansint*(-1.0)));
    n++;
    if(n==(count)){
        this->hide();
        g.fshu = this->fs/count;
        qDebug()<<g.fshu<<endl;
        g.show();
    }
}
