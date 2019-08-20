#include <iostream>
using namespace std;
const int MAX = 10;
char wheel[MAX][MAX];
int k;
void rotatewheel(int wn, int d){
	if(d==1){
		int tmp = wheel[wn][7];
		for(int i = 7 ; i>0;i--)
			wheel[wn][i] = wheel[wn][i-1];
		wheel[wn][0] = tmp;
	}
	else{
		int tmp = wheel[wn][0];
		for(int i =0; i<7;i++)
			wheel[wn][i] = wheel[wn][i+1];
		wheel[wn][7] = tmp;
	}
}
void getleft(int wn, int d){
	if(wn-1>=0){
		if(wheel[wn][6] != wheel[wn-1][2])
			getleft(wn-1,-d);
	}
	rotatewheel(wn,d);
}
void getright(int wn, int d){
	if(wn+1<4){
		if(wheel[wn][2] != wheel[wn+1][6])
			getright(wn+1,-d);
	}
	rotatewheel(wn,d);
}
void rotate(int wn, int d){
	if(wn-1>=0){
		if(wheel[wn][6] != wheel[wn-1][2])
			getleft(wn-1,-d);
	}
	if(wn+1<4){
		if(wheel[wn][2] != wheel[wn+1][6])
			getright(wn+1,-d);
	}
	rotatewheel(wn,d);
}

int main(){
	for(int i =0;i<4;i++) cin>>wheel[i];
	cin>>k;
	for(int i =0;i<k;i++){
		int n, d;
		cin>>n>>d;
		rotate(n-1,d);
	}
	int ans = 0;
	if(wheel[0][0]=='1') ans+= 1;
	if(wheel[1][0]=='1') ans+= 2;
	if(wheel[2][0]=='1') ans+= 4;
	if(wheel[3][0]=='1') ans+= 8;
	cout<< ans;
	return 0;
}
