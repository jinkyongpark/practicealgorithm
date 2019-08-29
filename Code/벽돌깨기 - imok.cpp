// 설계 20분  코딩 1시간15분
//tmparea를 어쩔때이용하는지 설계시 좀더 확실하게 해야함. 여기서 디버깅 오래걸림
//오늘도 d[4][2] 잘못씀..
//구슬을 쏘는 경우의수를 재귀로 돌렸는데 이부분이 더 익숙해야 할것같다. 이부분 설계를 7분 소요. 시험에서는 3분안에 해야할듯
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAX = 20;
int testCase,n,w,h;
int area[MAX][MAX];
int tmparea[MAX][MAX];
int d[4][2] = { {-1,0}, {0,1} ,{1,0} ,{0,-1} };
bool check[MAX][MAX];
int ans = 987987978;
int beadLst[MAX]; //i번째에 어느 colum에 쏠건지 저장
void breakblock(int row, int col) {
	queue<pair<int, int>> q;
	q.push(make_pair(row, col));
	check[row][col] = true;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			for (int maxL = 1; maxL <= tmparea[x][y] - 1; maxL++) {
				int nextx = x + d[i][0] * maxL;
				int nexty = y + d[i][1] * maxL;
				if (nextx < 0 || nextx >= h || nexty < 0 || nexty >= w) break;
				if (!check[nextx][nexty]) {
					check[nextx][nexty] = true;
					if(tmparea[nextx][nexty]>0)
						q.push(make_pair(nextx, nexty));
				}
			}
		}
		
	}
}
void dropblock() {
	for (int col = 0; col < w; col++) {
		int tmpidx = h - 1;
		for (int row = h-1; row >=0; row--) {
			if (tmparea[row][col] >=1 && check[row][col] == false ) tmparea[tmpidx--][col] =  tmparea[row][col];
		}
		for (; tmpidx >= 0; tmpidx--) {
			tmparea[tmpidx][col] = 0;
		}
	}	
}
int gamestart() {
	for (int i = 0; i < n; i++) {
		//체크 초기화
		for (int row = 0; row < h; row++) {
			for (int col = 0; col < w; col++) {
				check[row][col] = false;
			}
		}
		int lineN = beadLst[i]; // column번호
		int toprow;
		for (int row = 0; row < h; row++) {
			toprow = row;
			if (tmparea[row][lineN] != 0)
				break; //제일 위에있는 벽돌 찾음
		}
		breakblock(toprow, lineN); //벽돌 깨기
		dropblock(); //벽돌내리기
		
	}
	int cnt = 0;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (tmparea[row][col] > 0)cnt++;
		}
	}
	return cnt;
}
void bead(int idx) {
	if (idx >= n) {
		for (int row = 0; row < h; row++)
			for (int col = 0; col < w; col++)
				tmparea[row][col] = area[row][col];
		ans =min(ans,gamestart());
	}
	else {
		for (int i = 0; i < w; i++) {
			beadLst[idx] = i;
			bead(idx + 1);
		}
	}
}
int main() {
	scanf("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf("%d %d %d", &n, &w, &h);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++)
				scanf("%d", &area[i][j]);
		}
		ans = 987987987;
		for (int row = 0; row < h; row++)
			for (int col = 0; col < w; col++)
				tmparea[row][col] = area[row][col];
		bead(0);
		printf("#%d %d\n",tt, ans);
	}
	return 0;
}