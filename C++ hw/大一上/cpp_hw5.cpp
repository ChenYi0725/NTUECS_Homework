#include<iostream>
using namespace std;
int main(){
	int h,m,s,t;
	cin>>h>>m>>s;
	while(h>=24||m>=60||s>=60)
	{cin>>h>>m>>s;
	}
	while(1){
	for(s;s<61;s++){
		for(t=0;t<500000000;t++){
			continue;
			}
			if(s==60){
			m=m+1;
			s=0;
			}
			if(m==60){
			h=h+1;
			m=0;
			}
			if(h==24){
			h=0;
			}
		cout<<h<<":"<<m<<":"<<s<<endl;
		}		
	}
	
}
