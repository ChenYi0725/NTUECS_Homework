#include<iostream>
#include<cstring>
using namespace std;
 
class st_node{
	public:
		int no;
		char name[10];
		int pg;
		int rw;
	//	st_node *ptr;	
	};
int iexc(int&a,int&b){
	int t;
		t=a;
		a=b;
		b=t;	
	} 


char cexc(char*a,char*b){					
	char t[10];
	strcpy(t,a);
	strcpy(a,b);
	strcpy(b,t);
}


int main(){
	st_node a[10];
	for(int i=0;i<10;i++){
		cout<<"請輸入座號"<<endl;
		cin>>a[i].no;
		cout<<"請輸入姓名"<<endl;
		while(getchar()!='\n');				 
		cin.getline(a[i].name,10);
		cout<<"請輸入程式設計成績"<<endl;
		cin>>a[i].pg;
		cout<<"請輸入閱讀與寫作成績"<<endl;
		cin>>a[i].rw;
		if(a[i].no<0||a[i].pg>100||a[i].pg<0||a[i].rw>100||a[i].rw<0){
			cout<<"輸入錯誤，請重新輸入"<<endl;
			i=i-1;
	}
}
		for(int j=0;j<10;j++){
		for(int i=0;i<9;i++){
			if(a[i].no>a[i+1].no){
				iexc(a[i].no,a[i+1].no);
				iexc(a[i].pg,a[i+1].pg);
				iexc(a[i].rw,a[i+1].rw);
				cexc(a[i].name,a[i+1].name);
			}
			
			
		}
		
	}	
		
		
	
	
	
	cout<<"座號"<<"\t"<<"名字"<<"\t"<<"程式設計成績"<<"\t"<<"閱讀與寫作成績"<<endl;
	for(int i=0;i<10;i++){												
		cout<<a[i].no<<"\t"<<a[i].name<<"\t"<<a[i].pg<<"\t"<<a[i].rw<<endl;		
	}
	
	

} 
