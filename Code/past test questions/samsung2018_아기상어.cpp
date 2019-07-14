#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX = 25;
int n;
struct Pi{
	int r,c,dist;
};
int d[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int area[MAX][MAX];
bool check[MAX][MAX];
int sr,sc,sw=2; //아기상어위치,사이즈
int eatn = 0; //먹은 갯수
int t = 0;
vector<pair<int,int>> eatlst;
void bfs(){
	queue<Pi> q;
	q.push(Pi{sr,sc,0});
	check[sr][sc] = true;
	int mind = 0;
	while(!q.empty()){
		int rr = q.front().r, cc = q.front().c, dd = q.front().dist;
		q.pop();
		for(int i =0; i<4 ;i++){
			int nr = rr + d[i][0], nc = cc + d[i][1];
			if(nr<0 || nr>=n || nc<0 || nc>=n) continue;
			if(check[nr][nc]) continue; //방문한자리
			if(area[nr][nc]>sw) continue; //큰물고기
			else if(area[nr][nc]==sw || area[nr][nc] ==0){
				check[nr][nc] = true;
				q.push(Pi{nr,nc,dd+1});
			}
			else{ //먹을수있는물고기
				check[nr][nc] = true;
				if(eatlst.empty()){
					eatlst.push_back(make_pair(nr,nc));
					mind =dd+1;
				}
				else if(dd+1<=mind)
					eatlst.push_back(make_pair(nr,nc));
			}
		}
	}
	if(eatlst.empty())
		return ;
	else{
		sort(eatlst.begin(),eatlst.end());
		int rr = eatlst[0].first, cc = eatlst[0].second;
		area[rr][cc] = 0;
		eatn++;
		if(eatn>=sw) {
			sw++;
			eatn =0;
		}
		t += mind;
		eatlst.clear();
		for(int i = 0; i<n;i++)
            for(int j =0;j<n;j++)	check[i][j] = false;
		sr = rr, sc = cc;
		bfs();
	}
}
int main(){
	cin>>n;
	for(int i = 0; i<n;i++){
		for(int j =0;j<n;j++){
			 cin>>area[i][j];
			 if(area[i][j]==9) {
			 	sr = i, sc = j;
			 	area[i][j] = 0;
			 }
		}
	}
	bfs();
	cout<<t;
	return 0;
}