#include <cstdio>
#include <algorithm>
using namespace std;
const int arrMAX = 25, dessertMax = 110;
int dessert[arrMAX][arrMAX];
bool visit[arrMAX][arrMAX];
bool check[dessertMax];
int testCase;
int n;
int mymax = -1;
bool pathCheck(int w, int h, int x, int y) { //순서대로 이동
	for (int i = 0; i < w; i++) {
		x++, y--;
		if (x>=n || y<0) return false;
		if (!check[dessert[x][y]])
			check[dessert[x][y]] = true;
		else
			return false;
	}
	for (int i = 0; i < h; i++) {
		x++, y++;
		if (x >= n || y >= n) return false;
		if (!check[dessert[x][y]]) {
			check[dessert[x][y]] = true;
		}
		else
			return false;
	}
	for (int i = 0; i < w; i++) {
		x--, y++;
		if (x <0  || y >= n) return false;
		if (!check[dessert[x][y]]) {
			check[dessert[x][y]] = true;
		}
		else
			return false;
	}
	for (int i = 0; i < h; i++) {
		x--, y--;
		if (x <0  || y <0) return false;
		if (!check[dessert[x][y]]) {
			check[dessert[x][y]] = true;
		}
		else
			return false;
	}
	return true;
}
int main() {
	scanf_s("%d", &testCase);
	for (int i = 0; i < testCase; i++) {
		scanf_s("%d", &n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf_s("%d", &dessert[i][j]);
		for (int x = 0; x <= n; x++) {
			for (int y = 0; y <= n; y++) {
				//visit[x][y] = true;
				//check[dessert[x][y]] = true;
				for(int w = 1; w <= n; w++) { //증가량
					for (int h = 1; h <= n; h++) {
						if (pathCheck(w, h, x, y))
							mymax = max(mymax, (w + h) * 2);
						//if (mymax == 6)
							//printf("%d %d\n", x, y);
						for (int i = 0; i < 101; i++)
							check[i] = false;
					}
				}
			}
		}
		printf("#%d %d\n", i + 1, mymax);
		mymax = -1;
	}
	return 0;
}
