#include <iostream>
using namespace std;
const int MAX = 105;
struct Shark {
	int r, c; //좌표
	int v; //속도
	int d; //1- 위 2- 아래 3- 오른쪽 4- 왼쪽
	int w; //크기
	bool death = false; //true면 잡히거나 먹힌 상어
};
int d[5][2] = { {0,0}, {-1,0},{1,0},{0,1},{0,-1} };
Shark shark[MAX*MAX];
int area[MAX][MAX] = { 0, };
int R,C,M;
int main() {
	int ans = 0;//잡은 상어크기의 합
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		cin >> shark[i].r >> shark[i].c >> shark[i].v >> shark[i].d >> shark[i].w;
		area[shark[i].r][shark[i].c] = i;
	}
	for (int c =1; c <= C; c++) {
		//상어잡기
		for (int r = 1; r <= R; r++) {
			if (!area[r][c]) continue;
			ans += shark[area[r][c]].w;
			shark[area[r][c]].death = true;
			area[r][c] = 0;
			break;
		}
		//상어이동
		int tmparea[MAX][MAX] = { 0, };
		for (int i = 1; i <= M; i++) {
			if (shark[i].death) continue;
			int rr = shark[i].r, cc = shark[i].c;
			int dd = shark[i].d, vv = shark[i].v, ww = shark[i].w;
			int nextr, nextc;
			while(1) {
				nextr = rr + vv*d[dd][0];
				nextc = cc + vv*d[dd][1];
				if (nextr >= 1 && nextr <= R&& nextc >= 1 && nextc <= C) break;
				if (dd == 1) { vv -= rr-1; rr = 1;  dd = 2; }
				else if (dd == 2) { vv -= (R - rr); rr = R; dd = 1; }
				else if (dd == 3) { vv -= (C - cc); cc = C; dd = 4; }
				else if (dd == 4) { vv -= cc-1; cc = 1; dd = 3; }
			}
			if (tmparea[nextr][nextc]) {
				if (shark[tmparea[nextr][nextc]].w < ww) {
					shark[tmparea[nextr][nextc]].death = true;
					tmparea[nextr][nextc] = i;
				}
				else	shark[i].death = true;
			}
			else 	tmparea[nextr][nextc] = i;
			shark[i].r = nextr, shark[i].c = nextc, shark[i].d = dd;
		}
		for (int rr = 1; rr <= R; rr++)
			for (int cc = 1; cc <= C; cc++)
				area[rr][cc] = tmparea[rr][cc];
	}
	cout << ans;
	return 0;
}