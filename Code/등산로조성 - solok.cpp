//코딩 20분 디버깅 25분 총 45분걸림
// 2019-04-09 03:26
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct PI {
	int x, y;
};
const int MAX = 15;
int d[4][2] = { {1,0} ,{-1,0} ,{0,1} ,{0,-1} };
int area[MAX][MAX];
bool check[MAX][MAX];
int testCase,n,k;
PI startLst[MAX];
int maxPathL;
int startidx = 0;
void dfs(int x, int y, int pathL) {
	maxPathL = max(maxPathL, pathL);
	for (int i = 0; i < 4; i++) {
		int nextx = x + d[i][0];
		int nexty = y + d[i][1];
		if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) continue;			
		if (!check[nextx][nexty] &&area[x][y] > area[nextx][nexty]) { //체크안한곳만 방문한다는 조건을 빼먹음...
			check[nextx][nexty] = true;
			dfs(nextx, nexty, pathL+1);
			check[nextx][nexty] = false;                 //실수!!!!! 나갈 대 체크해제 해야함.
		}
		
	}
}
int main() {
	scanf("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf("%d %d", &n,&k);
		startidx = 0;
		int high = 0;
		for (int i = 0;i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &area[i][j]);
				high = max(high, area[i][j]);
			}
		}
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) 
				if (high == area[i][j]) 
					startLst[startidx++] ={ i,j };     //최대한 벡터말고 배열을 사용하자
	
		maxPathL=0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int cut = 0; cut <= k; cut++) {
					if (area[i][j] - cut < 0) continue;
					area[i][j] = area[i][j] - cut;
					for (int start = 0; start<startidx; start++) {
						check[startLst[start].x][startLst[start].y] = true;
						dfs(startLst[start].x, startLst[start].y,1);
						for (int q = 0; q < n; q++) 
							for (int p = 0; p < n; p++) 
								check[q][p] = false;
					}
					area[i][j] = area[i][j] + cut;
				}
			}
		}
		printf("#%d %d\n", tt, maxPathL);
	}
	return 0;
}