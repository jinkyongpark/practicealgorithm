#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int R,C,M;
const int Max = 110;
struct Shark{
	int v,d,w;//속력,방향,크기
};
struct PI{
	int r,c;
};
int d[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
vector<Shark> shark[Max][Max];

int main(){
	cin >>R>>C>>M;
	int ans = 0;
	for(int i=0;i<M;i++){
		int r,c,s,d,z;
		cin>>r>>c>>s>>d>>z;
		shark[r][c].push_back(Shark{s,d-1,z});
	}
	
	for(int cc=1;cc<=C;cc++){
		//1. catch fish
		for(int rr=1;rr<=R;rr++){
			if(!shark[rr][cc].size())continue;
			ans += shark[rr][cc][0].w;
			shark[rr][cc].clear();
			break;
		}
		
		//2. move fish
		//2-1. shark정보 저장
		queue<pair<Shark,PI>> q;
		for(int r = 1; r<=R;r++){
			for(int c = 1; c<=C; c++){
				if(!shark[r][c].size()) continue;
				q.push(make_pair(shark[r][c][0],PI{r,c}));
				shark[r][c].clear();
			}
		}
		//2-2. 이동
		while(!q.empty()){
			int r = q.front().second.r;
			int c = q.front().second.c;
			int vv = q.front().first.v;
			int dd = q.front().first.d;
			int ww = q.front().first.w;
			q.pop();
			
			//2-2-1. 이동할 위치 정하기
			for(int i = 0; i < vv; i++){
				int next;
				if(dd==1 || dd==0){ //행이동
					next = r + d[dd][0];
					if(next<=0 || next>R) 
						dd = 1 - dd;
					r =  r + d[dd][0];
				}
				else{//열이동
					next = c + d[dd][1];
					if(next<=0 || next>C)
						dd = 5 - dd;
					c = c + d[dd][1];
				}
			}
			
			//2-2-2. 이동할 위치에 상어가 있는지 확인
			//if(!shark[r][c].empty()) 면틀림
			if(!shark[r][c].size())
				shark[r][c].push_back(Shark{vv,dd,ww});
			else{
				if(ww > shark[r][c][0].w){
					shark[r][c].clear();
					shark[r][c].push_back(Shark{vv,dd,ww});
				}  
			}
		}
		
	}
	cout <<ans;
	return 0;
}