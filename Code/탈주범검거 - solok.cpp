//코딩 20분 디버깅40분 
//변수 x와 y를 헷갈림 
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int testCase;
const int MAX = 60;
int pipe[8][4] = { {0,0,0,0} ,{1,1,1,1},{1,1,0,0},{0,0,1,1},{1,0,0,1},{0,1,0,1},{0,1,1,0},{1,0,1,0} };//상 하 좌 우
int d[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//상하좌우
struct PI {
	int x, y;
	int t;//시간
};
int n, m, rx, ry,l;
int tunnel[MAX][MAX];
bool check[MAX][MAX];
int ans = 0;
bool connectionFunc(int in, int out, int direction) {
	if (pipe[in][direction]) {
		if (direction == 0) {
			if (pipe[out][1]) 	return true;
		}
		else if (direction == 1) {
			if (pipe[out][0]) return true;
		}
		else if (direction == 2) {
			if (pipe[out][3]) return true;
		}
		else if (direction == 3) {
			if (pipe[out][2]) return true;
		}
	}
	return false;
}
void BFS(int x, int y) {
	queue<PI> q;
	q.push({ x,y,1 });
	check[x][y] = 1;
	while (!q.empty()) {
		ans++;
		
		int xx = q.front().x;
		int yy = q.front().y;
		int tt = q.front().t;
		//printf("%d %d %d\n", xx, yy,tt);
		q.pop();
		if (tt >= l) continue;
		for (int i = 0; i < 4; i++) {
			int nextx = xx + d[i][0];
			int nexty = yy + d[i][1];
			
			if (nextx<0 || nextx>=n || nexty < 0 || nexty >= m) continue;
			if (!check[nextx][nexty] && connectionFunc(tunnel[xx][yy],tunnel[nextx][nexty], i)) {
				q.push({ nextx,nexty,tt + 1 });
				check[nextx][nexty] = true;
				//printf("%d %d\n", nextx,nexty);
			}
		}
	}
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		ans = 0;
		scanf_s("%d %d %d %d %d", &n,&m,&rx,&ry,&l);
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < m; j++) 
				scanf_s("%d", &tunnel[i][j]);
	
		BFS(rx, ry);
		//CHECK초기화
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				check[i][j] = false;
		printf("#%d %d\n", tt, ans);
	}
	return 0;
}