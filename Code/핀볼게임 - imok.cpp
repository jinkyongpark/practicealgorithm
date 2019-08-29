//재귀로 돌리면 스택에 쌓여서 런타임에러
//이럴땐 재귀문을 반복문으로 바꾸자 - 최대한 반복문이용하는게 좋은거같다.
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 110;
struct PI {
	int x, y;
};
PI emptyLst[MAX*MAX], wormLst[MAX];
PI blackhole[10];
int area[MAX][MAX];
PI wormhole[MAX][MAX];
int testCase, n, blackidx = 0, emptynum = 0 , wormnum = 0;
int sx, sy;
int d[4][2] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };  //위 오 아 왼
int ans = -987987978, cnt = 0;
bool flag;
int changeDirection(int direction, int wallN) { //벽번호를 맞았을 때 방향에 따라 어느방향으로 바꿀지
	switch (wallN) {
	case -1:
		if (direction == 0) return 2;
		else if (direction == 1) return 3;
		else if (direction == 2) return 0;
		else return 1;
		break;
	case 1:
		if (direction == 0) return 2;
		else if (direction == 1) return 3;
		else if (direction == 2) return 1;
		else return 0;
		break;
	case 2:
		if (direction == 0) return 1;
		else if (direction == 1) return 3;
		else if (direction == 2) return 0;
		else return 2;
		break;
	case 3:
		if (direction == 0) return 3;
		else if (direction == 1) return 2;
		else if (direction == 2) return 0;
		else return 1;
		break;
	case 4:
		if (direction == 0) return 2;
		else if (direction == 1) return 0;
		else if (direction == 2) return 3;
		else return 1;
		break;
	case 5:
		if (direction == 0) return 2;
		else if (direction == 1) return 3;
		else if (direction == 2) return 0;
		else return 1;
		break;
	}
	return 0;
}
void gamestart(int x, int y, int direction) {
	while (1) {
		//종료조건
		if (flag && x == sx && y == sy) //처음에는 flag가 false고  처음 아닐때는 바로 flag가 바뀜
			return;
		flag = true;
		int nextx = x + d[direction][0];
		int nexty = y + d[direction][1];
		for (int i = 0; i < blackidx; i++) 
			if (nextx == blackhole[i].x && nexty == blackhole[i].y) 
				return;
		
		if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) {
			cnt++;
			int cd = changeDirection(direction, -1); //반대
			x = nextx;
			y = nexty;
			direction = cd;
		}
		else if (area[nextx][nexty] >= 1 && area[nextx][nexty] <= 5) {
			cnt++;
			int cd = changeDirection(direction, area[nextx][nexty]);
			x = nextx;
			y = nexty;
			direction = cd;
		}
		else if (area[nextx][nexty] >= 6 && area[nextx][nexty] <= 10) {
			int jumpx = wormhole[nextx][nexty].x;
			int jumpy = wormhole[nextx][nexty].y;
			x = jumpx;
			y = jumpy;
		}
		else {
			x = nextx;
			y = nexty;
		}
	}
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf_s("%d", &n);
		ans = -987987987;
		blackidx = 0, emptynum = 0, wormnum = 0;
		cnt = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf_s("%d", &area[i][j]);
				if (area[i][j] == 0) emptyLst[emptynum++]={ i,j };
				else if (area[i][j] == -1) blackhole[blackidx++] = { i,j };
				else if (area[i][j] >= 6 && area[i][j] <= 10) {
					wormLst[wormnum++]={ i,j };
				}
			}
		}
		//반대 웜홀을 저장
		for (int i = 0; i < wormnum; i++) {
			int tx = wormLst[i].x;
			int ty = wormLst[i].y;
			int tmp = area[tx][ty];
			for (int j = 0; j < wormnum; j++) {
				if (wormLst[j].x == tx && wormLst[j].y == ty) continue;
				if (tmp == area[wormLst[j].x][wormLst[j].y]) 
					wormhole[tx][ty] = { wormLst[j].x ,wormLst[j].y };
			}
		}

		//모든 비어있는 곳에서 4방향으로 해본다.
		for (int i = 0; i < emptynum; i++) {
			for (int dd = 0; dd < 4; dd++) {
				cnt = 0;
				sx = emptyLst[i].x;
				sy = emptyLst[i].y;
				flag = false;
				gamestart(sx, sy, dd);
				ans = max(ans, cnt);
			}
		}
		//초기화
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) 
				wormhole[i][j] = { 0,0 };
		for (int i = 0; i < blackidx; i++)
			blackhole[i] = { 0,0 };
		for (int i = 0; i < emptynum; i++)
			emptyLst[i] = { 0,0 };
		for (int i = 0; i < wormnum; i++)
			wormLst[i] = { 0,0 };
		printf("#%d %d\n", tt, ans);
	}
	return 0;
}