#include<iostream>
#include<stdlib.h>
#include<time.h> 
using namespace std;
int menu(){
	int y;
	cout<<"請選擇下列的模擬"<<endl;
	cout<<endl;  
	cout<<"1.模擬骰子點數\n2.模擬5個介於100到200之間5的倍數\n3.從大至小\n0.離開\n請選擇(1,2,3,0)"<<endl;
	cin>>y;
	while(y!=0){
	while(y>3||y<0){ 
		cout<<"輸入錯誤，請重新輸入"<<endl;  
		cout<<endl;  
		cout<<"請選擇下列的模擬"<<endl;
		cout<<"1.模擬骰子點數\n2.模擬5個介於100到200之間5的倍數\n3.從大至小\n0.離開\n請選擇(1,2,3,0)"<<endl;
	 	cin>>y;
		}	 
	while(y<=3&&y>=1){
		cout<<"請選擇下列的模擬"<<endl;
		cout<<endl;
		cout<<"1.模擬骰子點數\n2.模擬5個介於100到200之間5的倍數\n3.從大至小\n0.離開\n請選擇(1,2,3,0)"<<endl;
		cin>>y;
		}
	}
	cout<<"再見"<<endl;  
}

int main(){	
	menu();
	

}

