#include <iostream>
#include<vector>
#include <queue>
using namespace std;
const int Max = 55;
bool checkvirus[15];
struct pi{
	int r,c;
};
vector<pi> virus,tvirus;
int tn=0,vn=0; //virus니아닌곳 갯수
int d[4][2] ={{-1,0},{1,0},{0,-1},{0,1}};
int area[Max][Max],tmparea[Max][Max];
int n,m,mintime=987987987;

int spreadvirus(){
	int ln = tn;// ln= 남아있수빈곳갯수, 이전에빈곳갯수
	
	queue<pair<pi,int>> q;
	for(int i=0;i<m;i++){
		q.push(make_pair(tvirus[i],0));
		tmparea[tvirus[i].r][tvirus[i].c] = 3;
	}
	while(!q.empty()){
		int r = q.front().first.r;
		int c = q.front().first.c;
		int t = q.front().second;
		q.pop();
		for(int i= 0;i<4;i++){
			int nextr = r +d[i][0];
			int nextc = c + d[i][1];
			if(nextr<0 || nextr>=n || nextc<0 || nextc>=n) continue;
			if(tmparea[nextr][nextc]==0 ){ //벽 
				tmparea[nextr][nextc] = 3;
				q.push(make_pair(pi{nextr,nextc},t+1));
				ln--;
			}
			else if (tmparea[nextr][nextc]==2) {//비활성바이러스
				tmparea[nextr][nextc] = 3;
				q.push(make_pair(pi{nextr,nextc},t+1));
			}
		}
		if(ln==0)  return t+1;	
	}
	return 987987987;

}
void choosevirus(int idx,int start){
	if(idx>=m) {
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				tmparea[i][j] = area[i][j];
		int t = spreadvirus();
		if(mintime>t)
			mintime =t;
		return;
	}
	for(int i=start;i<virus.size();i++){
		tvirus.push_back(virus[i]);
		choosevirus(idx+1,i+1);
		tvirus.pop_back();
	}
}
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>area[i][j];
			if(area[i][j]==0) 
				tn++;
			else if(area[i][j]==2){
				vn++;
				virus.push_back(pi{i,j});
			}
		}
	}
	if(tn==0) 
		cout<<0;
	else{
		choosevirus(0,0);
		if(mintime==987987987) cout<<-1;
		else cout<<mintime;
	}
	return 0;
}