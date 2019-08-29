#include <iostream>
#include<algorithm>
using namespace std;
const int MAX= 15;
struct PI {	int r, c;};
int T, n, k, area[MAX][MAX];
int topidx, maxpath, high;
PI top[MAX];
bool check[MAX][MAX];
int d[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
void dfs(int r,int c,int path) {
	maxpath = max(maxpath, path);
	for (int i = 0; i < 4; i++) {
		int nr = r + d[i][0], nc = c + d[i][1];
		if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
		if (check[nr][nc]|| area[nr][nc]>=area[r][c]) continue;
		check[nr][nc] = true;
		dfs(nr, nc, path + 1);
		check[nr][nc] = false;
	}
}
int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> k;
		topidx = 0, maxpath =1,high =-1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> area[i][j];
				if (high < area[i][j]) high = area[i][j];
			}
		}
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) 
				if (area[i][j] == high) 
					top[topidx++] = { i,j };
				
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int cut = 0; cut <= k; cut++) {
					if (area[i][j] - cut < 0) break;
					area[i][j] -= cut;
					for (int idx = 0; idx < topidx; idx++) {
						check[top[idx].r][top[idx].c] = true;
						dfs(top[idx].r, top[idx].c, 1);
						check[top[idx].r][top[idx].c] = false;
					}
					area[i][j] += cut;
				}
			}
		}
		cout << "#" << t << " " << maxpath << endl;
	}
	return 0;
}
