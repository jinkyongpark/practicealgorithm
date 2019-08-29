//설계 5분~ 코딩 45분
// 구현은 20분에 됐으나 오름차순인것을 보지못해 시간소비.. .
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
const int MAX = 100;
char str[MAX];
char part[MAX];
vector<int> ansLst;
int testCase;
int n, k;
int l;
void hextoten(char part[]) {
	int mul = 1;
	int total = 0;
	int convertPart[MAX];
	for (int i = 0; i < l; i++) {
		if (part[i] >= 'A' && part[i] <= 'F')
			convertPart[i] = int(part[i]) - 55;
		else
			convertPart[i] = int(part[i]) - 48;
	}
	for (int i = l - 1; i >= 0; i--) {
		total += (convertPart[i] * mul);
		mul = mul * 16;
	}
	ansLst.push_back( total);
}
int main() {
	scanf("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf("%d %d", &n, &k);
		scanf("%s", str,MAX);
		l = n / 4;
		for (int front = 0; front < n; front++) {
			
			int p = front;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < l; j++) {
					int idx = (p + j) % n;
					part[j] = str[idx]; 
				}
				hextoten(part);
				p = (p + l) % n;
			}
		}
		sort(ansLst.begin(), ansLst.end(),greater<int>());
		int cnt = 1;
		int tmp = ansLst[0];
		int size = ansLst.size();
		for (int i = 1; i < size; i++) {
			if (cnt == k) {
				printf("#%d %d\n", tt, tmp );
				break;
			}
			if (ansLst[i] != tmp) cnt++;
			tmp = ansLst[i];
		}
		ansLst.clear();
	}
	return 0;
}