#include <iostream>
#include <cmath>
using namespace std;
int first[7]={0,500,300,200,50,30,10};
int second[5] = {512,256,128,64,32};
int main()
{
	int t;
	cin>>t;
	int a,b;
	int ans;
	for(int i=0;i<t;i++){
		ans = 0;
		cin>>a>>b;
		int tmp = 0;
		if(a>0){
		for(int j=1;j<=6;j++){ //부등부터 6등
			
			tmp += j; //1->3->6->....
			if(a<=tmp){
				ans += first[j]; //j등 상금 추가
				break;
			}
		}
		}
		tmp =0;
		if(b>0){
		for(int j=0;j<5;j++){
			tmp += pow(2,j); //1 -> 3(+2) ->7(+4)....
			if(b<=tmp){
				ans += second[j]; //j등 상금 추가
				break;
			}
		}
		}
		cout<< ans*10000<<endl;
	}
	
	return 0;
}
