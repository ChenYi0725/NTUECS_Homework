#include<iostream>
#include<cstring>
using namespace std;

class st_node{
		int no,pg,rw,total,rk;
		char name[10];
		st_node *ptr;
	public:
		void w_no(int n){
			no=n;
		}	
		void w_pg(int n){
			pg=n;
		}
		void w_rw(int n){
			rw=n;
		}
		void w_name(char*a){   				
			strcpy(name,a);
		}
		int r_no(){
			return no;
		}
		char* r_name(){
			return name;
		}
		int r_pg(){
			return pg;
		}
		int r_rw(){
			return rw;
		}
		void w_ptr(st_node *p){
			ptr=p;
		}
		st_node*r_ptr(){
			return ptr;
		}
		int r_total(){
			total=pg+rw;
			return total;
		}
		int r_rk(){
			return rk;
		}	
		void w_rk(int n){
			rk=n;
		}
	};

int menu(){
	int choice;
	cout<<"\t請選擇\n1.新增學生資料\n2.刪除學生資料\n3.查詢學生資料\n4.列印串列資料\n5.列印成績單\n0.離開"<<endl;
	cin>>choice;
	while(choice>5||choice<0){			
		cout<<"輸入錯誤，請重新輸入"<<endl;
		cout<<"\t請選擇\n1.新增學生資料\n2.刪除學生資料\n3.查詢學生資料\n4.列印串列資料\n5.列印成績單\n0.離開"<<endl;
		cin>>choice;
	}
	return choice;
}

int main(){
	int choice=1;
	while(choice){
		choice=menu();
		if(choice==1){
			cout<<"新增學生資料執行中"<<endl;
			system("pause");
		}else if(choice==2){
			cout<<"刪除學生資料執行中"<<endl;
			system("pause");
		}else if(choice==3){
			cout<<"查詢學生資料執行中"<<endl;
			system("pause");
		}else if(choice==4){
			cout<<"列印串列資料執行中"<<endl;
			system("pause");
		}else if(choice==5){
			cout<<"列印成績單執行中"<<endl;
			system("pause");
		}
	}
	cout<<"再見"<<endl; 
}
