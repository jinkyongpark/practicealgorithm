#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAX =55;
int n,m;
vector <pair<int,int>>  chicken;// 좌표
int city[MAX][MAX], minans=987987987;
bool maintainChicken[MAX];
void selectChicken(int idx,int k){
	if(idx>=chicken.size()){
		if(k!=0) return ;
		int ans = 0;
		for(int i =1;i<=n;i++){
			for(int j= 1 ;j<=n;j++){
				if(city[i][j]!=1) continue;
				int mindistance = 987987987;
				for(int c = 0 ;c<chicken.size();c++){
					if(!maintainChicken[c]) continue;
					int distance = abs(chicken[c].first  - i) + abs(chicken[c].second - j);
					mindistance = min(mindistance, distance);
				}
				ans += mindistance;
			}
		}
		minans = min(minans, ans);
		return ;
	}
	maintainChicken[idx] = false;
	selectChicken(idx+1,k);
	if(k>0){
		maintainChicken[idx] = true;
		selectChicken(idx+1,k-1);
	}

}
int main(){
	cin>>n>>m;
	int idx =0, ans =0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>> city[i][j];
			if(city[i][j]==2) 	chicken.push_back(make_pair(i,j));
		}
	}
	selectChicken(0,m);
	cout<<minans;
	return 0;
}
