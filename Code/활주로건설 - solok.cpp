//2019-04-10 25분
#include <cstdio> 
#include <math.h>
#include <queue>
#include <vector>
#include <functional>
using namespace std;
const int MAX=25; 
int testCase;
int area[MAX][MAX];
bool check[MAX][MAX];//경사로를 세운 곳은 체크해서 경사로를 한번 더세우는것을 방지한다.
int n, l;
bool dfs1(int row, int col) {
	if (row >= n-1) return true;
	if (area[row][col] == area[row + 1][col]) {
		return dfs1(row + 1, col);
	}
	//내리막
	if (area[row][col] == area[row + 1][col]+1) {
		if (row + l >= n) return false;
		for (int i = row + 1; i <= row +l; i++) {
			if (area[row][col] != area[i][col]+1) return false;
			check[i][col] = true;//경사로 세움
		}
		return dfs1(row + l, col);
	}
	//오르막
	else if (area[row][col] + 1 == area[row + 1][col]) {
		if (row - l+1 < 0) return false;
		for (int i = row; i >= row - l + 1; i--) {
			if (check[i][col]) return false;
			if (area[i][col] + 1 != area[row + 1][col]) return false;
			check[i][col] = true;;
		}
		return dfs1(row + 1, col);
	}
	return false;
}
bool dfs2(int row,int col) {
	if (col >= n - 1) return true;
	if (area[row][col] == area[row][col + 1]) {
		return dfs2(row, col+1);
	}
	//내리막
	if (area[row][col] == area[row][col + 1] + 1) {
		if (col + l >= n) return false;
		for (int i = col + 1; i <= col + l; i++) {
			if (area[row][col] != area[row][i] + 1) return false;
			check[row][i] = true;//경사로 세움
		}
		return dfs2(row, col + l);
	}
	//오르막
	else if (area[row][col] + 1 == area[row][col + 1]) {
		if (col - l + 1 < 0) return false;
		for (int i = col; i >= col - l + 1; i--) {
			if (check[row][i]) return false;
			if (area[row][i] + 1 != area[row][col + 1]) return false;
			check[row][i] = true;;
		}
		return dfs2(row, col + 1);
	}
	return false;
}
int main() {
	scanf_s("%d", &testCase);
	for (int tt = 1; tt <= testCase; tt++) {
		scanf_s("%d %d", &n,&l);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf_s("%d", &area[i][j]);
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				check[i][j] = 0;
			}
		}
		//세로 dfs
		for (int col = 0; col < n; col++) {
			if (dfs1(0, col)) ans++;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				check[i][j] = 0;
			}
		}
		//가로 dfs
		for (int row = 0; row < n; row++) {
			if (dfs2(row, 0)) ans++;
		}
		printf("#%d %d\n", tt,ans);
	}
	
	return 0;
}