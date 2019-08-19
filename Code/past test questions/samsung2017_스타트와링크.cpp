#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAX = 25;
int n,minans = 987987987;
int team[MAX][MAX];
bool check[MAX];
void decideTeamMate(int idx, int k){
	if(idx>n){
		if(k!=0) return ;
		int start =0, link =0;
		for(int i=0;i<n;i++){
			bool flag = check[i];
			int tmp=0;
			for(int j=0;j<n;j++){
				if(flag == check[j])
					tmp += team[i][j];
			}
			if(flag) start+= tmp;
			else link += tmp;
		}
		minans = min(minans, abs(start-link));
		return ;
	}
	if(k>0){
		check[idx] = true;
		decideTeamMate(idx+1, k-1);
	}
	check[idx] = false;
	decideTeamMate(idx+1, k);
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>team[i][j];
	
	decideTeamMate(0,n/2);
	cout<<minans;
	return 0;
}
