#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n,m,k;
const int Max = 15;
int d[8][2] ={{-1,0},{1,0},{0,-1},{0,1},{1,1},{1,-1},{-1,1},{-1,-1}};
struct AREA{
	int energy = 5;
	vector<int> tree;
};
AREA area[Max][Max];
int plusenergy[Max][Max];
void spring_summer(){
	for(int r=1;r<=n;r++){
		for(int c=1;c<=n;c++){
			if(!area[r][c].tree.size()) continue;
			sort(area[r][c].tree.begin(),area[r][c].tree.end());
			int energy = area[r][c].energy;
			int size = area[r][c].tree.size();
			int idx;
			for(idx =0;idx<size ;idx++){	
				if(energy>=area[r][c].tree[idx]){
					energy -= area[r][c].tree[idx]; //양분먹기
					area[r][c].tree[idx]++; //나이증가
				}
				else break;
			}
			area[r][c].energy = energy;
			for(int i = size-1;i>=idx;i--){ //끝에서부은죽은나무체크
				area[r][c].energy += area[r][c].tree[i]/2; //summer
				area[r][c].tree.pop_back();//죽음
			}
		}
	}
}
void fall(){
	for(int r=1;r<=n;r++){
		for(int c=1;c<=n;c++){
			if(!area[r][c].tree.size()) continue;
			int size = area[r][c].tree.size();
			for(int i =0;i<size;i++){
				if(area[r][c].tree[i]%5!=0) continue;
				for(int j = 0;j<8;j++){
					int nr = r + d[j][0], nc = c + d[j][1];
					if(nr<=0 || nr>n || nc<=0 || nc>n) continue;
					area[nr][nc].tree.push_back(1);
				}
			}
		}
	}
}
void winter(){
	for(int r=1;r<=n;r++)
		for(int c=1;c<=n;c++)
			area[r][c].energy += plusenergy[r][c];
}
int main(){
	cin >>n>>m>>k;
	for(int r=1;r<=n;r++)
		for(int c=1;c<=n;c++)
			cin>>plusenergy[r][c];
	for(int i=0;i<m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		area[x][y].tree.push_back(z);
	}
	for(int i =0;i<k;i++){
		spring_summer();
		fall();
		winter();
	}
	int ans = 0;
	for(int r=1;r<=n;r++)
		for(int c=1;c<=n;c++)
			ans += area[r][c].tree.size();
	cout <<ans;
	return 0;
}