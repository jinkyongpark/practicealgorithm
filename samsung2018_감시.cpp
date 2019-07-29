#include<iostream>
#include <vector>
using namespace std;
const int MAX = 10;
int room[MAX][MAX];
bool check[MAX][MAX],tcheck[MAX][MAX];
int n,m;
vector<pair<int,int>> cl; //cctv위치
int cd[MAX]; //cctv방향
int cctv[6][4][4] = 
{{},
{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
{{1,1,0,0},{0,0,1,1},{0,0,0,0},{0,0,0,0}},
{{1,0,1,0},{0,1,1,0},{0,1,0,1},{1,0,0,1}},
{{1,1,1,0},{1,1,0,1},{1,0,1,1},{0,1,1,1}},
{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}}}; //cctv[번호][방향][여부]
int d[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int ccnt,minans = 987987987;
void findBlindSpot(){
	for(int i = 0 ;i <ccnt;i++){
		int r = cl[i].first, c = cl[i].second;
		int cctvnumber = room[r][c], cctvdirection = cd[i];
		for(int j=0;j<4;j++){
			if(cctv[cctvnumber][cctvdirection][j] ==0) continue;
			int nr = r, nc = c;
			while(1) {
				nr+= d[j][0],nc+=d[j][1];
				if(nr<0 || nr>=n || nc<0 || nc>=m) break;
				if(room[nr][nc]==6) break;
				check[nr][nc] = true;
			}
		}
	}
	int s = 0;
	for(int i =0;i<n;i++){
		for(int j=0;j<m;j++){
			if(!check[i][j]) s++; 
			check[i][j] = tcheck[i][j];
		}
	}
	if(s<minans) minans = s;
}
void dfs(int idx){
	if(idx>=ccnt){
		findBlindSpot();
		return ;
	}
	for(int i =0;i<4;i++){
		cd[idx] = i;
		dfs(idx+1);
	}
}
int main(){
	cin>>n>>m;
	for(int i =0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>room[i][j];
			if(room[i][j]>0 ){
				tcheck[i][j] = true;
				check[i][j] = true;
				if(room[i][j]<6)
					 cl.push_back(make_pair(i,j));
			} 
		}
	}
	ccnt = cl.size();
	dfs(0);
	cout<<minans;
	return 0;
}
