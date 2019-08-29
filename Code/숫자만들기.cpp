#include <iostream>
#include<algorithm>
using namespace std;
const int MAX = 20;
int T,n;
int op[MAX], num[MAX];
bool check[MAX];
int minans, maxans, ans;
void dfs(int idx) {
	if (idx >= n - 1) {
		//cout << ans << endl;
		minans = min(minans, ans);
		maxans = max(maxans, ans);
		return;
	}
	for (int i = 0; i <4; i++){
		if (!op[i]) continue;
		//2번째 속도향상 point : 원래처럼 배열을 만들어놓고 하는 것이 아니라 op[i]의 개수를 가지고 백트래킹
		//이렇게 하면 1a 1b 2 3과 1b 1a 2 3을 구분하지 않고 한번만 계산
		int tmp = ans;
		op[i]--;
		switch (i) {		//1번째 속도향상 point : oplst가 결정되었을 때 계산을 수행하는 것보다 계산을 수행하면서 백트래킹하는 것이 계산수를 훨씬 줄일 수 있다.
		case 0:
			ans += num[idx + 1];
			break;
		case 1:
			ans -= num[idx + 1];
			break;
		case 2:
			ans *= num[idx + 1];
			break;
		case 3:
			ans /= num[idx + 1];
			break;
		}
		dfs(idx + 1);
		ans = tmp;//recovery
		op[i]++;
	}
}
int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n;
		int idx = 0;
		minans = 978987987, maxans = -987987978; //값이 -가 나올수있으므로 max,min값을 적절히 초기화
		for (int i = 0; i < 4; i++) 
			cin >> op[i]; 
		
		for (int i = 0; i < n; i++) cin >> num[i];
		ans = num[0];
		dfs(0);
		cout << "#" << t << " " <<maxans-minans  << endl;
	}
	return 0;
}




/**********틀린버전********/
#include <iostream>
#include<algorithm>
using namespace std;
const int MAX = 20;
int T,n;
int op[MAX], oplst[MAX];
bool check[MAX];
int num[MAX];
int minans, maxans;
int ans;
void dfs(int idx) {
	// oplst의 idx번째에 연산자를 저장, 저장된 연산자는 check
	// idx가 n-1이 될때까지 진행
	if (idx >= n - 1) {
		//cout << ans << endl;
		minans = min(minans, ans);
		maxans = max(maxans, ans);
		return;
	}
	for (int i = 0; i < n - 1; i++){
		if (check[i]) continue;
		int tmp = ans;
		check[i] = true;
		switch (op[i]) {
		case 0:
			ans += num[idx + 1];
			break;
		case 1:
			ans -= num[idx + 1];
			break;
		case 2:
			ans *= num[idx + 1];
			break;
		case 3:
			ans /= num[idx + 1];
			break;
		}
		dfs(idx + 1);
		check[i] = false;
		ans = tmp;//recovery
	}
}
int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n;
		int idx = 0;
		minans = 978987987, maxans = -987987978;
		for (int i = 0; i < 4; i++) {
			int cnt;
			cin >> cnt;
			for (int j = 0; j < cnt; j++) op[idx++] = i; 
		}
		for (int i = 0; i < n; i++) cin >> num[i];
		ans = num[0];
		dfs(0);
		cout << "#" << t << " " <<maxans-minans  << endl;
	}
	return 0;
}