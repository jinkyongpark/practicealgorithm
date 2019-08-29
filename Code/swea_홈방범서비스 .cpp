#include <cstdio> //41분
#include <algorithm>
#include <cmath>
using namespace std;
const int MAX = 30; //16
int testCase;
struct home {
	int x, y;
};
int n, m;
int city[MAX][MAX];
home house[MAX*MAX];
int maxHouse, houseN;
int calccost(int k) {
	return (k*k) + (k - 1)*(k - 1);
}
void countHouse(int x, int y) {
	for (int l = 1; l<=2*n; l++) { //범위설정중요
		int cnt = 0;
		for (int i = 0; i < houseN; i++) {
			int hx = house[i].x;
			int hy = house[i].y;
			int d = int(abs(hx - x) + abs(hy - y));
			if (d <= l - 1) cnt++;
		}
		if (calccost(l) <= cnt*m)
			maxHouse = max(maxHouse, cnt);
	}
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf_s("%d %d", &n, &m);
		maxHouse = 0, houseN = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf_s("%d", &city[i][j]);
				if (city[i][j] == 1) house[houseN++] = { i,j };
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				countHouse(i, j);
			}
		}
		printf("#%d %d\n", tt, maxHouse);
	}
	return 0;
}
