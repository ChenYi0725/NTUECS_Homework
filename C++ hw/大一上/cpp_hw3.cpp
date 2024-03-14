#include<iostream>
using namespace std;
int main(){
	int a,b,c,t,s;
	cin>>a>>b>>c;
	while(1!=(a>b&&b>c)){
	
		if(c>a){
		t=a;
		s=b;
		a=c;
		b=t;
		c=s;
		}else{
		t=b;
		b=c;
		c=t;
	}
}
	
	cout<<a<<b<<c;
	
	
} 
