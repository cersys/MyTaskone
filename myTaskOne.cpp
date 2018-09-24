//本代码使用了C++11标准，编译是需要确定编译器是否支持C++11标准 

#include <bits/stdc++.h>
#include <direct.h>

using namespace std;

struct User{
    int type;
    string name;
    string password;
}user[20];
string name,pwd;
string op[20] = {"+","-","*","/","^2","^0.5","cos","sin","tan"};

char path[250];
//获取当前时间 
string getTime(){
	time_t timep;
	time (&timep);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y-%m-%d-%H-%M-%S",localtime(&timep));
	return tmp;
}
//获取存放文件路径 
void getPath(string p){
	string dir = ".\\"; dir.append(p);
	if(access(dir.c_str(),0) == -1){
		int flag = mkdir(dir.c_str());
		if(flag==-1) cout<<"Error！Can not make directory!"<<endl;
	}
	dir.append("\\"); dir.append(getTime());
	dir.append(".txt");
	
	for(int i=0; i<dir.size(); ++i) path[i] = dir[i];
}
//是否切换出题类型 
int isChange(string a){
	if(a == "切换为小学") return 1;
	else if(a == "切换为初中") return 2;
	else if(a == "切换为高中") return 3;
	return 0; 
}
//生成带括号的题目 
string makeKh(){
	string ret = to_string(rand()%100+1)+" * ((" + to_string(rand()%100+1) + " + "  + to_string(rand()%100+1) + ") / "
				+  to_string(rand()%100+1) + ") = ";
	return ret;
}

//比较是否有重复的题目
bool cmp(string p, string s){
	
} 
//初始化用户 
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
//生成题目 
void createProblems(int type,int num){
	int cas = 0;
    if(type==1){ 						//小学 
    	getPath(name);
        freopen(path,"w",stdout);
        srand((int)time(0));
        while(num--){
        	cout<<++cas<<": ";
        	int kh = rand()%4;
          	if(kh==3) cout<<makeKh()<<endl;
          	else{
          		int t = rand()%(5-2+1)+1;
            	while(t--){
                	cout<<rand()%100+1<<" "<<op[rand()%4]<<" ";
            	}
            	cout<<rand()%100+1<<" ="<<endl;
			}
//	        if(!cmp(name,path)){
//	        	deleteTxt(path);
//			}else break;
        }
    }else if(type==2){ 					//初中 
        getPath(name);
        freopen(path,"w",stdout);
        srand((int)time(0));
        while(num--){
        	cout<<++cas<<": ";
            int t = rand()%(5-2+1)+1;
            while(t--){
                cout<<rand()%100+1<<" ";
                int optmp = rand()%6;
                if(optmp>=4) cout<<op[optmp]<<" "<<op[rand()%4]<<" ";
                else cout<<op[optmp]<<" ";
            }
            cout<<rand()%100+1<<op[rand()%(5-4+1)+4]<<" ="<<endl;
        }
    }else{ 							//高中 
        getPath(name);
        freopen(path,"w",stdout);
        srand((int)time(0));
        while(num--){
        	cout<<++cas<<": ";
            int t = rand()%(4-2+1)+1;
            while(t--){
                cout<<rand()%100+1<<" ";
                int optmp = rand()%9;
                if(optmp>=4&&optmp<6) cout<<op[optmp]<<" "<<op[rand()%4]<<" ";
                else if(optmp >=6) cout<<op[rand()%4]<<" "<< op[optmp] <<rand()%361<<" "<<op[rand()%4]<<" ";
                else cout<<op[optmp]<<" ";
            }
            cout<<op[rand()%(8-6+1)+6]<<rand()%361<<" ="<<endl;
        }
    }
}


int main(int argc, char const *argv[])
{
    init();
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
    
    string ml; int flag = 0;
    while(cin>>ml&&!isdigit(ml[0])){ 		//判断是否切换 
    	if(isChange(ml)) {
    		type = isChange(ml);
    		flag = 1;
    		cout<<"准备生成";
		    if(type==1) cout<<"小学";
		    else if(type==2) cout<<"初中";
		    else cout<<"高中";
		    cout<<"数学题目，请输入生成题目数量："<<endl;
    		break;
		}
		cout<<"请输入切换为(小学、初中或高中)三个选项中的一个"<<endl; 
	}
    int num = 0;
    if(flag) cin>>num;
    else {
    	for(int i=0; i<ml.size(); ++i){
    		num = num*10 + (ml[i] - '0');
		}
	}
    do{
        if(num>=10 && num <=30) break;
        cout<<"输入的题目数量无效，请重新输入（有效范围:[10,30]): "<<endl;
    }while(cin>>num);

	//开始生成题目 
	createProblems(type,num);
    return 0;
}
