#include<iostream>
#include <queue>
using namespace std;
const int MAX = 12;
char gameboard[MAX][MAX];
bool check[MAX][MAX][MAX][MAX];
int d[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int n,m;
struct ball{
	int redr, redc, bluer, bluec;
	int moven;
};
int Rr,Rc,Br,Bc,hr,hc, ans;
bool flag = false;
int nrr, nrc, nbr, nbc;
void movingball(int rr, int rc, int br, int bc, int dir){
	//move red ball
	nrr = rr, nrc = rc, nbr= br, nbc = bc;

	while(1){
		nrr += d[dir][0], nrc += d[dir][1];
		if(gameboard[nrr][nrc]== 'O') break;		
		else if(gameboard[nrr][nrc] =='#'){
			nrr -= d[dir][0], nrc -= d[dir][1];
			break;
		}
	}
	//move blue ball
	while(1){
		nbr += d[dir][0], nbc += d[dir][1];
		if(gameboard[nbr][nbc] == 'O') break;
		else if(gameboard[nbr][nbc] == '#'){
			nbr -= d[dir][0], nbc -= d[dir][1];
			break; 
		}
	}
}
int game(){
	queue<ball> q;
	q.push(ball{Rr,Rc,Br,Bc,0});
	check[Rr][Rc][Br][Bc] = true;
	while(!q.empty()){
		int redr = q.front().redr, redc = q.front().redc,
			bluer = q.front().bluer, bluec = q.front().bluec;
		int mn = q.front().moven;
		
		q.pop();
		if(mn>=10) continue;
		for(int i=0;i<4;i++){
			//move ball 
      movingball(redr,redc,bluer,bluec,i);
			
			if(check[nrr][nrc][nbr][nbc]) continue;
			//nb가 hall에 있는지
			if(nbr == hr && nbc == hc) continue;
			//둘다 변화가 없을 때
			if(nrr== redr && nrc == redc && nbr == bluer && nbc==bluec) continue;
			//nr이 hall에 있는지 확인
			if(nrr == hr && nrc == hc){
				flag = true;
				return mn+1;
			}
			
			//둘이 같을 때 위치조정
			if(nrr == nbr && nrc == nbc){
				if(i==0){
					if(redr<bluer)	nbr++;
					else nrr++;
				}	
				else if(i==1){
					if(redr<bluer) nrr--;
					else nbr--;
				}
				else if(i==2){
					if(redc<bluec) nbc++;
					else nrc++;
				}
				else if(i==3){
					if(redc<bluec) nrc--;
					else nbc--;
				}
			}
			
			check[nrr][nrc][nbr][nbc] = true;
			q.push(ball{nrr,nrc,nbr,nbc,mn+1});
		}
		if(flag) break;
	}
	return -1;
}
int main(){
	cin>>n>>m;
	for(int i =0;i<n;i++) cin>>gameboard[i];
	for(int i =0;i<n;i++){
		for(int j=0;j<m;j++){
			if(gameboard[i][j] =='R') Rr = i, Rc = j;
			else if(gameboard[i][j]== 'B') Br = i , Bc = j;
			else if(gameboard[i][j] == 'O') hr = i, hc = j;
		}
	}
	ans = game();
	cout<<ans;
	return 0;
}
