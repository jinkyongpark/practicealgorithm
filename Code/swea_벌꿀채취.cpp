#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
const int MAX = 15;
struct pi {
	int r, sc, ec;
	int profit;
};
int honey[MAX][MAX];
int honeycase[2];
bool check[MAX][MAX];
pi hlst[MAX*MAX];
int testcase, n, m, C, maxans;
int  hn, tmpr, maxselectnum, tmpsum, tpowsum;

void calcProfit(int a, int sc) {
	//m개의 연속된 꿀통조합에서 채취할수있는 양 계산
	if (a >= maxselectnum) {
		hlst[hn].profit = max(hlst[hn].profit, tpowsum);
		return;
	}
	for (int c = sc; c <= hlst[hn].ec; c++ ) {
		int s = pow(honey[tmpr][c],2);

		tmpsum += honey[tmpr][c];
		tpowsum += s;
		if (tmpsum <= C)
			calcProfit(a + 1,  c + 1);
		tpowsum -= s;
		tmpsum -= honey[tmpr][c];
	}

}

void selectHoney(int a, int sidx) {
	if (a >= 2) {
		maxans = max(maxans, hlst[honeycase[0]].profit + hlst[honeycase[1]].profit);
		return;
	}

	for (int i = sidx; i<hn; i++) {
		bool flag = false;
		int r = hlst[i].r;
		for (int c = hlst[i].sc; c <= hlst[i].ec; c++) {
			if (check[r][c]) { //이미 check되었던거 -> 꿀통조합끼리 겹쳐짐
				for (int tc = hlst[i].sc; tc<c; tc++)
					check[r][tc] = false; //지금까지한거원래대로
				flag = true;
				break;
			}
			else check[r][c] = true;
		}
		if (flag) continue;
		honeycase[a] = i;
		selectHoney(a + 1, i + 1);
		for (int c = hlst[i].sc; c <= hlst[i].ec; c++)
			check[r][c] = false;
	}
}

int main() {

	cin >> testcase;
	for (int tt = 1; tt <= testcase; tt++) {
		hn = 0;
		maxans = 0;
		cin >> n >> m >> C;
		for (int i = 1; i <= n; i++)for (int j = 1; j <= n; j++)
			cin >> honey[i][j];

		//꿀통조합만들기
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n - m + 1; j++) {
				hlst[hn] = pi{ i , j, j + m - 1, 0 };
				tmpr = hlst[hn].r;
				for (int i = m; i >= 1; i--) {
					maxselectnum = i; //연속된꿀통조합에서 최대로 선택할 수 있는 갯수
					tmpsum = 0, tpowsum = 0;
					calcProfit(0, hlst[hn].sc);
				}
				hn++;
			}
		}
		selectHoney(0, 0);
		cout << "#" << tt << " " << maxans << endl;

	}
	return 0;
}
