#include<iostream>
#include<stdlib.h>
#include<time.h> 
using namespace std;
int menu(){
	int y;
	cout<<"請選擇下列的模擬"<<endl;
	cout<<"1.模擬骰子點數\n2.模擬5個介於100到200之間5的倍數\n3.從大至小\n0.離開\n請選擇(1,2,3,0)"<<endl;
	cin>>y;
	while(y>3||y<0){ 
		cout<<"輸入錯誤，請重新輸入"<<endl;  
		cout<<endl;  
		cout<<"請選擇下列的模擬"<<endl;
		cout<<"1.模擬骰子點數\n2.模擬5個介於100到200之間5的倍數\n3.從大至小\n0.離開\n請選擇(1,2,3,0)"<<endl;
	 	cin>>y;
		}	 
	return y;
	}


void sort1(int*x){
	int t;
	int j=0;
	for(int i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(x[j]<x[j+1]){	
				t=x[j];
				x[j]=x[j+1];
				x[j+1]=t;
			}
		}
	}
}

void dice(){
	int d;
	d=(rand()%6)+1;
	cout<<"骰子點數為 "<<d<<endl; 
	cout<<endl;
}

void option2(int*a){
	int s;
	for(int i=0;i<5;i++){
	s=5*(rand()%20)+100;
	a[i]=s;
	for(int j=0;j<i;j++)
	    if(a[i]==a[j]){
            i--;
             }
	}
	cout<<"模擬出的不重複數字為 "; 
	for(int i=0;i<5;i++){
	cout<<a[i]<<" ";
	}
	cout<<endl;
	cout<<endl;
}


int main(){
	srand(time(NULL));	
	int a[5];	
	int o;
	o=menu();
	while(o!=0){
	switch(o)
	{	case 1 :
		dice();
		break;
		case 2 :
		option2(a);
		break;
		case 3:
		sort1(a);
		cout<<"排序完為 ";
		for(int i=0;i<5;i++){
		cout<<a[i]<<" ";
	}

		break;
		default:
		break;
	}
	o=menu();
}
	cout<<"再見"<<endl;  
}

