#include <iostream>
#include <algorithm>
using namespace std;
typedef long long int ll;
const int MAX = 15;
int n;
int num[MAX];
int op_order[MAX];
int op[4];
ll maxans =-1000000005, minans = 1000000005;
void calcEquation(){
	ll ans = num[0];
	for(int i =1;i<n;i++){
		switch(op_order[i-1]){
			case 0:
				ans += num[i];
				break;
			case 1:
				ans -= num[i];
				break;
			case 2:
				ans *= num[i];
				break;
			case 3:
				ans /= num[i];
				break;
		}
	}
	maxans = max(maxans, ans);
	minans = min(minans, ans);
}
void setOperator(int idx){
	if(idx>=n-1){
		calcEquation();
		return ;
	}
	for(int i =0; i<4; i++){
		if(!op[i]) continue;
		op_order[idx] = i;
		op[i]--;
		setOperator(idx+1);
		op[i]++;
	}
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>num[i];
	for(int i=0;i<4;i++) cin>>op[i];
	setOperator(0);
	cout<<maxans<<endl<<minans;
}
