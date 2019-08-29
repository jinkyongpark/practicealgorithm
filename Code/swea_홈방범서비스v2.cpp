#include <iostream>
#include<algorithm>
using namespace std;
const int MAX = 30;
int T, d,w,k,ans;
int film[MAX][MAX], tmpfilm[MAX][MAX];
pair<int,int> cell[MAX];
int drugcnt;
void performanceCheck() {
	for (int r = 0; r < d; r++)
		for (int c = 0; c < w; c++)
			tmpfilm[r][c] = film[r][c];
	for (int i = 0; i < drugcnt; i++) {
		int rownum = cell[i].first, medicine = cell[i].second;
		for (int c = 0; c < w; c++)
			tmpfilm[rownum][c] = medicine;
	}
	for (int c = 0; c < w; c++) {
		int point = tmpfilm[0][c];
		int cnt = 1;
		for (int r = 1; r < d; r++) {
			if (point == tmpfilm[r][c]) {
				cnt++;
				if (cnt >= k) break;
			}
			else {
				point = tmpfilm[r][c];
				cnt = 1;
			}
		}
		if (cnt < k) return;
	}
	ans = min(ans, drugcnt);
}
void insertDrug(int idx,int sidx ) {
	if (ans < k) return;
	if (idx >= drugcnt) {
		performanceCheck();
		return;
	}
	for (int i = sidx; i < d; i++) {
		cell[idx] = make_pair(i,0); //이렇게 체크말고 약 투입하고 RECOVER하는게 더 좋다.
		insertDrug(idx + 1, i + 1);
		cell[idx] = make_pair(i,1);
		insertDrug(idx + 1, i + 1);
	}
}
int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> d>>w>>k;
		for (int r = 0; r < d; r++)
			for (int c = 0; c < w; c++)
				cin >> film[r][c];
		ans = k;
		for (drugcnt= 0; drugcnt < k; drugcnt++) {
			insertDrug(0,0);
			if (ans < k) break;
		}
		cout << "#" << t << " " << ans << endl;
	}
	return 0;
}
