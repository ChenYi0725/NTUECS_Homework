#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
#include<cstdlib>
#include<typeinfo>
#include<iomanip>
#include <stdio.h>
#include <string.h>
using namespace std;
using std::string;

class basic{
	protected:
		char id[7];
		int b_time=0;
		bool state=0;
		int order;	
	public:
		void w_order(int n){
			order=n;
		}
		int r_order(){
			return order;
		}
		void w_id(char*a){
			strcpy(id,a);
		}
		void add_b_time(){
			b_time=b_time+1;
		}
		void w_b_time(int a){
			b_time=a;
		}
		void change_state(){
			state=!state;
		}
		char* r_id(){
			return id;
		}
		int r_b_time(){
			return b_time;
		}
		bool r_statebool(){
			return state;
		}
		string r_state(){
			string n;
			if(state){
				n="已被借出";
			}else{
				n="未被借出"; 
			}
			return n;
		}
		void w_state(bool b){
			state=b;
		}
		
};

class Book:public basic{
	string bname;
	string author;
	Book *ptr;
	public:
		void w_bname(string a){
			bname=a;
		}
		void w_author(string a){
			author=a;
		}
		string r_bname(){
			return bname;
		}
		string r_author(){
			return author;
		}
		Book*r_ptr(){
			return ptr;
		} 
		void w_ptr(Book *p){
			ptr=p;
		}
};

class DVD:public basic{
	string dname;
	int size;
	DVD*ptr;
	public:
		void w_dname(string a){
			dname=a;
		}
		void w_size(int n){
			size=n;
		}
		string r_dname(){
			return dname;
		}
		int r_size(){
			return size; 
		} 
		DVD*r_ptr(){
			return ptr;
		} 
		void w_ptr(DVD *p){
			ptr=p;
		}
		
};
//-----------------class--------------

class menu{
	int choice;
	public:
		int callmenu(){
			cout<<"\t請選擇\n1.新增館藏\n2.列印館藏\n3.查詢館藏(由編號)\n4.刪除館藏\n5.借還館藏\n6.搜尋館藏(由關鍵字)\n7.儲存資料\n8.清空資料\n0.儲存並離開"<<endl;
		  	cin>>choice;
	  		return choice;
	 	}			
	 	
		Book *add(Book *q){
			string idstr,setstr; 			//setstr->作者、 
			char idarray[7],idnoarray[6];	//idarray陣列 idnoarray只有數字 idno整數型別 
			int idno;
			bool check=1;						//確認編號格式 1=ok
			Book *n,*f,*b,*h;				//new forward backward
			h=q;
			f=q;
			b=q;
			n=new Book;
			cout<<"輸入編號(例:B00001)"<<endl;
			while(check){						//確認格式		
				cin>>idstr;
				idstr.copy(idarray,6,0);		//string->array
				if(idstr.length()!=6||idarray[0]!='B'){	//確認格式為6碼、B開頭 
					check=0;
				} 
				for(int i=1;i<7;i++){			//array->noarray
					idnoarray[i-1]=idarray[i];
				}
				for(int i=0;i<5;i++){					//確認取出皆為數字 				
					if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		//取出ASCII值
					check=0;
					}
				}
				if(!check){
					cout<<"編號格式錯誤，請重新輸入"<<endl;
				}
				check=!check;	
			}
			idno=atoi(idnoarray);
			n->w_id(idarray);
			n->w_order(idno);
			if(!q){	
				q=n;
				q->w_ptr(NULL);
				cout<<"請輸入書名"<<endl;
				cin.get();
				getline(cin,setstr);
				q->w_bname(setstr);
				cout<<"請輸入作者"<<endl;
				getline(cin,setstr);
				q->w_author(setstr);
			}else{
				f=q;
				b=q;
				while(f){					//檢查有無重複座號
					if(f->r_order()==idno){
						cout<<"編號重複，請重新輸入"<<endl;	
						check=1;			
						while(check){								
							cin>>idstr;
							idstr.copy(idarray,6,0);		
							if(idstr.length()!=6||idarray[0]!='B'){	 
								check=0;
							} 	
							for(int i=1;i<7;i++){		
								idnoarray[i-1]=idarray[i];
							}
							for(int i=0;i<5;i++){					 				
								if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		
								check=0;
								}
							}
							if(!check){
								cout<<"編號格式錯誤，請重新輸入"<<endl;
							}
							check=!check;	
						}
						idno=atoi(idnoarray);
						n->w_id(idarray);
						n->w_order(idno);
						f=q;
					}else{
						f=f->r_ptr();
					}
					if(!f){
						break;
					}
				}
				f=q;
				cout<<"請輸入書名"<<endl;
				cin.get();
				getline(cin,setstr);
				n->w_bname(setstr);
				cout<<"請輸入作者"<<endl;
				getline(cin,setstr);
				n->w_author(setstr);
				while(f->r_order()<n->r_order()){								//指標移動 
					if(!f->r_ptr()){ 									//防止f指標指向null 
						break;
					}
					b=f;
					f=f->r_ptr(); 
				}
				if(!f->r_ptr()&&f==b){ 									//第一次插入資料 
					if(n->r_order()<f->r_order()){
						n->w_ptr(q);			
						q=n;
					}else{
						n->w_ptr(NULL);
						b->w_ptr(n);
					}
				}else if(!f->r_ptr()&&f->r_order()<n->r_order()){ 			//新資料插入最右邊 
					n->w_ptr(NULL);
					f->w_ptr(n);
				}else if(f==q){
					n->w_ptr(q);										//新資料插入最左邊 
					q=n;		
				}else{													//新資料插入串列中間 
					n->w_ptr(f);
					b->w_ptr(n);
					} 
				}
				return q;
			}
		
		
		DVD *add(DVD *q){
			string idstr,setstr; 			//setstr->作者、編號 
			char idarray[7],idnoarray[6],sizearray[10];	//idarray陣列 idnoarray只有數字 idno整數型別 
			int idno,size,i;
			bool check=1;						//確認編號格式 1=ok
			DVD *n,*f=q,*b=q;				//new forward backward
			n=new DVD;
			
			cout<<"輸入編號(例:D00001)"<<endl;
			while(check){						//確認格式		
				cin>>idstr;
				idstr.copy(idarray,6,0);		//string->array
				if(idstr.length()!=6||idarray[0]!='D'){	//確認格式為6碼、BorD開頭 
					check=0;
				} 
				for(int i=1;i<7;i++){			//array->noarray
					idnoarray[i-1]=idarray[i];
				}
				for(int i=0;i<5;i++){					//確認取出皆為數字 				
					if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		//取出ASCII值
					check=0;
					}
				}
				if(!check){
					cout<<"編號格式錯誤，請重新輸入"<<endl;
				}
				check=!check;	
			}
			idno=atoi(idnoarray);
			n->w_order(idno);
			n->w_id(idarray);
			
			if(!q){	
				q=n;
				cout<<"請輸入片名"<<endl;
				cin.get();
				getline(cin,setstr);
				q->w_dname(setstr);
				cout<<"請輸入片長"<<endl;
				cin>>sizearray;
				while(isdigit(sizearray[i])||i<10){						//檢查片長是否為整數 
					if(sizearray[i]=='-'){
						cout<<"片長不得為負數，請重新輸入"<<endl;
						cin>>sizearray;
					}else{
						if(sizearray[i]=='\0'){
							break;
						}		
						if(!isdigit(sizearray[i])){
							cout<<"片長應為整數，請重新輸入"<<endl;
							cin>>sizearray;
							i=-1;
						}
					}
					i=i+1;
				}
				size=atoi(sizearray);
				q->w_size(size);
				q->w_ptr(NULL);
			}else{
				f=q;
				b=q;
				while(f){					//檢查有無重複座號
					if(f->r_order()==idno){
						cout<<"編號重複，請重新輸入"<<endl;	
						check=1;			
						while(check){								
							cin>>idstr;
							idstr.copy(idarray,6,0);		
							if(idstr.length()!=6||idarray[0]!='D'){	 
								check=0;
							} 	
							for(int i=1;i<7;i++){		
								idnoarray[i-1]=idarray[i];
							}
							for(int i=0;i<5;i++){					 				
								if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		
								check=0;
								}
							}
							if(!check){
								cout<<"編號格式錯誤，請重新輸入"<<endl;
							}
							check=!check;	
						}
						idno=atoi(idnoarray);
						n->w_id(idarray);
						n->w_order(idno);
						f=q;
					}else{
						f=f->r_ptr();
					}
					if(!f){
						break;
					}
				}
				f=q;
				cout<<"請輸入片名"<<endl;
				cin.get();
				getline(cin,setstr);
				n->w_dname(setstr);
				cout<<"請輸入片長"<<endl;
				i=0;
				cin>>sizearray;
				while(isdigit(sizearray[i])||i<10){						//檢查片長是否為整數 
					if(sizearray[i]=='-'){
						cout<<"片長不得為負數，請重新輸入"<<endl;
						cin>>sizearray;
					}else{
						if(sizearray[i]=='\0'){
							break;
						}		
						if(!isdigit(sizearray[i])){
							cout<<"片長應為整數，請重新輸入"<<endl;
							cin>>sizearray;
							i=-1;
						}
					}
					i=i+1;
				}
				size=atoi(sizearray);
				n->w_size(size);
				while(f->r_order()<n->r_order()){								//指標移動 
					if(!f->r_ptr()){ 									//防止f指標指向null 
						break;
					}
					b=f;
					f=f->r_ptr(); 
				}
				if(!f->r_ptr()&&f==b){ 									//第一次插入資料 
					if(n->r_order()<f->r_order()){
						n->w_ptr(q);			
						q=n;
					}else{
						n->w_ptr(NULL);
						b->w_ptr(n);
					}
				}else if(!f->r_ptr()&&f->r_order()<n->r_order()){ 			//新資料插入最右邊 
					n->w_ptr(NULL);
					f->w_ptr(n);
				}else if(f==q){
					n->w_ptr(q);										//新資料插入最左邊 
					q=n;		
				}else{													//新資料插入串列中間 
					n->w_ptr(f);
					b->w_ptr(n);
					} 
				}
				return q;
		}
		
		
		void print(Book*q,DVD*p){			//列印串列(全部) 		
			int sizea,sizeb,digit=0,t;
			Book* a;
			DVD* b;
			a=q;
			b=p;
			sizea=0;
			sizeb=0;
			if(!q){
				cout<<"書籍資料是空的"<<endl;
			}else{
				sizea=a->r_bname().length();
				sizeb=a->r_author().length();
				while(a){												//最後的輸出迴圈
					if(a->r_bname().length()>sizea){					//找出資料中最長的字串 
						sizea=a->r_bname().length();
					}			
					if(a->r_author().length()>sizeb){
						sizeb=a->r_author().length();
					}		
					a=a->r_ptr();
				}
				if(sizea<4){
					sizea=4;
				}
				if(sizeb<4){
					sizeb=4;
				}
				cout<<left<<setw(10)<<"編號"<<setw(sizea+4)<<"書名"<<setw(sizeb+4)<<"作者"<<setw(12)<<"租借狀態"<<"租借次數"<<endl;
				while(q){												//最後的輸出迴圈
					cout<<left<<setw(10)<<q->r_id()<<setw(sizea+4)<<q->r_bname()<<setw(sizeb+4)<<q->r_author()<<setw(12)<<q->r_state()<<q->r_b_time()<<endl;
					q=q->r_ptr();
					}
			}
			cout<<endl;
			if(!p){
				cout<<"影片資料是空的"<<endl;
			}else{
				sizea=b->r_dname().length();
				t=b->r_size();
				while(t>0){
           			t=t/10;
		            digit=digit+1;
    			}
				sizeb=digit;

				while(b){												//長度設定 
					digit=0;
					if(b->r_dname().length()>sizea){					//找出資料中最長的字串 
						sizea=b->r_dname().length();
					}			
					t=b->r_size();
					while(t>0){
	           			t=t/10;
			            digit=digit+1;
	    			}					
					if(digit>sizeb){
						sizeb=digit;
					}		
					b=b->r_ptr();
				}
				if(sizea<4){
					sizea=4;
				}
				cout<<"Sizeb"<<sizeb<<endl;
				cout<<left<<setw(10)<<"編號"<<setw(sizea+4)<<"片名"<<setw(sizeb+7)<<"片長"<<setw(12)<<"租借狀態"<<"租借次數"<<endl;	
				while(p){												
					cout<<left<<setw(10)<<p->r_id()<<setw(sizea+4)<<p->r_dname()<<setw(sizeb)<<p->r_size()<<setw(7)<<" 分鐘"<<setw(12)<<p->r_state()<<p->r_b_time()<<endl;
					p=p->r_ptr();
				}
			}
		}
		
		void search(Book*p,DVD*q){			//查詢(以編號) qp不同 
			Book *searchbook;
			DVD *searchdvd;
			int sizea,sizeb,digit=0,t;
			string idstr;
			searchdvd=q;
			searchbook=p;
			char idarray[7],idnoarray[6];
			int idno;
			bool exist=0,check;
			cout<<"請輸入欲查詢編號(例:B00001、D99999)"<<endl;
			check=1;		
			while(check){						//確認格式		
				cin>>idstr;
				idstr.copy(idarray,6,0);		//string->array
				if(!(idstr.length()==6&&(idarray[0]=='B'||idarray[0]=='D'))){	//確認格式為6碼、BorD開頭 
					check=0;
				} 	
				for(int i=1;i<7;i++){			//array->noarray
					idnoarray[i-1]=idarray[i];
				}
				for(int i=0;i<5;i++){					//確認取出皆為數字 				
					if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		//取出ASCII值
						check=0;
					}
				}
				if(!check){
					cout<<"編號格式錯誤，請重新輸入"<<endl;
				}
				check=!check;	
			}
			idno=atoi(idnoarray);
			if(idarray[0]=='B'){									//書本 
				while(searchbook){								//查詢指標移動				
				if(searchbook->r_order()==idno){
					exist=1;
					break;
				}
				searchbook=searchbook->r_ptr();
				}
				if(exist==1){
						sizea=searchbook->r_bname().length();
						sizeb=searchbook->r_author().length();	
					cout<<left<<setw(10)<<"編號"<<setw(sizea+4)<<"書名"<<setw(sizeb+4)<<"作者"<<setw(12)<<"租借狀態"<<"租借次數"<<endl;
					cout<<left<<setw(10)<<searchbook->r_id()<<setw(sizea+4)<<searchbook->r_bname()<<setw(sizeb+4)<<searchbook->r_author()<<setw(12)<<searchbook->r_state()<<searchbook->r_b_time()<<endl;
				}else{
					cout<<"查無資料"<<endl; 
				}
			}else if(idarray[0]=='D'){									//dvd 
				while(searchdvd){								//查詢指標移動				
				if(searchdvd->r_order()==idno){
					exist=1;
					break;
				}
				searchdvd=searchdvd->r_ptr();
				}
				if(exist==1){
					sizea=searchdvd->r_dname().length();
					t=searchdvd->r_size();
					while(t>0){
	           			t=t/10;
			            digit=digit+1;
	    			}
					sizeb=digit;
					cout<<left<<setw(10)<<"編號"<<setw(sizea+4)<<"片名"<<setw(sizeb+7)<<"片長"<<setw(12)<<"租借狀態"<<"租借次數"<<endl;	
					cout<<left<<setw(10)<<searchdvd->r_id()<<setw(sizea+4)<<searchdvd->r_dname()<<setw(sizeb)<<searchdvd->r_size()<<setw(7)<<" 分鐘"<<setw(12)<<searchdvd->r_state()<<searchdvd->r_b_time()<<endl;
				}else{
					cout<<"查無資料"<<endl;
				}
			}
		}
		
		Book *del(Book*q){									//刪除 
			Book *f,*b;
			string idstr;
			f=q;
			b=q;
			char idarray[7],idnoarray[6];
			int idno;
			bool exist=0,check=1;
			cout<<"請輸入要刪除的編號"<<endl;
			while(check){						//確認格式		
				cin>>idstr;
				idstr.copy(idarray,6,0);		//string->array
				if(!(idstr.length()==6&&(idarray[0]=='B'||idarray[0]=='D'))){	//確認格式為6碼、BorD開頭 
					check=0;
				} 	
				for(int i=1;i<7;i++){			//array->noarray
					idnoarray[i-1]=idarray[i];
				}
				for(int i=0;i<5;i++){					//確認取出皆為數字 				
					if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		//取出ASCII值
						check=0;
					}
				}
				if(!check){
					cout<<"編號格式錯誤，請重新輸入"<<endl;
				}
				check=!check;	
			}
			idno=atoi(idnoarray);	
				
			while(f->r_order()!=idno){								//指標移動 
				if(f->r_order()==idno){								//找到 
					exist=1; 
					break; 
				}
				if(!f->r_ptr()){ 									//防止f指標指向null 
					break;
				}
				b=f;
				f=f->r_ptr(); 
			}
			if(f->r_order()==idno){								//防止第一筆資料就找到 
				exist=1; 
			}
			
			
			if(!exist){
				cout<<"查無資料"<<endl;		
				
			}else{											//有符合資料 
				if(!f->r_ptr()&&f==b){						//串列是否只有一筆資料 
					q=NULL;
				}else if(f==q){							//刪除最左邊資料 
					q=q->r_ptr();	
				}else{				
					b->w_ptr(f->r_ptr());
				} 
				cout<<"該筆資料已順利刪除"<<endl;
			}
			
			return q;		
		}
		
		DVD *del(DVD*q){									//刪除 
			DVD *f,*b;
			string idstr;
			f=q;
			b=q;
			char idarray[7],idnoarray[6];
			int idno;
			bool exist=0,check=1;
			cout<<"請輸入要刪除的編號"<<endl;
			while(check){						//確認格式		
				cin>>idstr;
				idstr.copy(idarray,6,0);		//string->array
				if(!(idstr.length()==6&&(idarray[0]=='B'||idarray[0]=='D'))){	//確認格式為6碼、BorD開頭 
					check=0;
				} 	
				for(int i=1;i<7;i++){			//array->noarray
					idnoarray[i-1]=idarray[i];
				}
				for(int i=0;i<5;i++){					//確認取出皆為數字 				
					if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		//取出ASCII值
						check=0;
					}
				}
				if(!check){
					cout<<"編號格式錯誤，請重新輸入"<<endl;
				}
				check=!check;	
			}
			idno=atoi(idnoarray);	
				
			while(f->r_order()!=idno){								//指標移動 
			if(f->r_order()==idno){								//找到 
				exist=1; 
				break; 
			}
			if(!f->r_ptr()){ 									//防止f指標指向null 
				break;
			}
			b=f;
			f=f->r_ptr(); 
			}
			if(f->r_order()==idno){								//防止第一筆資料就找到 
				exist=1; 
			}
			if(!exist){
				cout<<"查無資料"<<endl;		
				
			}else{											//有符合資料 
				if(!f->r_ptr()&&f==b){						//串列是否只有一筆資料 
					q=NULL;
				}else if(f==q){							//刪除最左邊資料 
					q=q->r_ptr();	
				}else{				
					b->w_ptr(f->r_ptr());
				} 
				cout<<"該筆資料已順利刪除"<<endl;
			}
			return q;		
		}
				
		void state(Book*p,DVD*q){			//借還 
			Book *searchbook;
			DVD *searchdvd;
			string idstr;
			searchdvd=q;
			searchbook=p;
			char idarray[7],idnoarray[6];
			int idno,action;
			bool exist=0,check=1,state;
			cout<<"\t請選擇執行項目"<<endl;
			cout<<"1.借出\t2.還回"<<endl; 
			cin>>action;
			while(action>2||action<1){
				cout<<"輸入錯誤，請重新輸入"<<endl;
				cin>>action;
			}
			switch(action){
				case 1:
					cout<<"請輸入要租借的編號"<<endl;
					while(check){						//確認格式		
						cin>>idstr;
						idstr.copy(idarray,6,0);		//string->array
						if(!(idstr.length()==6&&(idarray[0]=='B'||idarray[0]=='D'))){	//確認格式為6碼、BorD開頭 
							check=0;
						} 	
						for(int i=1;i<7;i++){			//array->noarray
							idnoarray[i-1]=idarray[i];
						}
						for(int i=0;i<5;i++){					//確認取出皆為數字 				
							if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		//取出ASCII值
								check=0;
							}
						}
						if(!check){
							cout<<"編號格式錯誤，請重新輸入"<<endl;
						}
						check=!check;	
					}
					idno=atoi(idnoarray);
					if(p){
						if(idarray[0]=='B'){
							while(searchbook){								//查詢指標移動				
								if(searchbook->r_order()==idno){
									exist=1;
									break;
								}
								searchbook=searchbook->r_ptr();
							}
							
							if(exist==1&&!searchbook->r_statebool()){
								cout<<"編號 "<<searchbook->r_id()<<" 已順利租借"<<endl;
								searchbook->change_state();
								searchbook->add_b_time();
							}else if(exist==1&&searchbook->r_statebool()){
								cout<<"動作失敗，該書已被借出"<<endl;
							}else{
								cout<<"查無資料"<<endl; 
							}
						}
					}else if(idarray[0]=='B'){
						cout<<"查無資料"<<endl;
					}	 
					if(q){
						if(idarray[0]=='D'){
							while(searchdvd){								//查詢指標移動				
								if(searchdvd->r_order()==idno){
									exist=1;
									break;
								}
								searchdvd=searchdvd->r_ptr();
							}
							if(exist==1&&!searchdvd->r_statebool()){
								cout<<"編號 "<<searchdvd->r_id()<<" 已順利借出"<<endl;
								searchdvd->change_state();
								searchdvd->add_b_time();
							}else if(exist==1&&searchdvd->r_statebool()){
								cout<<"動作失敗，該DVD已被借出"<<endl;
							}else{
								cout<<"查無資料"<<endl;
							}
						}
					}else if(idarray[0]=='D'){
						cout<<"查無資料"<<endl;
					}
					break;
				case 2:
					cout<<"請輸入要歸還的編號"<<endl; 
					while(check){						//確認格式		
						cin>>idstr;
						idstr.copy(idarray,6,0);		//string->array
						if(!(idstr.length()==6&&(idarray[0]=='B'||idarray[0]=='D'))){	//確認格式為6碼、BorD開頭 
							check=0;
						} 	
						for(int i=1;i<7;i++){			//array->noarray
							idnoarray[i-1]=idarray[i];
						}
						for(int i=0;i<5;i++){					//確認取出皆為數字 				
							if((int)idnoarray[i]<48||(int)idnoarray[i]>57){		//取出ASCII值
								check=0;
							}
						}
						if(!check){
							cout<<"編號格式錯誤，請重新輸入"<<endl;
						}
						check=!check;	
					}
					idno=atoi(idnoarray);
					if(p){
						if(idarray[0]=='B'){
							while(searchbook){								//查詢指標移動				
								if(searchbook->r_order()==idno){
									exist=1;
									break;
								}
							searchbook=searchbook->r_ptr();
							}
							if(exist==1&&searchbook->r_statebool()){
								cout<<"編號 "<<searchbook->r_id()<<" 已順利歸還"<<endl;
								searchbook->change_state(); 
							}else if(exist==1&&!searchbook->r_statebool()){
								cout<<"動作失敗，目前已被歸還"<<endl;
							}else{
								cout<<"查無資料"<<endl;
							}
						}
					}else if(idarray[0]=='B'){
						cout<<"查無資料"<<endl;
					}	 
					if(q){
						if(idarray[0]=='D'){
							while(searchdvd){								//查詢指標移動				
							if(searchdvd->r_order()==idno){
								exist=1;
								break;
							}
							searchdvd=searchdvd->r_ptr();
							}
							if(exist==1&&searchdvd->r_statebool()){
								cout<<"編號 "<<searchdvd->r_id()<<" 已順利歸還"<<endl;
								searchbook->change_state();
							}else if(exist==1&&!searchdvd->r_statebool()){
								cout<<"動作失敗，目前已被歸還"<<endl;
							}else{
								cout<<"查無資料"<<endl;
							}
						}
					}else if(idarray[0]=='D'){
						cout<<"查無資料"<<endl;
					}	 
					break;
			}			
		}
		
		
		
		void keyword(Book*p,DVD*q){			//查詢(以編號)			//找不到無回應 
			Book *searchbook,*bout,*mb;	
			DVD *searchdvd,*dout,*md;
			bout=NULL;
			dout=NULL;
			int sizea=0,sizeb=0,digit=0,t;
			string str;
			searchdvd=q;
			searchbook=p;
			bool existbook=0,existdvd=0;
			cout<<"請輸入欲查詢名稱"<<endl;
			cin>>str;		
			
			if(!q&&!p){
				cout<<"查無資料"<<endl;
			}else{
				
				while(searchbook){								//查詢指標移動				
					if(searchbook->r_bname().find(str)!=string::npos){				//檢查名稱 * 
						mb=searchbook;	
						searchbook=searchbook->r_ptr();						
						if(!bout){
							bout=mb;
							mb->w_ptr(NULL);
						}else{
							mb->w_ptr(bout->r_ptr());
							bout->w_ptr(mb);		
						}								
					}else{
						searchbook=searchbook->r_ptr();
					}
				}		
				if(bout){
					existbook=1;
					searchbook=bout;
					while(searchbook){				
						if(searchbook->r_bname().length()>sizea){					//找出資料中最長的字串 
							sizea=searchbook->r_bname().length();
						}			
						if(searchbook->r_author().length()>sizeb){
							sizeb=searchbook->r_author().length();
						}
						searchbook=searchbook->r_ptr();
					}
					cout<<left<<setw(10)<<"編號"<<setw(sizea+4)<<"書名"<<setw(sizeb+4)<<"作者"<<setw(12)<<"租借狀態"<<"租借次數"<<endl;
					while(bout){
						cout<<left<<setw(10)<<bout->r_id()<<setw(sizea+4)<<bout->r_bname()<<setw(sizeb+4)<<bout->r_author()<<setw(12)<<bout->r_state()<<bout->r_b_time()<<endl;
						bout=bout->r_ptr();
					}	
				}
				sizea=0;
				sizeb=0;
				cout<<endl;					
				while(searchdvd){								//查詢指標移動				
					if(searchdvd->r_dname().find(str)!=string::npos){	//檢查名稱 *			 
						md=searchdvd;							
						searchdvd=searchdvd->r_ptr();
						if(!dout){
							dout=md;
							md->w_ptr(NULL);
						}else{
							md->w_ptr(dout->r_ptr());
							dout->w_ptr(md);		
						}								
					}else{
						searchdvd=searchdvd->r_ptr();
					}
				}
					
				if(dout){
					existdvd=1;
					searchdvd=dout;
					while(searchdvd){
						digit=0;
						if(searchdvd->r_dname().length()>sizea){					//找出資料中最長的字串 
							sizea=searchdvd->r_dname().length();
						}			
						t=searchdvd->r_size();
						while(t>0){
			        		t=t/10;
					        digit=digit+1;
			    			}					
						if(digit>sizeb){
							sizeb=digit;
						}
						searchdvd=searchdvd->r_ptr();
					}
						cout<<left<<setw(10)<<"編號"<<setw(sizea+4)<<"片名"<<setw(sizeb+7)<<"片長"<<setw(12)<<"租借狀態"<<"租借次數"<<endl;	
					while(dout){
						cout<<left<<setw(10)<<dout->r_id()<<setw(sizea+4)<<dout->r_dname()<<setw(sizeb)<<dout->r_size()<<setw(7)<<" 分鐘"<<setw(12)<<dout->r_state()<<dout->r_b_time()<<endl;
						dout=dout->r_ptr();
					}	
				}						
				if(!existdvd&&!existbook){
					cout<<"無符合資料"<<endl; 
				}				
			}
			cout<<endl;
		}
							
		
		void upload(Book *q,DVD *p){
			fstream f("exam.txt",ios_base::out/*||ios_base::trunc*/); 
			char divider[7]="000000";	
			if(!f){
				cout<<"檔案讀取失敗"<<endl;
			}else{
				if(q){
					while(q){												//寫入書本資料 
						f<<q->r_id()<<"\n"<<q->r_bname()<<"\n"<<q->r_author()<<"\n"<<q->r_statebool()<<"\n"<<q->r_b_time()<<"\n"<<q->r_order()<<"\n";
						q=q->r_ptr();
					}
				}
				f<<divider<<endl;													//寫入分隔線 
				if(p){
					while(p){												//寫入DVD資料 
						f<<p->r_id()<<"\n"<<p->r_dname()<<"\n"<<p->r_size()<<"\n"<<p->r_statebool()<<"\n"<<p->r_b_time()<<"\n"<<p->r_order()<<"\n";
						p=p->r_ptr();
					}
				}
				f<<divider<<endl;
				cout<<"資料已儲存"<<endl;
				f.close();
			} 

		}
		
		Book *download(Book *q){
			fstream f;
			f.open("exam.txt",ios_base::in);
			Book*n,*e;
			int s=2000000;
			e=q;
			int interger;
			bool boolean;
			char array[s],divider[7]="000000",end;
			string str;
			if(!f){
				cout<<"檔案讀取失敗"<<endl;
			}else{
				if(!f.get(end).eof()){				//如果f不為空文字檔 
					f.seekg(0);
					while(1){						//第二輪出bug 嘗試最後一個使用string轉int \n 
						n=new Book;		
						f.getline(array,7,'\n');			//取出編號
						if(strncmp(array,divider,6)==0){		//如果取出000000 	
							break;
						}
						n->w_id(array);
						getline(f,str,'\n');			//取出名稱
						n->w_bname(str);
						getline(f,str,'\n');			//取出作者
						n->w_author(str);				
						f>>boolean;		
						n->w_state(boolean);			//取出狀態 
						f>>interger;					//取出租借次數 
						n->w_b_time(interger);
						f>>interger;					//取出順序編號 
						n->w_order(interger);
						f.get();
						
						if(!q){
							q=n;
							q->w_ptr(NULL);
						}else{
							e=q;
							while(e){
								if(!e->r_ptr()){
									break;
								}
								e=e->r_ptr();
							}
							e->w_ptr(n);
							n->w_ptr(NULL);
						} 					
					}			
				}
				f.close();
			} 			
			return q;
		}		
		
		DVD *download(DVD *q){
			fstream f("exam.txt",ios_base::in);
			DVD*n,*e;
			int interger;
			bool boolean;
			int s=2000000;
			char array[s],divider[7]="000000",end;
			char order[7];
			string str;
			if(!f){
				cout<<"檔案讀取失敗"<<endl;
			}else{
				if(!f.get(end).eof()){								//如果f不為空文字檔 
					f.seekg(0);
					f.getline(array,7,'\n');
					while(!(strncmp(array,divider,6)==0)){			//找000000	//沒經過 
						if(strncmp(array,divider,6)==0){		//如果取出000000 	
							break;
						}
						f.getline(array,s,'\n');
					} 
					while(1){
						n=new DVD;	
						f.getline(array,7,'\n');			//取出編號
						if(strncmp(array,divider,6)==0){		//如果取出000000
							
							break;
						}		
						

						n->w_id(array);
						getline(f,str,'\n');			//取出名稱
						n->w_dname(str);
						f>>interger;							//取出作者
						n->w_size(interger);				
						f>>boolean;		
						n->w_state(boolean);			//取出狀態 
						f>>interger;					//取出租借次數 
						n->w_b_time(interger);
						f>>interger;					//取出順序 
						n->w_order(interger);
						f.get(); 

						if(!q){
							q=n;
							q->w_ptr(NULL);
						}else{
							e=q;
							while(e){
								if(!e->r_ptr()){
									break;
								}
								e=e->r_ptr();
							}
							e->w_ptr(n);
							n->w_ptr(NULL);
						} 				
					}
				}				
				f.close();
			} 			
			return q;
		}
		
		Book *clear(Book*q){
			char c[7];
			char con[6]="clear";
			cout<<"請輸入clear以確定清空資料"<<endl;
			cin>>c;
			if(strcmp(con,c) == 0) {
				q=NULL;
		        cout<<"書本資料已清空"<<endl;
		    }
		    return q;
		}
		
		DVD *clear(DVD*q){
			char c[7];
			char con[6]="clear";
			cout<<"請輸入clear以確定清空資料"<<endl;
			cin>>c;
			if(strcmp(con,c) == 0) {
				q=NULL;
		        cout<<"DVD資料已清空"<<endl;
		    }
		    return q;
		}
				
};

//---------------menu--------------- 

int main(){
	menu *m;
	int menuchoice=1,addchoice;					//menuchoice接收menu回傳值 
	char choice[1];
	m=new menu;
	Book *b_q;				//new head forward backward
	DVD *d_q;
	b_q=NULL;
	d_q=NULL;
	b_q=m->download(b_q);
	d_q=m->download(d_q);

		
	while(menuchoice){
		menuchoice=m->callmenu();
		switch(menuchoice){ 
		    case 0:
		    	break;
			case 1:  							//新增 
	            cout<<"請選擇欲新增種類"<<endl; 
	            cout<<"1.書\t2.DVD\t0.回到選單"<<endl;
	            cin>>choice;
				while((int)choice[0]<48||(int)choice[0]>50){
	            	cout<<"輸入錯誤，請重新輸入"<<endl;
					cout<<"1.書\t2.DVD\t0.回到選單"<<endl; 
					cin>>choice;
				}
				switch(choice[0]){
					case 49:
						b_q=m->add(b_q);
						break;
					case 50:
						d_q=m->add(d_q);
						break;
					default:
						break;
				}	
	            break;
			case 2: 
				m->print(b_q,d_q);		//列印 
				break;
	        case 3: 
	            m->search(b_q,d_q);		//查詢(二合一) 
	            break; 
	        case 4: 
	            cout<<"請選擇欲刪除種類"<<endl; 
	            cout<<"1.書\t2.DVD\t0.回到選單"<<endl;
	            cin>>choice;
				while((int)choice[0]<48||(int)choice[0]>50){	//取出ASCII值					
					cout<<"輸入錯誤，請重新輸入"<<endl;
					cout<<"1.書\t2.DVD\t0.回到選單"<<endl; 	
					cin>>choice;
				}
				switch(int(choice[0])){
					case 49:
						if(b_q){
							b_q=m->del(b_q);
						}else{
							cout<<"無書本資料"<<endl; 
						}
						break;
					case 50:
						if(d_q){
							d_q=m->del(d_q);
						}else{
							cout<<"無DVD資料"<<endl;
						}
						break;
					default:
						break;
				}	
	            break;
	        case 5: 
	            m->state(b_q,d_q); 		//狀態改變 
	            break; 
	        case 6:
				m->keyword(b_q,d_q);
				break;
			case 7:
				m->upload(b_q,d_q);
				break;
			case 8:
	            cout<<"請選擇欲清空種類"<<endl; 
	            cout<<"1.書\t2.DVD\t0.回到選單"<<endl;
	            cin>>choice;
				while((int)choice[0]<48||(int)choice[0]>50){
	            	cout<<"輸入錯誤，請重新輸入"<<endl;
					cout<<"1.書\t2.DVD\t0.回到選單"<<endl; 
					cin>>choice;
				}
					switch(choice[0]){
						case 49:
							b_q=m->clear(b_q);
							break;
						case 50:
							d_q=m->clear(d_q);
							break;
						default:
							break;
					}
				break;		
			default: 
	            cout<<"輸入錯誤，請重新輸入"<<endl;
				menuchoice=m->callmenu();
	            break;
    	} 
	}
	m->upload(b_q,d_q);
	cout<<"再見"<<endl;
	system("pause");
	}
