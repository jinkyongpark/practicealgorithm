#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int Max = 105;
int arr[Max][Max]={0,};
int checknum[Max] ={0,};
int maxr=3,maxc=3;
struct cmp{
	bool operator()(pair<int,int> a,pair<int,int> b){
		if(a.first!=b.first) return a.first>=b.first;
		else return a.second>=b.second;
	}
};
priority_queue <pair<int,int>,vector<pair<int,int>>,cmp> numlst; // count, num

int R,C,k;
int main(){
	cin>>R>>C>>k;
	for(int i =1;i<=3;i++)
		for(int j=1;j<=3;j++)
			cin>> arr[i][j];
	
	for(int t =0;t<=100;t++){
		if(t==52) cout<<"-----------------------------------------"<<endl;
		for(int i =1;i<=10;i++){
			for(int j=1;j<=10;j++){
				cout<< arr[i][j]<<" ";
			}
			cout<<endl;
		}
		if(arr[R][C]==k){
			cout <<t;
			return 0;
		}
		
		if(maxr>=maxc){
			for(int r=1;r<=maxr;r++){
				//갯수세기
				for(int c=1;c<=maxc;c++){
					if(arr[r][c] ==0) continue;
					checknum[arr[r][c]]++;	
				}
				//priority queue에넣기
				for(int i =1;i<=100;i++){
					if(checknum[i]==0) continue;
					numlst.push(make_pair(checknum[i],i));
					//cout <<i<<"의갯수:"<<checknum[i]<<endl;
					checknum[i] = 0;
				}
				//배열 채우기
				int c = 1;
				while(!numlst.empty()){
					if(c>100) break;
					arr[r][c] = numlst.top().second;
					c++;
					if(c>100) break;
					arr[r][c] = numlst.top().first;
					numlst.pop();
					c++;
				}
				if(maxc < c-1)
					maxc = c-1;
				while(!numlst.empty())
					numlst.pop();
				while(c<=100){
					arr[r][c] = 0;
					c++;
				}
			}
		}
		else{
			for(int c=1;c<=maxc;c++){
				//1.갯수세기
				for(int r=1;r<=maxr;r++){
					
					if(arr[r][c] ==0) continue;
					checknum[arr[r][c]]++;
				}
				//2.priority queue에넣기
				for(int i =1;i<=100;i++){
					if(checknum[i]==0) continue;
					numlst.push(make_pair(checknum[i],i));
					//cout <<i<<"의갯수:"<<checknum[i]<<endl;
					checknum[i] = 0;
				}
				//3.배열 채우기
				int r = 1;
				while(!numlst.empty()){
					if(r>100) break;
					arr[r][c] = numlst.top().second;
					r++;
					if(r>100) break;
					arr[r][c] = numlst.top().first;
					numlst.pop();
					r++;
				}
				if(maxr<r-1)
					maxr = r-1;
				while(!numlst.empty())
					numlst.pop();
				while(r<=100){
					arr[r][c] = 0;
					r++;
				}
			}
		}
	}
	cout<<-1;
	return 0;
}
