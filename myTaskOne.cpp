#include <bits/stdc++.h>

using namespace std;

struct User{
    int type;
    string name;
    string password;
}user[20];

string op[20] = {"+","-","*","/","^2","^0.5","cos","sin","tan"};

char nowtime[150];
void getTime(){
	time_t timep;
	time (&timep);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y-%m-%d-%H-%M-%S",localtime(&timep));
	strcpy(nowtime,tmp);
	int len = strlen(tmp);
	nowtime[len] = '.'; nowtime[len+1]='t'; nowtime[len+2]='x';nowtime[len+3] = 't';
}

void init(){
    user[1].type = 1; user[1].name = "张三1"; user[1].password = "123";
    user[2].type = 1; user[2].name = "张三2"; user[2].password = "123";
    user[3].type = 1; user[3].name = "张三3"; user[3].password = "123";
    user[4].type = 2; user[4].name = "李四1"; user[4].password = "123";
    user[5].type = 2; user[5].name = "李四2"; user[5].password = "123";
    user[6].type = 2; user[6].name = "李四3"; user[6].password = "123";
    user[7].type = 3; user[7].name = "王五1"; user[7].password = "123";
    user[8].type = 3; user[8].name = "王五2"; user[8].password = "123";
    user[9].type = 3; user[9].name = "王五3"; user[9].password = "123";
}

int main(int argc, char const *argv[])
{
    init();
    string name,pwd;
    int type = 0;
    cout<<"请输入用户名和密码（用一个空格隔开）: "<<endl;
    while(cin>>name>>pwd){
        int is_ok = 0;
        for(int i=1; i<=9; ++i){
            if(name==user[i].name && pwd == user[i].password) {
                type = user[i].type;
                is_ok =1;
                break;
            }
        }
        if(is_ok) break;
        cout<<"账户或密码错误，请输入正确的用户名、密码："<<endl;
    }

    cout<<"准备生成";
    if(type==1) cout<<"小学";
    else if(type==2) cout<<"初中";
    else cout<<"高中";
    cout<<"数学题目，请输入生成题目数量："<<endl;
    int num;
    while(cin>>num){
        if(num>=10 && num <=30) break;
        cout<<"输入的题目数量无效，请重新输入（有效范围:[10,30]): "<<endl;
    }

    if(type==1){
    	getTime();
        freopen(nowtime,"w",stdout);
        srand((int)time(0));
        while(num--){
            int t = rand()%(5-2+1)+1;
            while(t--){
                cout<<rand()%100+1<<" "<<op[rand()%4]<<" ";
            }
            cout<<rand()%100+1<<"="<<endl;
        }
    }else if(type==2){
        getTime();
        freopen(nowtime,"w",stdout);
        srand((int)time(0));
        while(num--){
            int t = rand()%(5-2+1)+1;
            while(t--){
                cout<<rand()%100+1<<" ";
                int optmp = rand()%6;
                if(optmp>=4) cout<<op[optmp]<<" "<<op[rand()%4]<<" ";
                else cout<<op[optmp]<<" ";
            }
            cout<<rand()%100+1<<op[rand()%(5-4+1)+4]<<"="<<endl;
        }
    }else{
        getTime();
        freopen(nowtime,"w",stdout);
        srand((int)time(0));
        while(num--){
            int t = rand()%(4-2+1)+1;
            while(t--){
                cout<<rand()%100+1<<" ";
                int optmp = rand()%9;
                if(optmp>=4&&optmp<6) cout<<op[optmp]<<" "<<op[rand()%4]<<" ";
                else if(optmp >=6) cout<<op[rand()%4]<<" "<< op[optmp] <<rand()%361<<" "<<op[rand()%4]<<" ";
                else cout<<op[optmp]<<" ";
            }
            cout<<op[rand()%(9-6+1)+6]<<rand()%361<<endl;
        }
    }
    return 0;
}
