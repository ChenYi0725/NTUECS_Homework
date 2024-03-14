#include<iostream>
#include<cstring>
#include<string>

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
	cout<<"\t請選擇\n1.新增學生資料\n2.刪除學生資料\n3.以座號查詢學生資料\n4.以姓名查詢學生資料\n5.列印串列資料\n6.列印成績單\n0.離開"<<endl;
	cin>>choice;
	while(choice>6||choice<0){
		cout<<"輸入錯誤，請重新輸入"<<endl;
		cout<<"\t請選擇\n1.新增學生資料\n2.刪除學生資料\n3.以座號查詢學生資料\n4.以姓名查詢學生資料\n5.列印串列資料\n6.列印成績單\n0.離開"<<endl;
		cin>>choice;
	}
	return choice;
}

void searchinfo(st_node*q){			//查詢(以座號)
	st_node *searchpoint;
	searchpoint=NULL;
	int exist=0,number;
	cout<<"請輸入欲查詢座號"<<endl;
	cin>>number; 
	searchpoint=q;
	while(searchpoint){											
		if(searchpoint->r_no()==number){
			exist=1;
			break;
		}
		searchpoint=searchpoint->r_ptr();
	}
	if(exist==1){
	cout<<"座號\t姓名\t程設成績\t閱讀與寫作成績"<<endl;
	cout<<searchpoint->r_no()<<"\t"<<searchpoint->r_name()<<"\t"<<searchpoint->r_pg()<<"\t"<<searchpoint->r_rw()<<endl;
	}else{
		cout<<"該學生不存在"<<endl; 
	}
}

int deleteinfo(st_node*q){							//刪除(以座號)
	st_node *deletea,*deleteb;
	deletea=NULL;
	deleteb=NULL;
	int exist=0,number;
	
	if(q!=NULL){
	cout<<"請輸入欲刪除的座號"<<endl; 
	cin>>number;
	deletea=q;										
	deleteb=q;	
	if(q->r_no()==number){									//第一筆資料 
		return 1;
	}
	
	while(deletea){										//指標移動 
		if(deletea->r_no()==number){					//找到號碼 
			deleteb->w_ptr(deletea->r_ptr());
			cout<<"該筆資料已成功刪除"<<endl; 
			deleteb=NULL;
			deletea=NULL;
			break;
		}							
		deleteb=deletea;
		deletea=deletea->r_ptr(); 
		
		if(!deletea){ 						 
			deleteb,deletea=NULL;
			cout<<"該筆資料不存在，無法刪除"<<endl;
		}
	}
	}
}

void show(st_node*q){			//列印串列(只有座號)
	st_node *h;
	h=q;
	cout<<"head->";
	while(q){												//最後的輸出迴圈
		cout<<q->r_no();
		cout<<"->";
		q=q->r_ptr();
		}
	cout<<"||"<<endl;
	q=h;
}


void printinfo(st_node*q){			//列印串列(全部) 
	st_node *h;
	
	h=q;
	if(q==NULL){
		cout<<"資料是空的"<<endl;
	}else{
	cout<<"座號\t姓名\t程設成績\t閱讀與寫作成績"<<endl;
	while(q){												//最後的輸出迴圈
		cout<<q->r_no()<<"\t"<<q->r_name()<<"\t"<<q->r_pg()<<"\t"<<q->r_rw()<<endl;
		q=q->r_ptr();
		}
	}
	q=h;
}

void printgrade(st_node*q){
	int quantity=0,rank=1,orank=1;
	st_node *current,*highest;
	current=q;
	highest=q;			//set

	if(!q){
		cout<<"資料是空的"<<endl; 
	}else{
		while(current){
			quantity=quantity+1;
			current->w_rk(0);				//數數量、rank歸0 ok
			current=current->r_ptr();
		}
		current=q;	
		
		for(int i=quantity;i>0;i--){		//排多少人 
			
			while(current){		
			
				if(current->r_rk()==0&&highest->r_rk()!=0){
					highest=current;
				}
				if(current->r_total()>highest->r_total()&&current->r_rk()==0){				//
					highest=current;
				}
				current=current->r_ptr();		
			}
			current=q;
			highest->w_rk(rank);
			rank=rank+1;	
		}
			
		cout<<"座號\t姓名\t程設成績\t閱讀與寫作成績"<<endl; //按照rank輸出 
		
		current=q;
		for(int i=quantity;i>0;i--){
		
		
			while(current){
				if(current->r_rk()==orank){
					cout<<current->r_no()<<"\t"<<current->r_name()<<"\t"<<current->r_pg()<<"\t"<<current->r_rw()<<endl;
				}
				current=current->r_ptr();
			} 
			orank=orank+1;
			current=q;
		}

	}

}

void searchname(st_node*q){
	char name[10];
	int exist=0;
	st_node *searchpoint;
	searchpoint=NULL;
	
	
	
	cout<<"請輸入欲查詢姓名"<<endl;
	cin.get();
	cin.getline(name,10);
	string target=string(name);
	
	
	searchpoint=q;
	while(searchpoint){											
		string currentname=string(searchpoint->r_name());
		
		if(currentname==target&&!exist){
			cout<<"座號\t姓名\t程設成績\t閱讀與寫作成績"<<endl;
			cout<<searchpoint->r_no()<<"\t"<<searchpoint->r_name()<<"\t"<<searchpoint->r_pg()<<"\t"<<searchpoint->r_rw()<<endl;
			exist=1;
		}else if(currentname==target&&exist){
			cout<<searchpoint->r_no()<<"\t"<<searchpoint->r_name()<<"\t"<<searchpoint->r_pg()<<"\t"<<searchpoint->r_rw()<<endl;
		}
		searchpoint=searchpoint->r_ptr();
	}
	
	
	if(!exist){
		cout<<"該學生不存在"<<endl; 
	}
	
	
}

int main(){
	st_node *n,*q,*a,*b,*searchpoint,*g;									//n->new  q->head
	char na[10];
	q=NULL;
	a=NULL;
	n=NULL;
	b=NULL;
	searchpoint=NULL;
	g=NULL;
	int choice=1,number,pro,rd,cknode=0,deleteno,ckdelete;
	
	while(choice){
		choice=menu();
		if(choice==1){
			if(cknode==0){
				n=new st_node;											  //1st				
			
				cout<<"請輸入座號"<<endl;
				cin>>number;            				
				n->w_no(number);
				n->w_ptr(NULL);
				q=n;	
				cout<<"請輸入姓名"<<endl;							//輸入其他資料
				cin.get();
				cin.getline(na,10);
				n->w_name(na);
				cout<<"請輸入程設成績(0~100分)"<<endl;
				cin>>pro;
				while(pro<0||pro>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>pro;
				}
				n->w_pg(pro);
				cout<<"請輸入閱讀與寫作成績(0~100分)"<<endl;														 
				cin>>rd;
				while(rd<0||rd>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>rd;
				}
				n->w_rw(rd);
				cknode=1;
				
			}else{ 
				n=new st_node;
				searchpoint=q;
				cout<<"請輸入座號"<<endl;
				cin>>number;
				while(searchpoint){					//檢查有無重複座號						
					if(searchpoint->r_no()==number){
						cout<<"座號重複，請重新輸入"<<endl;
						cin>>number;
						searchpoint=searchpoint->r_ptr();
						searchpoint=q;
					}else{
					searchpoint=searchpoint->r_ptr();	
					}
					if(!searchpoint){
						break;
					}
				}
				
				n->w_no(number);		
				
				a=q;
				b=q;

				cout<<"請輸入姓名"<<endl;							//輸入其他資料
				cin.get();
				cin.getline(na,10);
				n->w_name(na);
				cout<<"請輸入程設成績(0~100分)"<<endl;
				cin>>pro;
				while(pro<0||pro>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>pro;
				}
				n->w_pg(pro);
				cout<<"請輸入閱讀與寫作成績(0~100分)"<<endl;														 
				cin>>rd;
				while(rd<0||rd>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>rd;
				}
				n->w_rw(rd);				
			
			while(a->r_no()<n->r_no()){								//指標移動 
				if(!a->r_ptr()){ 									//防止a指標指向null 
				break;
				}
				b=a;
				a=a->r_ptr(); 
			}	
			if(!a->r_ptr()&&a==b){ 									//第一次插入資料 
				if(n->r_no()<a->r_no()){
					n->w_ptr(q);			
					q=n;
				}else{
					n->w_ptr(NULL);
					b->w_ptr(n);
				}
			}else if(!a->r_ptr()&&a->r_no()<n->r_no()){ 			//新資料插入最右邊 
				n->w_ptr(NULL);
				a->w_ptr(n);
			}else if(a==b){
				n->w_ptr(q);										//新資料插入最左邊 
				q=n;		
			}else{													//新資料插入串列中間 
				n->w_ptr(a);
				b->w_ptr(n);
				n=q;
			}
			} 
			
		}else if(choice==2){
			if(!q){
				cout<<"資料是空的"<<endl; 
			}else if(q->r_ptr()==NULL){									//只有一筆資料 
					cout<<"請輸入欲刪除的座號"<<endl; 
					cin>>deleteno;
					if(q->r_no()==deleteno){
						q=NULL;
						cout<<"該筆資料已成功刪除"<<endl; 
						cknode=0;
			}else{
				cout<<"該筆資料不存在，無法刪除"<<endl;
			}
			}else{
				ckdelete=deleteinfo(q);
				if(ckdelete==1){
					q=q->r_ptr();
					cout<<"該筆資料已成功刪除"<<endl; 
				}
			}
		}else if(choice==3){
			searchinfo(q);
		}else if(choice==4){
			searchname(q);
		}else if(choice==5){
			show(q);
		}else if(choice==6){
			printgrade(q); 
		}
	} 
	cout<<"再見"<<endl; 
}



