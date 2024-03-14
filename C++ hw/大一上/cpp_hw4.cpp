#include<iostream>
using namespace std;
int main(){
	int a,b,c,d,e,t;
	cin>>a>>b>>c>>d>>e;
	while(1!=(a>b&&b>c&&c>d&&d>e)){
		if(e>d){
			t=d;
			d=e;
			e=t;
		}
		if(d>c){
			t=c;
			c=d;
			d=t;
		}
		if(c>b){
			t=b;
			b=c;
			c=t;
		}
		if(b>a){
			t=a;
			a=b;
			b=t;
		}
}
	
	cout<<a<<b<<c<<d<<e;
	
	
} 
