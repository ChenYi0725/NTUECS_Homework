#include<iostream>
using namespace std;
void exch(int&x,int&y){
	int t;
	t=x;
	x=y;
	y=t;	
}

int main(){
	int a,b,c,d,e;
	cin>>a>>b>>c>>d>>e;
	while(1!=(a>=b&&b>=c&&c>=d&&d>=e)){
		if(e>d){
			exch(d,e);
		}
		if(d>c){
			exch(c,d);
		}
		if(c>b){
			exch(b,c);
		}
		if(b>a){
			exch(a,b);
		}
}
	
	cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e;
} 
