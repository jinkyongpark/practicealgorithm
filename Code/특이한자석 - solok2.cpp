//2019-04-10 10분
#include <cstdio> 
using namespace std;
const int MAX = 110; 
int testCase,k;
int magnet[5][8];
void rotate(int mN, int d) {
	//1 시계방향
	if (d == 1) {
		int tmp = magnet[mN][7];
		for (int i = 7; i >= 1; i--) 
			magnet[mN][i] = magnet[mN][i - 1];
		magnet[mN][0] = tmp;
	}
	else {
		int tmp = magnet[mN][0];
		for (int i = 0; i < 7; i++) 
			magnet[mN][i] = magnet[mN][i + 1];
		magnet[mN][7] = tmp;
	}
}
void getLeft(int x,int dd) {
	if (x > 1) 
		if (magnet[x][6] != magnet[x - 1][2])
			getLeft(x - 1, dd*-1);
	rotate(x, dd);
}
void getRight(int x, int dd) {
	if (x < 4) 
		if (magnet[x][2] != magnet[x + 1][6])
			getRight(x + 1, dd*-1);
	rotate(x, dd);
}
int main() {
	scanf("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf("%d", &k);
		for (int i =1; i <= 4; i++) 
			for (int j = 0; j < 8; j++)
				scanf("%d", &magnet[i][j]);
		for (int i = 0; i < k; i++) {
			int magN, d;
			scanf("%d %d", &magN, &d);
			getLeft(magN,d);
			rotate(magN, d*-1);
			getRight(magN, d);
		}
		int ans = 0;
		if (magnet[1][0] == 1) ans += 1;
		if (magnet[2][0] == 1) ans += 2;
		if (magnet[3][0] == 1) ans += 4;
		if (magnet[4][0] == 1) ans += 8;
		printf("#%d %d\n", tt, ans);
	}
	return 0;
}