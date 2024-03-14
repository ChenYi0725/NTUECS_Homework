#include<iostream>
#include<cstring>
using namespace std;

class st_node{
	public:
		int no;
		char name[10];
		int pg;
		int rw;
		st_node *ptr;	
	};


int main(){
	int i=0;
	st_node *p,*q;
	q=NULL;
	for(i=0;i<10;i++){
		p=new st_node;
		
		cout<<"請輸入座號"<<endl;
		cin>>p->no;
		while(p->no<=0){
			cout<<"輸入錯誤，請重新輸入"<<endl;
			cin>>p->no;
		}
		cout<<"請輸入姓名"<<endl;
		cin.get();
		cin.getline(p->name,10);
		cout<<"請輸入程式設計成績"<<endl;
		cin>>p->pg;
		while(p->pg<0||p->pg>100){
			cout<<"輸入錯誤，請重新輸入"<<endl;
			cin>>p->pg;
		}
		cout<<"請輸入國文成績"<<endl;
		cin>>p->rw;
		while(p->rw<0||p->rw>100){
			cout<<"輸入錯誤，請重新輸入"<<endl;
			cin>>p->rw;
		}			
		
		p->ptr=q;
		q=p;									//反向 
	}
	
	cout<<"座號"<<"\t"<<"名字"<<"\t"<<"程式設計成績"<<"\t"<<"國文成績"<<endl;

	while(q){
		cout<<q->no<<"\t"<<q->name<<"\t"<<q->pg<<"\t"<<q->rw<<endl;
	
		q=q->ptr;
	}
	
}
