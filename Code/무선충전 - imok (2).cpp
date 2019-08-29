//2019-04-10 36분
#include <cstdio> 
#include <math.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 10;
struct PI {
	int x, y;
	int d;
	int power;
};
int testCase;
vector<int> aa, bb;
int amove[110], bmove[110];
int d[5][2] = { { 0,0 },{ -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };
int m, battery;
PI blst[MAX];
int calc(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf_s("%d %d", &m, &battery);
		printf("%d", battery);
		int ans = 0;
		int ax = 1, ay = 1;
		int bx = 10, by = 10;
		for (int i = 0; i < m; i++)
			scanf_s("%d", &amove[i]);
		for (int i = 0; i < m; i++)
			scanf_s("%d", &bmove[i]);
		for (int i = 0; i < battery; i++)
			scanf_s("%d %d %d %d", &blst[i].y, &blst[i].x, &blst[i].d, &blst[i].power);

		for (int i = 0; i <= m; i++) {
			for (int i = 0; i < battery; i++) {
				int distance = calc(ax, ay, blst[i].x, blst[i].y);
				int distance2 = calc(bx, by, blst[i].x, blst[i].y);
				if (distance <= blst[i].d)
					aa.push_back(i);
				if (distance2 <= blst[i].d)
					bb.push_back(i);
			}
			int asize = aa.size(), bsize = bb.size();
			int tmp = 0;
			int maxval = 0;
			if (asize == 0 && bsize != 0) {
				for (int j = 0; j < bsize; j++)
					maxval = max(maxval, blst[bb[j]].power);
			}
			else if (bsize == 0 && asize != 0) {
				for (int j = 0; j < asize; j++)
					maxval = max(maxval, blst[aa[j]].power);
			}
			else if (asize != 0 && bsize != 0) {
				for (int j = 0; j < asize; j++) {
					for (int p = 0; p < bsize; p++) {
						if (aa[j] == bb[p]) {
							tmp = max(tmp, blst[aa[j]].power);
						}
						else {
							tmp = blst[aa[j]].power;
							tmp += blst[bb[p]].power;
						}
						maxval = max(maxval, tmp);
					}
				}
			}
			ans += maxval;
			printf("%d\n", maxval);
			ax = ax + d[amove[i]][0];
			ay = ay + d[amove[i]][1];
			bx = bx + d[bmove[i]][0];
			by = by + d[bmove[i]][1];
			aa.clear();
			bb.clear();
		}
		printf("#%d %d\n", tt, ans);
	}

	return 0;
}