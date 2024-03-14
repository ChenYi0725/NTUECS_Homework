#include<iostream>
#include<stdlib.h>
#include<time.h> 
using namespace std;
int menu(int&y){
	cout<<"\t骰子遊戲"<<endl;
	cout<<"1.比大\n2.比小\n3.離開\n請選擇"<<endl;
	cin>>y;
	while(y>3||y<1){ 
		cout<<"請重新輸入"<<endl;  
		cout<<"1.比大\n2.比小\n3.離開\n請選擇"<<endl;
	 	cin>>y;
	} 
}
game(int&x){
	int p,c,w;
	p=(rand()%6)+1;
	c=(rand()%6)+1;
	if (x==1){
		cout<<"你的數字為"<<p<<endl;
		 cout<<"電腦的數字為"<<c<<endl;
		if(p>c)
		 cout<<"你贏了\n";
		if(c>p)
	 	 cout<<"你輸了\n";
		if(c==p)
		 cout<<"平手\n"; 
	}
	if (x==2){
		cout<<"你的數字為"<<p<<endl;
	 	cout<<"電腦的數字為"<<c<<endl;
		if(p<c)
	 	cout<<"你贏了\n";
		if(c<p)
		cout<<"你輸了\n";
		if(c==p)
		cout<<"平手\n";
	}
}

int main(){	
	srand(time(NULL));
	int m=1;
	while(1){
		menu(m);
		if (m==3){ 
	    	cout<<"再見"<<endl;
		    break;
		} 
		
		game(m);
		system("pause");
	}
}

