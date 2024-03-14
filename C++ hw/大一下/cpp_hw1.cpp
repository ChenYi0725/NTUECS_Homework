#include<iostream>
#include<cstring>
using namespace std;
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
	int num[10];
	char name[10][10];
	char n;
	int pg[10];
	int rw[10];
	for(int j=0;j<10;j++){											 
		cout<<"請輸入座號"<<endl;
		cin>>num[j];
		cout<<"請輸入姓名"<<endl;
		while(getchar()!='\n');				 
		cin.getline(name[j],10);			
		cout<<"請輸入程式設計成績"<<endl;
		cin>>pg[j];
		cout<<"請輸入閱讀與寫作成績"<<endl;
		cin>>rw[j];
		if(num[j]<0||pg[j]>100||pg[j]<0||rw[j]>100||rw[j]<0){
			cout<<"輸入錯誤，請重新輸入"<<endl;
			j=j-1;
		}
		}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(num[j]>num[j+1]){
				iexc(num[j],num[j+1]);
				iexc(pg[j],pg[j+1]);
				iexc(rw[j],rw[j+1]);
				cexc(name[j],name[j+1]);
			}
			
			
		}
		
	}	
		
		
		
	cout<<"座號"<<"\t"<<"名字"<<"\t"<<"程式設計成績"<<"\t"<<"閱讀與寫作成績"<<endl;
	for(int i=0;i<5;i++){												
		cout<<num[i]<<"\t"<<name[i]<<"\t"<<pg[i]<<"\t"<<rw[i]<<endl;	
		
	}


	}
	

