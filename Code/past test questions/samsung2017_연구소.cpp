#include<iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX =15;
struct pi{int R,C;};
int d[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int n,m, maxans =-987987987;
vector<pi> emptyspace, virus;
int area[MAX][MAX];
bool check[MAX][MAX];
void spreadVirus(int rr, int cc){
	check[rr][cc] = true;
	queue<pi> q;
	q.push(pi{rr,cc});
	while(!q.empty()){
		int r = q.front().R, c = q.front().C;
		q.pop();
		for(int i =0;i<4;i++){
			int nr = r+ d[i][0], nc = c + d[i][1];
			if(nr<0 || nr>=n || nc<0 || nc>=m) continue;
			if(check[nr][nc] || area[nr][nc] != 0) continue;
			q.push(pi{nr,nc});
			check[nr][nc] = true;
		}
	}
}
void selectThreeSpace(int idx,int startidx){
	if(idx>=3){
		for(int v = 0 ; v<virus.size();v++)
			spreadVirus(virus[v].R, virus[v].C);
		int ans =0;
		for(int r =0;r<n;r++){
			for(int c=0 ;c<m;c++){
				if(area[r][c]==0 && check[r][c]==false)	ans++;
				else if(check[r][c])	check[r][c] = false;
			}
		}
		maxans = max(maxans, ans);
		return ;
	}
	for(int i = startidx; i<emptyspace.size();i++){
		int r = emptyspace[i].R, c = emptyspace[i].C;
		area[r][c] = 1;
		selectThreeSpace(idx+1, i+1);
		area[r][c] = 0;
	}
}
int main(){
	cin>>n>>m;
	for(int r=0;r<n;r++){
		for(int c=0 ;c<m;c++){
			cin>>area[r][c];
			if(area[r][c]==0) emptyspace.push_back(pi{r,c});
			else if(area[r][c]==2) virus.push_back(pi{r,c});
		}
	}
	selectThreeSpace(0,0);
	cout<<maxans;
	return 0;
}
