#include<iostream>
#include<queue>
using namespace std;
const int MAX = 110;
struct info{int a,b;};
queue<info> route;
queue<info> snake; //snake가있는좌표목록
int board[MAX][MAX]={0,};//1이면사과, 2면 뱀
int n,k,l;
int dir; //방향
int sr,sc;
int d[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
int dummy(){
	sr = 1, sc = 1, dir = 0;
	board[sr][sc] = 2;
	snake.push(info{sr,sc});
	int t;
	for(t=1;1;t++){
		sr += d[dir][0], sc += d[dir][1];
		if(sr<1 || sr>n || sc < 1 || sc>n ) break;
		if(board[sr][sc] == 0){ //꼬리가위치한칸비움
			int r = snake.front().a, c = snake.front().b;
			board[r][c] = 0;
			snake.pop();
			
			snake.push(info{sr,sc});
			board[sr][sc] = 2;
		}
		else if(board[sr][sc] == 1){ //사과가있을 때
			snake.push(info{sr,sc});
			board[sr][sc] = 2;
		}
		else if(board[sr][sc] == 2) break; //몸과부딪힘
		
		//이동 후 회전
		if(t == route.front().a){
			if(route.front().b==0)dir = dir==0? 3 : dir-1;
			else dir = (dir+1)%4;
			route.pop();
		}
	}
	return t;
}
int main(){
	cin>>n>>k;
	for(int i =0;i<k;i++)	{
		int r,c;
		cin>>r>>c;
		board[r][c] = 1;
	}
	cin>>l;
	for(int i=0;i<l;i++) {
		int t;
		char dir;
		cin>>t>>dir;
		if(dir=='L') route.push(info{t,0});
		else route.push(info{t,1});
	}
	cout<<dummy();
	return 0;
}
