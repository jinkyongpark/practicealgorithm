#include <iostream>
#include<algorithm>
#include <queue>
using namespace std;
int n;
const int MAX = 25;
int gameboard[MAX][MAX],tmpboard[MAX][MAX];
int order[5], maxans = -987987987;
queue<int> q;
void move(int dir){
	int idx;
	if(dir==0 ){
		for(int c = 0 ; c<n ;c++){
			idx = 0;
			for(int r = 0; r<n ;r++){
				if(gameboard[r][c]) q.push(gameboard[r][c]);
				gameboard[r][c] =0;
			}
			while(!q.empty()){
				int data = q.front();
				q.pop();
				if(gameboard[idx][c] == 0)	gameboard[idx][c] = data;
				else if(gameboard[idx][c] == data)	gameboard[idx++][c] *=2;
				else	gameboard[++idx][c] = data; 
				
			}
		}
	}
	else if(dir == 1){
		for(int c = 0 ; c<n ; c++){
			idx = n-1;
			for(int r = n-1; r>=0; r--){
				if(gameboard[r][c]) q.push(gameboard[r][c]);
				gameboard[r][c] = 0;
			}
			while(!q.empty()){
				int data = q.front();
				q.pop();
				if(gameboard[idx][c]==0) gameboard[idx][c] = data;
				else if(gameboard[idx][c] == data) gameboard[idx--][c] *=2;
				else gameboard[--idx][c] = data;
			}
		}
	}
	else if(dir==2){
		for(int r = 0 ; r<n ;r++){
			idx = 0;
			for(int c = 0; c<n ;c++){
				if(gameboard[r][c]) q.push(gameboard[r][c]);
				gameboard[r][c] =0;
			}
			while(!q.empty()){
				int data = q.front();
				q.pop();
				if(gameboard[r][idx] == 0)		gameboard[r][idx] = data;
				else if(gameboard[r][idx] == data) gameboard[r][idx++] *=2;
				else	gameboard[r][++idx] = data; 
				
			}
		}
	}
	else {
		for(int r = 0 ; r<n ; r++){
			idx = n-1;
			for(int c = n-1; c>=0; c--){
				if(gameboard[r][c]) q.push(gameboard[r][c]);
				gameboard[r][c] = 0;
			}
			while(!q.empty()){
				int data = q.front();
				q.pop();
				if(gameboard[r][idx]==0) gameboard[r][idx] = data;
				else if(gameboard[r][idx] == data) gameboard[r][idx--] *=2;
				else gameboard[r][--idx] = data;
			}
		}
	}
}
void setdirection(int idx){
	if(idx>=5){
		for(int i=0;i<5;i++)	move(order[i]);
		for(int i =0;i<n;i++){
			for(int j=0;j<n;j++){
				maxans = max(maxans, gameboard[i][j]);
				gameboard[i][j] = tmpboard[i][j];
			}
		}
		return ;
	}
	for(int i =0;i<4;i++){
		order[idx] = i;
		setdirection(idx+1);
	}
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++){
			 cin>>gameboard[i][j];
			 tmpboard[i][j] = gameboard[i][j];
		}
	}
	setdirection(0);
	cout<<maxans;
	return 0;
}
