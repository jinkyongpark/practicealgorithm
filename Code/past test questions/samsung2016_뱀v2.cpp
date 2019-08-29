#include <cstdio>
#include <queue>
#include <math.h>
using namespace std;
const int MAX = 110;
int dommy[MAX][MAX] = { 0, };
int d[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{-1,0} }; //오 아래 왼 위
int n, k, l;
int appleN = 0;
queue<pair<int, int>> snake;
queue<pair<int, int>> dLst;
int sx = 1, sy = 1;
int gamestart() {
	int x = sx, y = sy;
	int dNum = 0;
	int t;
	for (t = 1;; t++) {
		
		int nextx = x + d[dNum][0];
		int nexty = y + d[dNum][1];
		//printf("%d초 :%d %d\n",t, nextx, nexty);
		if (nextx<1 || nextx>n || nexty<1 || nexty>n) return t;
		if (dommy[nextx][nexty] == 2) return t;
		if (dommy[nextx][nexty] == 1) {
			//사과 만남
			snake.push(make_pair(nextx, nexty));
			dommy[nextx][nexty] = 2;
		}
		else { // 비어있는곳에 오면 지금까지 거 다 0으로만들고 이동할자리만 2
			int tmpx = snake.front().first;
			int tmpy = snake.front().second;
			snake.pop();
			dommy[tmpx][tmpy] = 0;
			snake.push(make_pair(nextx, nexty));
			dommy[nextx][nexty] = 2;
		}
		if (!dLst.empty()) {
			if (dLst.front().first == t) {
				if (dLst.front().second == 'L') {
					if (dNum - 1 < 0) dNum = 3;
					else dNum -= 1;
				}
				else {
					if (dNum + 1 > 3) dNum = 0;
					else dNum += 1;
				}
				dLst.pop();
			}
		}
		x = nextx;
		y = nexty;
	}
}
int main() {
	scanf("%d", &n);
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		dommy[x][y] = 1;
	}
	scanf("%d", &l);
	for (int i = 0; i < l; i++) {
		int  t;
		char direction;
		scanf("%d %c", &t, &direction);
		dLst.push(make_pair(t, direction));
	
	}
	snake.push(make_pair(sx, sy));
	dommy[sx][sy] = 2;

	
	printf("%d", gamestart() );
	return 0;
}
