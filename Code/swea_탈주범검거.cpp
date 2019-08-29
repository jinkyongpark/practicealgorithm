#include <iostream>
#include <algorithm>
#include<queue>
using namespace std;
struct PI { int r, c,t; };
const int MAX = 60;
int T, n,m,R,C,maxtime;
int ans, tunnel[MAX][MAX];
bool check[MAX][MAX];
int d[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int pipe[8][4] = { {0,0,0,0},{1,1,1,1},{1,1,0,0},{0,0,1,1},
		  {1,0,0,1},{0,1,0,1},{0,1,1,0},{1,0,1,0} };
int rev[4] = { 1,0,3,2 };

bool connectionpipe(int r1, int c1, int r2, int c2,int direction) {
	int in = tunnel[r1][c1], out = tunnel[r2][c2];
	if(pipe[in][direction] && pipe[out][rev[direction]])
		return true;
	else return false;
}

void countPossibleZone() {
	check[R][C] = true;
	queue<PI> q;
	q.push(PI{ R,C,1 });
	while (!q.empty()) {
		int r = q.front().r, c = q.front().c, t = q.front().t;
		q.pop();
		if (t >= maxtime ) continue;
		for (int i = 0; i < 4; i++) {
			int nr = r + d[i][0], nc = c + d[i][1];
			if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
			if (check[nr][nc]) continue;
			if (!connectionpipe(r, c, nr, nc,i)) continue;
			check[nr][nc] = true;
			q.push(PI{ nr,nc,t+1 });
			ans++;
		}
	}
}

int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		ans = 1;
		cin >> n >> m >> R >> C>>maxtime;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> tunnel[i][j];
		countPossibleZone();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) check[i][j] = false;
		cout << "#" << t << " " << ans << endl;
	}
	return 0;
}
