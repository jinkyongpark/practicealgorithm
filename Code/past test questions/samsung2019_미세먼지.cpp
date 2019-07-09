#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int Max = 55;
int area[Max][Max], tmparea[Max][Max]={0,};
int R,C,T;
int d[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
vector <int > airclear;
int ar1,ar2;
void spreaddust(){
	for(int r=0;r<R;r++){
		for(int c=0;c<C;c++){
			if(area[r][c]<=0) continue;
			int spreadn = area[r][c]/5;
			int cnt = 0;
			for(int i =0;i<4;i++){
				
				int nextr = r +d[i][0];
				int nextc = c + d[i][1];
				
				if(nextr<0 || nextr>=R|| nextc<0 || nextc>=C || area[nextr][nextc] ==-1) continue;
				tmparea[nextr][nextc] += spreadn;
				cnt++;
			}
			tmparea[r][c] += (area[r][c] - (cnt*spreadn));
		}
	}
	for(int r=0;r<R;r++){
		for(int c=0;c<C;c++){
			if((r==ar1&& c==0) || (r==ar2&& c==0)) continue;
			area[r][c] = tmparea[r][c];
			tmparea[r][c] = 0;
		}
	}
}
void clearair(){
	for(int r = ar1-1 ;r > 0;r--){
		area[r][0] = area[r-1][0];
	}
	for(int c = 0 ; c < C-1;c++){
		area[0][c] = area[0][c+1];
	}
	for(int r = 0; r<= ar1-1;r++){
		area[r][C-1] = area[r+1][C-1];
	}
	for(int c = C-1; c>=2;c--){
		area[ar1][c] = area[ar1][c-1];
	}
	area[ar1][1] = 0;
	for(int r = ar2+1; r<R-1;r++){
		area[r][0] = area[r+1][0];
	}
	for(int c= 0; c<C-1;c++){
		area[R-1][c] = area[R-1][c+1];
	}
	for(int r = R-1 ; r>=ar2+1;r--){
		area[r][C-1] = area[r-1][C-1];
	}
	for(int c = C-1 ; c>=2;c--){
		area[ar2][c] = area[ar2][c-1];
	}
	area[ar2][1] = 0;
}
int main(){
	cin>>R>>C>>T;
	int ans =0;
	for(int i =0;i<R;i++){
		for(int j=0;j<C;j++){
			cin>>area[i][j];
			if(area[i][j]==-1){
				airclear.push_back(i);
			}
		}
	}
	ar1 = airclear[0], ar2 = airclear[1];
	
	for(int t=1;t<=T;t++){
		spreaddust();
		
		clearair();
		
	}
	for(int i =0;i<R;i++){
		for(int j=0;j<C;j++){
			ans += area[i][j];
		}
	}
	cout<<ans+2;
	return 0;
}