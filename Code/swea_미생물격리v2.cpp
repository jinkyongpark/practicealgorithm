#include <iostream>
#include<algorithm>
using namespace std;
const int MAX = 110;
struct cell { 
	int cnt=0,d=0,maxn=0; };
int T,n,m,k;
bool flag;
int ans;
cell area[MAX][MAX],tmparea[MAX][MAX];
int dd[5][2] = { {},{-1,0},{1,0},{0,-1},{0,1} };
int rev[5] = { 0,2,1,4,3 };
int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> m >> k;
		ans = 0;
		for (int i = 0; i < k; i++) {
			int r, c;
			cin >> r >> c;
			cin >> area[r][c].cnt >> area[r][c].d;
		}
		for (int time = 0; time < m; time++) {
			//이동예정값
			for (int r = 0; r < n; r++) {
				for (int c = 0; c < n; c++) {
					if (!area[r][c].cnt) continue;
					int direction = area[r][c].d;
					int nr = r + dd[direction][0], nc = c + dd[direction][1];
					//경계값
					if (nr == 0 || nr == n - 1 || nc == 0 || nc == n - 1) 
							tmparea[nr][nc].cnt  = area[r][c].cnt / 2, tmparea[nr][nc].d = rev[direction] , tmparea[nr][nc].maxn =area[r][c].cnt ;
					
					//다음값에 뭐가 없을 때
					else if (tmparea[nr][nc].cnt == 0) 
						tmparea[nr][nc].cnt  = area[r][c].cnt, tmparea[nr][nc].d = direction , tmparea[nr][nc].maxn =area[r][c].cnt ;
					//다음에 뭐가 있을 때
					else if (tmparea[nr][nc].cnt > 0) {
						if (tmparea[nr][nc].maxn < area[r][c].cnt) {
							tmparea[nr][nc].maxn = area[r][c].cnt;
							tmparea[nr][nc].d = direction;
						}
						tmparea[nr][nc].cnt += area[r][c].cnt;
					}
					area[r][c].cnt=  0, area[r][c].d = 0;
				}
			}
			//업데이트
			for (int r = 0; r < n; r++) {
				for (int c = 0; c < n; c++) {
					if (!tmparea[r][c].cnt) continue;
					area[r][c].cnt = tmparea[r][c].cnt, area[r][c].d = tmparea[r][c].d;
					tmparea[r][c].cnt =0, tmparea[r][c].d = 0, tmparea[r][c].maxn =0;
				}
			}
		}
		for (int r = 0; r < n; r++)
			for (int c = 0; c < n; c++) 
				ans += area[r][c].cnt;
		cout << "#" << t << " " <<ans  << endl;
		//초기화
		for (int r = 0; r < n; r++)
			for (int c = 0; c < n; c++) 
				area[r][c].cnt = 0, area[r][c].d = 0;
	}
	return 0;
}
