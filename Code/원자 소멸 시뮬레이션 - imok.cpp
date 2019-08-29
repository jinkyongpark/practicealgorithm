#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX = 2050;
struct Atom {
	int x;
	int y;
	int direction;
	int power;
};
struct Area {
	int direction;
	int power;
	int atomN;
};
struct TmpArea {
	int direction = -1;//아무것도 아닌 곳
	int power;
	int atomN;
	int cnt = 0;
};
struct Tmp {
	int x, y;
};
Atom atom[1010];
bool atomcheck[1010]; //i번째원소가 사라졌는지
Area area[MAX][MAX];
TmpArea tmparea[MAX][MAX];
int testCase, n; // 원자갯수
int atomnum = 0;
vector<Tmp> tmp;
int d[4][2] = { { 1,0 },{ -1,0 },{ 0,-1 },{ 0,1 } };  // 상 하 좌 우
bool rev(int a, int b) {
	if (a == 0 && b == 1) return true;
	if (a == 1 && b == 0) return true;
	if (a == 2 && b == 3) return true;
	if (a == 3 && b == 2) return true;
	return false;
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf_s("%d", &n);
		atomnum = 1;
		for (int i = 1; i <= n; i++) {
			scanf_s("%d %d %d %d", &atom[i].y, &atom[i].x, &atom[i].direction, &atom[i].power);
			atom[i].y += 1000;
			atom[i].x += 1000;
			area[atom[i].x][atom[i].y] = { atom[i].direction, atom[i].power ,i };
			atomnum++;
		}
		int t = 0;
		int tEnergy = 0;
		for (t = 0; 1; t++) {
			int checkN = 0;
			for (int i = 1; i < atomnum; i++) {
				if (atomcheck[i]) {
					checkN++;
					continue;
				}
				int x = atom[i].x, y = atom[i].y;
				int nextx = x + d[atom[i].direction][0];
				int nexty = y + d[atom[i].direction][1];
				if (nextx < 0 || nextx >= 2002 || nexty < 0 || nexty >= 2002) {
					atomcheck[i] = true;
					area[x][y] = { 0,0,0 };
				}
				else if (area[nextx][nexty].power > 0 && rev(atom[i].direction, atom[area[nextx][nexty].atomN].direction)) { //중간에 만남(0.5초)
					atomcheck[i] = true; //현재 노드 체크
					atomcheck[area[nextx][nexty].atomN] = true; // 현재 노드가 이동할 곳에 있는 노드 체크
					tEnergy += area[nextx][nexty].power; //에너지 추가
					tEnergy += area[x][y].power; //에너지 추가
					area[x][y] = { 0,0,0 };
					area[nextx][nexty] = { 0,0,0 };
				}
				else if (tmparea[nextx][nexty].cnt > 0) { // 다음 이동경로가 일치
					atomcheck[i] = true; //현재노드 체크
					atomcheck[tmparea[nextx][nexty].atomN] = true; //그자리에 이동예정이었던 노드 체크
					area[x][y] = { 0,0,0 };
					tmparea[nextx][nexty] = { -1, tmparea[nextx][nexty].power + atom[i].power, 1008,tmparea[nextx][nexty].cnt + 1 };
					//에너지추가는 업데이트시 CNT확인할때 하자.
				}
				else if (tmparea[nextx][nexty].cnt == 0) { //다음 경로에 아무것도 없음
					tmparea[nextx][nexty] = { atom[i].direction, atom[i].power,i, 1 };
					tmp.push_back({ nextx,nexty });
					area[x][y] = { 0,0,0 };
				}
			}
			//printf("%d\n", checkN);
			if (checkN + 1 == atomnum)  break;
			int size = tmp.size();
			for (int i = 0; i < size; i++) {
				int xx = tmp[i].x;
				int yy = tmp[i].y;
				if (tmparea[xx][yy].cnt > 1) {
					tEnergy += tmparea[xx][yy].power;
				}
				else {
					area[xx][yy].atomN = tmparea[xx][yy].atomN;
					area[xx][yy].direction = tmparea[xx][yy].direction;
					area[xx][yy].power = tmparea[xx][yy].power;
					atom[area[xx][yy].atomN].x = xx;
					atom[area[xx][yy].atomN].y = yy;
				}
				//초기화
				tmparea[xx][yy] = { -1,0,0,0 };
			}
			tmp.clear();
		}
		for (int i = 1; i <= atomnum; i++)
			atomcheck[i] = false;
		printf("#%d %d\n", tt, tEnergy);
	}
	return 0;
}