#include <iostream>
#include<algorithm>
using namespace std;
const int MAX = 13;
int T;
int month[MAX], threemonthlst[MAX], tidx, sumday, summonth,sumthree, totalprice;
int dayp, monthp, tmonthp, yearp;
bool usethree[MAX];
int tcheck[MAX] = { 0, };
void calcRemain(int idx) {
	if (idx > 12) {
		sumday = 0, summonth = 0;
		for (int i = 1; i <= 12; i++) {
			
			if (tcheck[i] == 1)
				sumday += month[i];
			else if (tcheck[i] == 2)
				summonth++;
		}
		totalprice = min(totalprice, sumday*dayp + summonth*monthp + sumthree*tmonthp);
		return;
	}
	if (month[idx]> 0 && tcheck[idx] != 3) {
		tcheck[idx] = 1;
		calcRemain(idx + 1);
		tcheck[idx] = 2;
		calcRemain(idx + 1);
		tcheck[idx] = 0;
	}
	else 
		calcRemain(idx + 1);
}
void calcThreeMonth(int idx) {
	if (idx >= tidx) {
		sumthree = 0;
		for (int i = 0; i < tidx; i++) {
			if (!usethree[i]) continue;
			int p = threemonthlst[i],
				n1 = p + 1 <= 12 ? p + 1 : 1,
				n2 = p + 2 <= 12 ? p + 2 : p - 12;
			tcheck[p] = 3, tcheck[n1] = 3, tcheck[n2] = 3;
			sumthree++;
		}
		calcRemain(1);
		for (int i = 1; i <= 12; i++) tcheck[i] = 0;
		return;
	}
	usethree[idx] = false;
	calcThreeMonth(idx + 1);
	usethree[idx] = true;
	calcThreeMonth(idx + 1);
}

int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> dayp >> monthp >> tmonthp >> yearp;
		sumday = 0, totalprice = yearp,tidx = 0,summonth=0;
		for (int i = 1; i <= 12; i++) 
			cin >> month[i];
		//3달연속인달 구하기
		for (int i = 1; i <= 12; i++) {
			if (month[i]) {
				int n1 = i + 1 <= 12 ? i + 1 : 1,
					n2 = i + 2 <= 12 ? i + 2 : i - 12;
				if(month[n1] &&  month[n2]) 
					threemonthlst[tidx++] = i;
			}
		}
		calcThreeMonth(0);
		cout << "#" << t << " " << totalprice << endl;
	}
	return 0;
}