
#include<iostream>
#include<cstring>
using namespace std;

class st_node{
		int no,pg,rw;
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
	};



int main(){
	st_node *p,*q,*a,*b,*h;
	int x,y,pro,rd;				//x->座號 
	char na[10];									
	p=new st_node;											  //1st				
	cout<<"請輸入座號(輸入0結束)"<<endl;
	cin>>x;            				
	p->w_no(x);
	if(p->r_no()!=0){
		p->w_ptr(NULL);
		q=p;	
		}
	
	cout<<"請輸入姓名"<<endl;							//輸入其他資料
	cin.get();
	cin.getline(na,10);
	p->w_name(na);
	cout<<"請輸入程式設計成績"<<endl;
	cin>>pro;
	p->w_pg(pro);
	cout<<"請輸入國文成績"<<endl;														 
	cin>>rd;
	p->w_rw(rd);
	 
		h=q;
	while(1){
		cout<<q->r_no()<<"->";
		if(!q->r_ptr()){
			break;
		}
		q=q->r_ptr();	//
	}
	cout<<"||"<<endl;
	q=h;				
					
	while(p->r_no()){										//重複輸入							
		p=new st_node;
		cout<<"請輸入座號(輸入0結束)"<<endl;
		cin>>x;
		p->w_no(x);		
		if(!p->r_no()){  									//輸入0結束 
			break;
		//輸入其他資料 
	
		h=q;	
			while(1){
				y=q->r_no();
				cout<<y<<"->";
				if(!q->r_ptr()){
				break;
				}
			q=q->r_ptr();	
			}
			cout<<"||"<<endl;
			q=h;
		}
		
		a=q;
		b=q;
		
		cout<<"請輸入姓名"<<endl;							//輸入其他資料
		cin.get();
		cin.getline(na,10);
		p->w_name(na);
		cout<<"請輸入程式設計成績"<<endl;
		cin>>pro;
		p->w_pg(pro);
		cout<<"請輸入國文成績"<<endl;														 
		cin>>rd;
		p->w_rw(rd);				
	
	while(a->r_no()<p->r_no()){								//指標移動 
		if(!a->r_ptr()){ 									//防止a指標指向null 
		break;
		}
		b=a;
		a=a->r_ptr(); 
	}	
	if(!a->r_ptr()&&a==b){ 									//第一次插入資料 
		if(p->r_no()<a->r_no()){
			p->w_ptr(q);			
			q=p;
		}else{
			p->w_ptr(NULL);
			b->w_ptr(p);
		}
	}else if(!a->r_ptr()&&a->r_no()<p->r_no()){ 			//新資料插入最右邊 
		p->w_ptr(NULL);
		a->w_ptr(p);
	}else if(a==b){
		p->w_ptr(q);										//新資料插入最左邊 
		q=p;		
	}else{													//新資料插入串列中間 
		p->w_ptr(a);
		b->w_ptr(p);
		p=q;
	}
	
	h=q;
	while(1){
		y=q->r_no();
		cout<<y<<"->";
		if(!q->r_ptr()){
			break;
		}
		q=q->r_ptr();	
	}
	cout<<"||"<<endl;
	q=h;
	}
	
	cout<<"座號\t姓名\t程設成績\t國文成績"<<endl; 
	while(q){												//最後的輸出迴圈
	cout<<q->r_no()<<"\t"<<q->r_name()<<"\t"<<q->r_pg()<<"\t"<<q->r_rw()<<endl;
	q=q->r_ptr();
	}
}



