//2019-04-10
//코딩 15분 디버깅불가
#include <cstdio> 
#include <math.h>
using namespace std;
const int MAX = 110;
int d[5][2] = { { 0,0 },{ -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
struct Info {
	int val = 0;
	int direction=0;
};
Info area[MAX][MAX];
Info tmparea[MAX][MAX];
int maxNum[MAX][MAX] = { 0, };
int n, m, k; // 크기, 격리시간, 군집수
int testCase;
int ans = 0;
int rev[5] = { 0,2,1,4,3 };
void move() {
	for (int t = 0; t < m; t++) {
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				if (area[x][y].val == 0) continue;
				int nextx = x + d[area[x][y].direction][0];
				int nexty = y + d[area[x][y].direction][1];
				if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) continue;
				if (nextx == 0 || nextx == n - 1 || nexty == 0 || nexty == n - 1) {  //벽
					tmparea[nextx][nexty].val = area[x][y].val / 2;
					if (tmparea[nextx][nexty].val != 0)
						tmparea[nextx][nexty].direction = rev[area[x][y].direction];
				}
				else {
					if (tmparea[nextx][nexty].val > 0) {//이미 여기로 이동할 값이 있는 경우
						if (area[x][y].val > maxNum[nextx][nexty]) {
							tmparea[nextx][nexty].direction = area[x][y].direction;
							maxNum[nextx][nexty] = area[x][y].val;
						}
					}
					else {
						tmparea[nextx][nexty].direction = area[x][y].direction;
						maxNum[nextx][nexty] = area[x][y].val;
					}
					tmparea[nextx][nexty].val += area[x][y].val;
				}
			}
		}
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				area[x][y] = tmparea[x][y];
				tmparea[x][y] = { 0,0 };
				maxNum[x][y] = 0;
			}
		}
	}
	for (int x = 0; x < n; x++)
		for (int y = 0; y < n; y++)
			ans += area[x][y].val;
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf_s("%d %d %d", &n, &m, &k);
		for (int i = 0; i < k; i++) {
			int x, y, num, d;
			scanf_s("%d %d %d %d", &x, &y, &num, &d);
			area[x][y].val = num;
			area[x][y].direction = d;
		}
		ans = 0;
		move();
		printf("#%d %d\n", tt, ans);
	}
	return 0;
}
