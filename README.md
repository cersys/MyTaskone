## 中小学自动出题系统PC端

### 本系统是基于QT Creator 4.5.2开发环境，开发语言C++，能够实现用户注册，发送短信验证码，用户登陆，用户选择题目类型和数量，显示用户本次答题基本功能。支持对用户账号查重，账号密码以及验证码的准确性检测
### 启动系统方式一：双击打开demo文件夹下的MyTask.exe，注册后登录，即可使用
### 启动方式二：双击 MyTask文件夹中 MyTask.pro （前提：电脑需要安装QT）

### 0x01 系统登陆页面
#### methon QLineEdit & QPushButton
#### file login.h & login.cpp & login.ui

#### get

* filed: 账号（手机号）
* filed: 密码

```实例：
{
    "账户": "18692279036",
    "密码": "zxj1234",
}
```

#### 点击 "登录"，成功时跳转至主菜单页面，失败时提示 “账户或密码错误” （此时需要注册新用户，或检查一下是否输入错误）

#### 点击 "注册"，跳转至注册界面


### 0x02 系统注册页面
#### methon QLineEdit & QPushButton & 短信API
#### file regwindow.h & regwindow.cpp regwindow.ui

### get

* filed: 用户名
* filed：手机号
* filed：密码
* filed：验证码

```实例：
{
    "用户名": "xiaoZhao",
    "手机号": "18692279036",
    "密码": "zxj1234",
    "验证码": "12580“,
}
```
#### 点击 "获取短信验证码",成功时会弹出提示框"正在发送验证码",等待手机接收得验证码，填入框内
#### 点击 "注册",成功时会弹框提示"注册成功，点击跳转至登陆界面",
#### 点击 "注册"，失败时如果弹出"该手机号已被注册",则需要更改手机号注册，如果提示"验证码错误",需要检查验证码输入是否正确

### 0x03 主菜单页面
#### methon QLineEdit & QPushButton
#### file mainwindow.h & mainwindow.cpp & mainwindow.ui

### get
* filed: 题目数量
* filed: 题目类型

```实例：
{
    "题目数量": "15",
    "题目类型": "小学",
}
```
#### 点击 "小学"或"初中","高中"  跳转到生成题目的界面,生成对应类型题目

### 0x04 生成题目页面
#### methon QLineEdit & QPushButton & QRadioButton
#### file createproblems.h & createproblems.cpp & createproblems.ui

```实例：
{
    "题目": "1+2+3 = ",
    "选项1": "4",
    "选项2": "5",
    "选项3": "6",
    "选项4": "7",
}
```
#### 点击选项旁边按钮会记录用户选择的答案，首次四个按钮是没有被选，之后的题目，每次进入选项会和上次选的一样，用户需要重新点击要选的答案
#### 点击"下一题" 继续生成题目，当全部题目数量超过输入时，跳转至分数页面


### 0x05 分数页面
#### methon QLineEdit & QPushButton
#### file grade.h & grade.cpp & geade.ui

```实例：
{
    "分数": "50",
}
```
#### 点击 "查看分数" 显示用户所得分数
#### 点击 "退出" 退出本系统




