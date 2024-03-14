
#include<iostream>
#include<cstring>
using namespace std;

class st_node{
	public:
		int no;
		st_node *ptr;	
	};

void print(st_node *q){
	while(q!=0){
		cout<<q->no<<"->";
		q=q->ptr;
	}
	cout<<"||"<<endl;	
}

int main(){
	st_node *p,*q,*a,*b;							
	p=new st_node;								
	cout<<"請輸入座號(輸入0結束)"<<endl;
	cin>>p->no;
	if(p->no!=0){
		p->ptr=q;
		q=p;	
		}
	print(q);					
	while(p->no){							
		p=new st_node;
		cout<<"請輸入座號(輸入0結束)"<<endl;
		cin>>p->no;
		a=q;
		b=q;				
	
	while(a->no<p->no){			
		if(!a->ptr){ 
		break;
		}
		b=a;
		a=a->ptr; 
	}	
	if(!a->ptr&&a==b){ 				//1st
		if(p->no<a->no){
			p->ptr=q;			
			q=p;
		}else{
			p->ptr=NULL;
			b->ptr=p;
		}
	}else if(!a->ptr&&a->no<p->no){ 			//right
		p->ptr=NULL;
		a->ptr=p;
	}else if(a==b){
		p->ptr=q;			//left
		q=p;		
	}else{					//middle
		p->ptr=a;
		b->ptr=p;
		p=q;
	}
		print(q);
	}	
}
