//undirected weight graph에서 다익스트라알고리즘을 구현하였다.

#include <iostream>
#include <vector>
using namespace std;
const int MAX = 100;
int n;//노드 갯수
int distFromstart[MAX]; //출발점으로부터의 거리 저장
bool check[MAX]; // 확정된 노드인지
vector<int> g[MAX]; // i번째 노드와 연결된 모든 노드를 저장
vector<int> weight[MAX];//i번째 노드와 연결된 노드 사이의 거리를 저장
void dijkstra(int start){
	//init
	for(int i =0;i<n;i++){
		distFromstart[i] = 987987987; //무한대로 설정
	}
	distFromstart[start] = 0;
	
	//모든 노드를 확정할때까지 반복, 한번 loop를 돌때마다 한개가 확정된다.
	for(int i = 0; i < n; i++){
		
		//Loop1
		int minval = 987987987, minidx= -1;
		for(int j = 0 ; j < n ; j++){
			if(minval>distFromstart[j]){
				minval = distFromstart;
				minidx = j
			}
		}
		check[minidx] = true;
		
		//Loop2
		for(int j = 0; j< int(g[minidx].size()) ; j++){
			int node = g[minidx][j]; 
			int cost = cost[minidx][j];
			// 현재까지 업데이트된 시작점에서 j까지 거리 > minidx를 지나서 j까지 가는 거리( start~minidx + minidx~j)
			if(table[j] > table[minidx] + cost){
				table[j] = table[minidx] + cost;
			}
		}
	}
	
}

int main(){
	cin >> n;
	for(int i=0;i<n;i++){
		int s,d,w;
		cin>>s>>d>>w;
		g[s].push_back(d);
		g[d].push_back(s);
		weight[s].push_back(w);
		weight[d].push_back(w);
	}
	
	int start = 0;
	diklstra(start);
	return 0;
}
