#include <queue>
#include<vector>
#include<iostream>
using namespace std;
const int Max = 55;
int n,L,R;
int area[Max][Max];
bool check[Max][Max];
bool flag = false;
int ans =0;
int d[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
void bfs(int r,int c){
	check[r][c] = true;
	queue<pair<int,int>> q;
	q.push(make_pair(r,c));
	vector<pair<int,int>> s;
	int sum = area[r][c];
	s.push_back(make_pair(r,c));
	while(!q.empty()){
		int rr = q.front().first, cc = q.front().second;
		q.pop();
		for(int i =0;i<4;i++){
			int nr = rr + d[i][0], nc = cc + d[i][1];
			if(nr<0 || nr>=n || nc<0 || nc>=n) continue;
			if(check[nr][nc]) continue;
			int diff =area[rr][cc]-area[nr][nc];
			if(diff<0) diff*=-1;
			if(diff>=L && diff<=R){
				s.push_back(make_pair(nr,nc));
				sum += area[nr][nc];
				check[nr][nc] = true;
				q.push(make_pair(nr,nc));
			}
		}
	}
	if(s.size()==1) return ;
	int chv = sum/s.size();
	for(int i=0;i<s.size();i++)
		area[s[i].first][s[i].second] = chv;
	flag = true;
}
int main(){
	cin>>n>>L>>R;
	for(int i =0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>area[i][j];
	
	while(1){
		flag = false;
		for(int i =0;i<n;i++)
			for(int j=0;j<n;j++)
				if(!check[i][j]) bfs(i,j);
		if(!flag) break;
		ans++;
		for(int i =0;i<n;i++)
			for(int j=0;j<n;j++) check[i][j] = false;
	}
	cout<<ans;
	return 0;
}
