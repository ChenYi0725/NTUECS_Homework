#include<iostream>
#include<cstring>
using namespace std;

class student{
	protected:
		int no,total,rk;
		char name[10];
};

class cs_st : protected student{
		int pg,cp;
		cs_st *ptr;
	public:
		void w_no(int n){
			no=n;
		}	
		void w_pg(int n){
			pg=n;
		}
		void w_cp(int n){
			cp=n;
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
		int r_cp(){
			return cp;
		}
		void w_ptr(cs_st *p){
			ptr=p;
		}
		cs_st*r_ptr(){
			return ptr;
		}
		int r_total(){
			total=pg+cp;
			return total;
		}
		int r_rk(){
			return rk;
		}	
		void w_rk(int n){
			rk=n;
		}
		
};

class pe_st : protected student{					//體育系 
		int pescore,run;
		pe_st *ptr;
	public:
		void w_no(int n){
			no=n;
		}	
		void w_pescore(int n){
			pescore=n;
		}
		void w_run(int n){
			run=n;
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
		int r_pescore(){
			return pescore;
		}
		int r_run(){
			return run;
		}
		void w_ptr(pe_st *p){
			ptr=p;
		}
		pe_st*r_ptr(){
			return ptr;
		}
		int r_total(){
			total=(100-run)+pescore;
			return total;
		}
		int r_rk(){
			return rk;
		}	
		void w_rk(int n){
			rk=n;
		}
};
//-------------------類別設定------------------------------ 

int menu(){
	int choice=0;
	int department=0;
	
	cout<<"\t請選擇\n1.新增學生資料\n2.刪除學生資料\n3.查詢學生資料\n4.列印串列資料\n5.列印成績單\n0.離開"<<endl;
	cin>>choice;
	while(choice>5||choice<0){
		cout<<"輸入錯誤，請重新輸入"<<endl;
		cout<<"\t請選擇\n1.新增學生資料\n2.刪除學生資料\n3.查詢學生資料\n4.列印串列資料\n5.列印成績單\n0.離開"<<endl;
		cin>>choice;
	}
	if(choice){
		cout<<"\t請選擇科系"<<endl;
		cout<<"1.資科系	2.體育系"<<endl;
		cin>>department;
		while(department<1||department>2){
			cout<<"請重新選擇"<<endl;
			cout<<"1.資科系	 2.體育系"<<endl;
			cin>>department;
		} 
	}
	choice=choice+department*10;
	return choice;
	
}

//----------資科用函式------------------- 


void cs_searchinfo(cs_st*q){			//查詢(以座號)資科 
	cs_st *searchpoint;
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
	cout<<"座號\t姓名\t程設成績\t計概成績"<<endl;
	cout<<searchpoint->r_no()<<"\t"<<searchpoint->r_name()<<"\t"<<searchpoint->r_pg()<<"\t"<<searchpoint->r_cp()<<endl;
	}else{
		cout<<"該學生不存在"<<endl; 
	}
}

int cs_deleteinfo(cs_st*q){							//刪除(以座號)
	cs_st *deletea,*deleteb;
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
			cout<<"該筆資料已刪除"<<endl; 
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

void cs_printinfo(cs_st*q){			//列印串列(只有座號)
	cs_st *h;
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


void cs_printgrade(cs_st*q){					//列印成績 
	int quantity=0,rank=1,orank=1;
	cs_st *current,*highest;
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
			
		cout<<"座號\t姓名\t程設成績\t計概成績\t總分"<<endl; //按照rank輸出 
		
		current=q;
		for(int i=quantity;i>0;i--){
		
		
			while(current){
				if(current->r_rk()==orank){
					cout<<current->r_no()<<"\t"<<current->r_name()<<"\t"<<current->r_pg()<<"\t"<<current->r_cp()<<"\t"<<current->r_total()<<endl;
				}
				current=current->r_ptr();
			} 
			orank=orank+1;
			current=q;
		}

	}

}
//---------------體育用函式------------------------------ 

void pe_searchinfo(pe_st*q){			//查詢(以座號)資科 
	pe_st *searchpoint;
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
	cout<<"座號\t姓名\t體育成績\t100公短跑成績"<<endl;
	cout<<searchpoint->r_no()<<"\t"<<searchpoint->r_name()<<"\t"<<searchpoint->r_pescore()<<"\t"<<searchpoint->r_run()<<endl;
	}else{
		cout<<"該學生不存在"<<endl; 
	}
}

int pe_deleteinfo(pe_st*q){							//刪除(以座號)
	pe_st *deletea,*deleteb;
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
			cout<<"該筆資料已刪除"<<endl; 
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

void pe_printinfo(pe_st*q){			//列印串列(只有座號)
	pe_st *h;
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


void pe_printgrade(pe_st*q){					//列印成績 
	int quantity=0,rank=1,orank=1;
	pe_st *current,*highest;
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
			
		cout<<"座號\t姓名\t體育成績\t100公短跑成績\t總分"<<endl; //按照rank輸出 
		
		current=q;
		for(int i=quantity;i>0;i--){
		
		
			while(current){
				if(current->r_rk()==orank){
					cout<<current->r_no()<<"\t"<<current->r_name()<<"\t"<<current->r_pescore()<<"\t"<<current->r_run()<<"\t"<<current->r_total()<<endl;
				}
				current=current->r_ptr();
			} 
			orank=orank+1;
			current=q;
		}

	}

}

//-------------主函式----------------------------------- 
int main(){
	cs_st *cs_n,*cs_q,*cs_a,*cs_b,*cs_searchpoint;									//cs_n->new  q->head
	pe_st *pe_n,*pe_q,*pe_a,*pe_b,*pe_searchpoint;	
	char cs_na[10],pe_na[10];
	cs_q=NULL;
	cs_a=NULL;
	cs_n=NULL;
	cs_b=NULL;
	cs_searchpoint=NULL;
	pe_q=NULL;
	pe_a=NULL;
	pe_n=NULL;
	pe_b=NULL;
	pe_searchpoint=NULL;
	int choice=1,cs_number,pg_score,cp_score,cs_cknode=0,pe_number,pe_score,run_score,pe_cknode=0,deleteno,ckdelete; 
	
	while(choice){
		choice=menu();
		if(choice==11){										//插入資料 
			if(cs_cknode==0){
				cs_n=new cs_st;											  //1st				
				cout<<"請輸入座號"<<endl;
				cin>>cs_number;            				
				cs_n->w_no(cs_number);
				cs_n->w_ptr(NULL);
				cs_q=cs_n;	
				cout<<"請輸入姓名"<<endl;							//輸入其他資料
				cin.get();
				cin.getline(cs_na,10);
				cs_n->w_name(cs_na);
				cout<<"請輸入程設成績(0~100分)"<<endl;
				cin>>pg_score;
				while(pg_score<0||pg_score>100){
					cout<<"輸入錯誤︷s_a請重新輸入"<<endl; 
					cin>>pg_score;
				}
				cs_n->w_pg(pg_score);
				cout<<"請輸入計概成績(0~100分)"<<endl;														 
				cin>>cp_score;
				while(cp_score<0||cp_score>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>cp_score;
				}
				cs_n->w_cp(cp_score);
				cs_cknode=1;
				
			}else{ 
				cs_n=new cs_st;
				cs_searchpoint=cs_q;
				cout<<"請輸入座號"<<endl;
				cin>>cs_number;
				while(cs_searchpoint){					//檢查有無重複座號						
					if(cs_searchpoint->r_no()==cs_number){
						cout<<"座號重複，請重新輸入"<<endl;
						cin>>cs_number;
						cs_searchpoint=cs_searchpoint->r_ptr();
						cs_searchpoint=cs_q;
					}else{
					cs_searchpoint=cs_searchpoint->r_ptr();	
					}
					if(!cs_searchpoint){
						break;
					}
				}
				
				cs_n->w_no(cs_number);		
				
				cs_a=cs_q;
				cs_b=cs_q;

				cout<<"請輸入姓名"<<endl;							//輸入其他資料
				cin.get();
				cin.getline(cs_na,10);
				cs_n->w_name(cs_na);
				cout<<"請輸入程設成績(0~100分)"<<endl;
				cin>>pg_score;
				while(pg_score<0||pg_score>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>pg_score;
				}
				cs_n->w_pg(pg_score);
				cout<<"請輸入計概成績(0~100分)"<<endl;														 
				cin>>cp_score;
				while(cp_score<0||cp_score>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>cp_score;
				}
				cs_n->w_cp(cp_score);				
			
			while(cs_a->r_no()<cs_n->r_no()){								//指標移動 
				if(!cs_a->r_ptr()){ 									//防止a指標指向null 
				break;
				}
				cs_b=cs_a;
				cs_a=cs_a->r_ptr(); 
			}	
			if(!cs_a->r_ptr()&&cs_a==cs_b){ 									//第一次插入資料 
				if(cs_n->r_no()<cs_a->r_no()){
					cs_n->w_ptr(cs_q);			
					cs_q=cs_n;
				}else{
					cs_n->w_ptr(NULL);
					cs_b->w_ptr(cs_n);
				}
			}else if(!cs_a->r_ptr()&&cs_a->r_no()<cs_n->r_no()){ 			//新資料插入最右邊 
				cs_n->w_ptr(NULL);
				cs_a->w_ptr(cs_n);
			}else if(cs_a==cs_b){
				cs_n->w_ptr(cs_q);										//新資料插入最左邊 
				cs_q=cs_n;		
			}else{													//新資料插入串列中間 
				cs_n->w_ptr(cs_a);
				cs_b->w_ptr(cs_n);
				cs_n=cs_q;
			}
			} 
			
		}else if(choice==13){											//查詢 
			cs_searchinfo(cs_q);
		}else if(choice==12){											//刪除 
			if(!cs_q){
				cout<<"資料是空的"<<endl; 
			}else if(cs_q->r_ptr()==NULL){									//只有一筆資料 
					cout<<"請輸入欲刪除的座號"<<endl; 
					cin>>deleteno;
					if(cs_q->r_no()==deleteno){
						cs_q=NULL;
						cout<<"該筆資料已刪除"<<endl; 
						cs_cknode=0;
			}else{
				cout<<"該筆資料不存在，無法刪除"<<endl;
			}
			}else{														//如果要刪除的是第一筆資料 
				ckdelete=cs_deleteinfo(cs_q);				
				if(ckdelete==1){
					cs_q=cs_q->r_ptr();
					cout<<"該筆資料已刪除"<<endl; 
				}
				ckdelete=0;
			}
		}else if(choice==14){										//列印串列 
			cs_printinfo(cs_q);
		}else if(choice==15){										//列印成績單 
			cs_printgrade(cs_q); 
		}else if(choice==21){										//插入資料 
			if(pe_cknode==0){
				pe_n=new pe_st;											  //1st				
			
				cout<<"請輸入座號"<<endl;
				cin>>pe_number;            				
				pe_n->w_no(pe_number);
				pe_n->w_ptr(NULL);
				pe_q=pe_n;	
				cout<<"請輸入姓名"<<endl;							//輸入其他資料
				cin.get();
				cin.getline(pe_na,10);
				pe_n->w_name(pe_na);
				cout<<"請輸入體育成績(0~100分)"<<endl;
				cin>>pe_score;
				while(pe_score<0||pe_score>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>pe_score;
				}
				pe_n->w_pescore(pe_score);
				cout<<"請輸入100公短跑成績(0~100分)"<<endl;														 
				cin>>run_score;
				while(run_score<0){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>run_score;
				}
				pe_n->w_run(run_score);
				pe_cknode=1;
				
			}else{ 
				pe_n=new pe_st;
				pe_searchpoint=pe_q;
				cout<<"請輸入座號"<<endl;
				cin>>pe_number;
				while(pe_searchpoint){					//檢查有無重複座號						
					if(pe_searchpoint->r_no()==pe_number){
						cout<<"座號重複，請重新輸入"<<endl;
						cin>>pe_number;
						pe_searchpoint=pe_searchpoint->r_ptr();
						pe_searchpoint=pe_q;
					}else{
					pe_searchpoint=pe_searchpoint->r_ptr();	
					}
					if(!pe_searchpoint){
						break;
					}
				}
				
				pe_n->w_no(pe_number);		
				
				pe_a=pe_q;
				pe_b=pe_q;

				cout<<"請輸入姓名"<<endl;							//輸入其他資料
				cin.get();
				cin.getline(pe_na,10);
				pe_n->w_name(pe_na);
				cout<<"請輸入體育成績(0~100分)"<<endl;
				cin>>pe_score;
				while(pe_score<0||pe_score>100){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>pe_score;
				}
				pe_n->w_pescore(pe_score);								//秒 
				cout<<"請輸入100公短跑成績"<<endl;														 
				cin>>run_score;
				while(run_score<0){
					cout<<"輸入錯誤，請重新輸入"<<endl; 
					cin>>run_score;
				}
				pe_n->w_run(run_score);				
			
			while(pe_a->r_no()<pe_n->r_no()){								//指標移動 
				if(!pe_a->r_ptr()){ 									//防止a指標指向null 
				break;
				}
				pe_b=pe_a;
				pe_a=pe_a->r_ptr(); 
			}	
			if(!pe_a->r_ptr()&&pe_a==pe_b){ 									//第一次插入資料 
				if(pe_n->r_no()<pe_a->r_no()){
					pe_n->w_ptr(pe_q);			
					pe_q=pe_n;
				}else{
					pe_n->w_ptr(NULL);
					pe_b->w_ptr(pe_n);
				}
			}else if(!pe_a->r_ptr()&&pe_a->r_no()<pe_n->r_no()){ 			//新資料插入最右邊 
				pe_n->w_ptr(NULL);
				pe_a->w_ptr(pe_n);
			}else if(pe_a==pe_b){
				pe_n->w_ptr(pe_q);										//新資料插入最左邊 
				pe_q=pe_n;		
			}else{													//新資料插入串列中間 
				pe_n->w_ptr(pe_a);
				pe_b->w_ptr(pe_n);
				pe_n=pe_q;
			}
			} 
			
		}else if(choice==23){											//查詢 
			pe_searchinfo(pe_q);
		}else if(choice==22){											//刪除 
			if(!pe_q){
				cout<<"資料是空的"<<endl; 
			}else if(pe_q->r_ptr()==NULL){									//只有一筆資料 
					cout<<"請輸入欲刪除的座號"<<endl; 
					cin>>deleteno;
					if(pe_q->r_no()==deleteno){
						pe_q=NULL;
						cout<<"該筆資料已刪除"<<endl; 
						pe_cknode=0;
			}else{
				cout<<"該筆資料不存在，無法刪除"<<endl;
			}
			}else{
				ckdelete=pe_deleteinfo(pe_q);
				if(ckdelete==1){
					pe_q=pe_q->r_ptr();
					cout<<"該筆資料已刪除"<<endl; 
				}
			}
		}else if(choice==24){										//列印串列 
			pe_printinfo(pe_q);
		}else if(choice==25){										//列印成績單 
			pe_printgrade(pe_q); 
		}
	} 
	cout<<"再見"<<endl; 
}



