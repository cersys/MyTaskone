//������ʹ����C++11��׼������ǰ��Ҫȷ���������Ƿ�֧��C++11��׼ 

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
//��ȡ��ǰʱ�� 
string getTime(){
	time_t timep;
	time (&timep);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y-%m-%d-%H-%M-%S",localtime(&timep));
	return tmp;
}
//��ȡ����ļ�·�� 
void getPath(string p){
	string dir = ".\\"; dir.append(p);
	if(access(dir.c_str(),0) == -1){
		int flag = mkdir(dir.c_str());
		if(flag==-1) cout<<"Error��Can not make directory!"<<endl;
	}
	dir.append("\\"); dir.append(getTime());
	dir.append(".txt");
	
	for(int i=0; i<dir.size(); ++i) path[i] = dir[i];
}
//�Ƿ��л��������� 
int isChange(string a){
	if(a == "�л�ΪСѧ") return 1;
	else if(a == "�л�Ϊ����") return 2;
	else if(a == "�л�Ϊ����") return 3;
	return 0; 
}
//���ɴ����ŵ���Ŀ 
string makeKh(){
	string ret = to_string(rand()%100+1)+" * ((" + to_string(rand()%100+1) + " + "  + to_string(rand()%100+1) + ") / "
				+  to_string(rand()%100+1) + ") = ";
	return ret;
}
//��ȡ��ǰ�ļ����������ļ� 
void getFiles( string path, vector<string>& files )  
{  
    //�ļ���� 
    long  hFile = 0;  
    //�ļ���Ϣ
    struct _finddata_t fileinfo;  
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1)  
    {  
        do
        {  
            //�����Ŀ¼,����֮  
            //�������,�����б�  
            if((fileinfo.attrib &  _A_SUBDIR))  
            {  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );  
            }  
            else  
            {  
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  
        _findclose(hFile);  
    }
}

char command[100] = {0};
//�Ƚ��Ƿ����ظ�����Ŀ
bool cmp(string p){
	vector<string> files;
	string dir = ".\\"; dir.append(p);
	getFiles(dir,files);
	for(int i=0; i<files.size(); ++i){
		if(files[i].c_str() != path){
			sprintf(command, "FC /B \"%s\" \"%s\" |find \"FC:�Ҳ�������\" >temp.txt",files[i].c_str(),path);
			system(command);
			memset(command,0,100);
			FILE *file = fopen("temp.txt","r");
			fread(command,1,100,file);
			fclose(file);
			if(command[0]=='\0')continue;
			else return false;
			system("del temp.txt");
		} 
	}
	return true;
} 
//��ʼ���û� 
void init(){
    user[1].type = 1; user[1].name = "����1"; user[1].password = "123";
    user[2].type = 1; user[2].name = "����2"; user[2].password = "123";
    user[3].type = 1; user[3].name = "����3"; user[3].password = "123";
    user[4].type = 2; user[4].name = "����1"; user[4].password = "123";
    user[5].type = 2; user[5].name = "����2"; user[5].password = "123";
    user[6].type = 2; user[6].name = "����3"; user[6].password = "123";
    user[7].type = 3; user[7].name = "����1"; user[7].password = "123";
    user[8].type = 3; user[8].name = "����2"; user[8].password = "123";
    user[9].type = 3; user[9].name = "����3"; user[9].password = "123";
}
//������Ŀ 
void createProblems(int type,int num){
	ofstream outfile;
	int cas = 0;
    if(type==1){
		while(1){ 						//Сѧ 
	    	getPath(name);
	        outfile.open(path);
	        srand((int)time(0));
	        while(num--){
	        	outfile<<++cas<<": ";
	        	int kh = rand()%4;
	          	if(kh==3) outfile<<makeKh()<<endl;
	          	else{
	          		int t = rand()%(5-2+1)+1;
	            	while(t--){
	                	outfile<<rand()%100+1<<" "<<op[rand()%4]<<" ";
	            	}
	            	outfile<<rand()%100+1<<" ="<<endl;
				}
	        }
		     if(!cmp(name)){ //���� 
		        remove(path); //�ظ��Ļ�ɾ�����ļ� 
			}else break;    //�����˳� 
		}
    }else if(type==2){ 					//����
		while(1){
			getPath(name);
	        outfile.open(path);
	        srand((int)time(0));
	        while(num--){
	        	outfile<<++cas<<": ";
	            int t = rand()%(5-2+1)+1;
	            while(t--){
	                outfile<<rand()%100+1<<" ";
	                int optmp = rand()%6;
	                if(optmp>=4) outfile<<op[optmp]<<" "<<op[rand()%4]<<" ";
	                else outfile<<op[optmp]<<" ";
	            }
	            outfile<<rand()%100+1<<op[rand()%(5-4+1)+4]<<" ="<<endl;
	        }
	        if(!cmp(name)){ //���� 
			    remove(path); //�ظ��Ļ�ɾ�����ļ� 
			}else break;    //�����˳� 
		}
    }else{							//���� 
    	while(1){
    		getPath(name);
	        outfile.open(path);
	        srand((int)time(0));
	        while(num--){
	        	outfile<<++cas<<": ";
	            int t = rand()%(4-2+1)+1;
	            while(t--){
	                outfile<<rand()%100+1<<" ";
	                int optmp = rand()%9;
	                if(optmp>=4&&optmp<6) outfile<<op[optmp]<<" "<<op[rand()%4]<<" ";
	                else if(optmp >=6) outfile<<op[rand()%4]<<" "<< op[optmp] <<rand()%361<<" "<<op[rand()%4]<<" ";
	                else outfile<<op[optmp]<<" ";
	            }
	            outfile<<op[rand()%(8-6+1)+6]<<rand()%361<<" ="<<endl;
	        }
	        if(!cmp(name)){ //���� 
			    remove(path); //�ظ��Ļ�ɾ�����ļ� 
			}else break;    //�����˳�
	    }
	} 
	outfile.close();   
}


int main(int argc, char const *argv[])
{
    init();
    int type = 0;
    cout<<"�������û��������루��һ���ո������: "<<endl;
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
        cout<<"�˻������������������ȷ���û��������룺"<<endl;
    }

    cout<<"׼������";
    if(type==1) cout<<"Сѧ";
    else if(type==2) cout<<"����";
    else cout<<"����";
    cout<<"��ѧ��Ŀ��������������Ŀ������"<<endl;
    
    string ml; int flag = 0;
    while(cin>>ml&&!isdigit(ml[0])){ 		//�ж��Ƿ��л� 
    	if(isChange(ml)) {
    		type = isChange(ml);
    		flag = 1;
    		cout<<"׼������";
		    if(type==1) cout<<"Сѧ";
		    else if(type==2) cout<<"����";
		    else cout<<"����";
		    cout<<"��ѧ��Ŀ��������������Ŀ������"<<endl;
    		break;
		}
		cout<<"�������л�Ϊ(Сѧ�����л����)����ѡ���е�һ��"<<endl; 
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
        cout<<"�������Ŀ������Ч�����������루��Ч��Χ:[10,30]): "<<endl;
    }while(cin>>num);

	//��ʼ������Ŀ 
	createProblems(type,num);

	printf("\n<------������Ŀ��ɣ��Զ��˳�ϵͳ------->\n");
    return 0;
}

