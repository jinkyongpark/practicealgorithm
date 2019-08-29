#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX = 35;
int testcase;
int n, m, k;
struct Cell {
	int lifeT = 0;
	int startT = 0;
	int dieT = 0;
	int state = 0;//0 - 아무것도 아님 1- 비활성화 예정 2 - 비활성화 3 - 활성화 4 - 죽음
};
struct PI {
	int x, y;

};
Cell area[700][700];
int d[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
vector<PI> totalLst, tmp;
int main() {
	scanf_s("%d", &testcase);
	for (int tt = 1; tt <= testcase; tt++) {
		scanf_s("%d %d %d", &n, &m, &k);
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int t;
				scanf_s("%d", &t);
				if (t > 0) {
					area[i + 500][j + 500] = { t,t,2 * t ,2 };
					totalLst.push_back({ i + 500,j + 500 });
				}
				else
					area[i + 500][j + 500] = {0,0,0,0};
			}
		}
		int t;
		for (int i = 495; i < 505; i++) {
			for (int j = 495; j < 505; j++) {
				printf("%d ", area[i][j].state);
			}
			printf("\n");
		}
		printf("\n");
		int size = totalLst.size();
		for (t = 1; t <= k; t++) {
			for (int i = 495; i < 505; i++) {
				for (int j = 495; j < 505; j++) {
					printf("%d ", area[i][j].state);
				}
				printf("\n");
			}
			printf("\n");
			size = totalLst.size();
			for (int i = 0; i < size; i++) {
				int x = totalLst[i].x;
				int y = totalLst[i].y;
				int state = area[x][y].state;
				if (state == 0 || state == 4) continue;
				if (state == 2) { //비활성화중인거
					if (area[x][y].startT == t)
						area[x][y].state = 3;
				}
				else if (state == 3) {
					//번식
					for (int dd = 0; dd < 4; dd++) {
						int nextx = x + d[dd][0];
						int nexty = y + d[dd][1];
						// 범위 나가면 안됨- 범위를 넓혀야
						if (area[nextx][nexty].state > 1) continue;
						int maxlifet = area[x][y].lifeT;
						if (area[nextx][nexty].state == 0) {
							tmp.push_back({ nextx,nexty });
						}
						else  maxlifet = max(area[nextx][nexty].lifeT, maxlifet);
						area[nextx][nexty] = { maxlifet,t + maxlifet,t + maxlifet * 2, 1 };

					}
					if (area[x][y].dieT == t)
						area[x][y].state = 4;
				}
			}
			int tmpsize = tmp.size();
			for (int i = 0; i < tmpsize; i++) {
				int x = tmp[i].x, y = tmp[i].y;
				area[x][y].state = 2;
				totalLst.push_back({ x,y });
			}
			tmp.clear();
		}

		int ans = 0;
		size = totalLst.size();
		for (int i = 0; i < size; i++) {
			int x = totalLst[i].x, y = totalLst[i].y;
			if (area[x][y].state == 2 || area[x][y].state == 3) ans++;
		}
		printf("#%d %d\n", tt, ans);
	}
	return 0;
}