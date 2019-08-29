#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int MAX = 15;
struct PI {
	int x, y;
};
int area[MAX][MAX];
PI person[MAX], stair[MAX];
bool check[MAX];
int personN = 0, stairN = 0;
int testCase, n; // 원자갯수
int stairInfo1[MAX], stairInfo2[MAX];
int mintime = 987987987;
int s1, s2;
void calcDistance() {
	int sx = stair[0].x, sy = stair[0].y;
	for (int p = 0; p < personN; p++) {
		int d = int(abs(sx - person[p].x)) + int(abs(sy - person[p].y));
		stairInfo1[p] = d;
	}
	s1 = area[sx][sy];
	sx = stair[1].x, sy = stair[1].y;
	for (int p = 0; p < personN; p++) {
		int d = int(abs(sx - person[p].x)) + int(abs(sy - person[p].y));
		stairInfo2[p] = d;
	}	
	s2 = area[sx][sy];
} 
void dfs(int idx) {
	if (idx >= personN) {
		int first[MAX], ffront = 0, frear = 0;
		int second[MAX], sfront = 0, srear = 0;
		
		int stair1[100], stair2[100];
		int onefront = 0, onerear = 0, twofront = 0, tworear = 0;
		for (int i = 0; i < personN; i++) {
			if (!check[i]) 
				first[frear++] = stairInfo1[i]+1;
			else 
				second[srear++] = stairInfo2[i]+1;
		}
		int fn = frear, sn = srear;
		sort(first, first + fn);
		sort(second, second + sn);
		int t ;
		for (t = 1; ; t++) {
			for (int i = onefront; i<onerear; i++) {
				if (t >= stair1[i]) {
					onefront++;
					fn--;
				}
			}
			for (int i = ffront; i < frear; i++) {
				if (onerear - onefront >= 3) break;
				if (t >= first[ffront]) {
					stair1[onerear++] = (t + s1);
					ffront++;
				}
			}
			for (int i = twofront; i<tworear; i++) {
				if (t >= stair2[i]) {
					twofront++;
					sn--;
				}
			}
			
			for (int i = sfront; i < srear; i++) {
				if (tworear-twofront >= 3) break;
				if (t >= second[sfront]) {
					stair2[tworear++] = t + s2;
					sfront++;
				}
			}
			if (  fn<=0 &&  sn<=0) 
				break;
			
		}
		mintime = min(mintime, t);
		return;
	}
	else {
		check[idx] = false;
		dfs(idx + 1);
		check[idx] = true;
		dfs(idx + 1);
	}
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf_s("%d", &n);
		mintime = 987987987;
		personN = 0, stairN = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf_s("%d", &area[i][j]);
				if (area[i][j] == 1) person[personN++] = { i,j };
				else if(area[i][j] >= 2) stair[stairN++] = { i,j };
			}
		}
		
		calcDistance();
		dfs(0);
		printf("#%d %d\n", tt, mintime);
		for (int i = 0; i < personN; i++) person[i] = { 0,0 };
		for (int i = 0; i < stairN; i++) stair[i] = { 0,0 };
	}
	return 0;
}