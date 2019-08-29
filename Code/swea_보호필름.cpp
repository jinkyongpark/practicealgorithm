#include <cstdio> //33분
#include <algorithm>
using namespace std;
const int MAX = 30;
int testCase;
int d, w, k;
int film[MAX][MAX];
int tmp[MAX][MAX];
void insertmedicine(int row, int ab) {
	int medicine;
	if (ab == 1) medicine = 0;
	else medicine = 1;
	for (int i = 0; i < w; i++)
		film[row][i] = medicine;
}
void recover(int row) {
	for (int i = 0; i < w; i++)
		film[row][i] = tmp[row][i];
}
bool checkThree(int col) {
	int startN = film[0][col];
	int cnt = 1;
	for (int i = 1; i < d; i++) {
		if (startN == film[i][col]) cnt++;
		else {
			startN = film[i][col];
			cnt = 1;
		}
		if (cnt >= k) return true;
	}
	return false;
}
bool dfs(int idx, int kN) {
	if (idx >= d) {
		if (kN != 0) return false;
		for (int i = 0; i < w; i++) {
			if (!checkThree(i))
				return false;
		}
		return true;
	}
	else {
		if (dfs(idx + 1, kN)) return true;;
		
		if (kN > 0) {
			insertmedicine(idx, 1);
			if (dfs(idx + 1, kN - 1)) {
				recover(idx);
				return true;
			}
			recover(idx);


			insertmedicine(idx, 2);
			if (dfs(idx + 1, kN - 1)) {
				recover(idx);
				return true;
			}
			recover(idx);

		}
	}
	return false;
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf_s("%d %d %d", &d,&w,&k);
		
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++) {
				scanf_s("%d", &film[i][j]); //a = 0 b =1
				tmp[i][j] = film[i][j];
			}
		}
		int ans;
		for (ans = 0; ans <= d; ans++) {
			//약을 i번 주입해서 true나오면 그만
			if (dfs(0, ans)) {
				break;
			}
		}
		printf("#%d %d\n", tt, ans);
	}
	return 0;
}
