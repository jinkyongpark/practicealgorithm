#include <iostream>
#include<algorithm>
#include<cmath>
#include <vector>
using namespace std;
const int MAX = 20;
int T, n;
int food[MAX][MAX];
bool check[MAX]; //team 구분
int minans;
vector<int> team1, team2;

void calcSynergy() {
	int s1 = 0, s2 = 0;
	for (int i : team1) 
		for (int j : team1) 
			s1 += food[i][j];
	
	for (int i : team2) 
		for (int j : team2) 
			s2 += food[i][j];
	
	minans = min(minans, abs(s1 - s2));
}
void divideteam(int idx, int start) {
	if (idx >= n / 2) {
		for (int i = 1; i <= n; i++) 
			if (!check[i]) team2.push_back(i);
		calcSynergy();
		team2.clear();
		return;
	}
	for (int i = start; i <= n; i++) {
		if (check[i]) continue;
		check[i] = true;
		team1.push_back(i);
		divideteam(idx + 1, i + 1);
		team1.pop_back();
		check[i] = false;
	}
}
int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		minans = 987987987;
		cin >> n;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> food[i][j];
		divideteam(0, 1);
		cout << "#" << t << " " << minans << endl;
	}
	return 0;
}