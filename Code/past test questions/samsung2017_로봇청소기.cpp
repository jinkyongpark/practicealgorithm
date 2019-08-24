#include <iostream>
#include <algorithm>
using namespace std;
const int MAX = 55;
int d[4][2] = {{-1,0},{0,1},{1,0},{0,-1}}; // 북 동 남 서
int leftD[4] = {3,0,1,2}; //서북동남
int revD[4] = {2,3,0,1};
int room[MAX][MAX];
int n, m, R,C,dd;
int ans =0,idx =2;
void cleaningRoom(){
	bool flag = false;
	room[R][C] = idx++; //청소된 빈공간
	ans++;
	int r = R, c = C;	
	while(1){
		if(flag) break;
		flag = true;
		int ld = dd;
		for(int i =0;i<4;i++){
			ld = leftD[ld]; //왼쪽방향
			int nr = r + d[ld][0], nc = c + d[ld][1];
			if(nr<0 || nr>= n || nc<0 ||nc>=m) continue;
			if(room[nr][nc]) continue;
			//청소할공간이있을때
			flag = false;
			room[nr][nc] = idx++;
			ans++;
			dd= ld, r= nr, c= nc;
			break;
		}
		if(flag){
			int br = r+ d[revD[dd]][0], bc = c + d[revD[dd]][1];
			if(br<0 || br>= n || bc<0 ||bc>=m) continue;
			if(room[br][bc]!=1) {
				r= br, c= bc;
				flag = false;
			}
		} 
	}
}
int main(){
	cin>>n>>m;
	cin>>R>>C>>dd;
	for(int r =0;r<n;r++)
		for(int c = 0;c<m;c++)
			cin>>room[r][c];
	
	cleaningRoom();
	cout <<ans;
	return 0;
}
