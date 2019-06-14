#include <string>
#include <vector>
#include <algorithm>
#include<iostream>

using namespace std;
bool desc(pair<double,int> a, pair<double,int> b) {
	if(a.first==b.first)
        return a.second<b.second;
    else
        return a.first > b.first;
}

vector<int> solution(int N, vector<int> stages) {
	vector<pair<double, int>> failure; // 실패율,stage
	vector<int> answer;
	double state[503] = { 0.0, }; //i번 stage에 머무르고 있는 사용자 수
	double total[503] = { 0.0, }; //stage에 도달한 player수 
	
    int userN = stages.size();
	for (int i = 0; i<userN; i++) 
		state[stages[i]]++;
	
	if (state[N + 1]!=0.0) total[N] = state[N] + state[N+1]; // N+1번째 stage에 값이 있다면
	else total[N] = state[N];

	for (int i = N - 1; i >= 1; i--) //stage에 도달한 player수 = 현재 stage player 수 + 다음 stage에 도달한 player
		total[i] = state[i] + total[i + 1];
        
	for (int i = 1; i <= N; i++) {
		if (!state[i]) 
            failure.push_back(make_pair(0.0, i));
		else {
			double p = state[i] / total[i];
			failure.push_back(make_pair(p, i));
		}
	}
	sort(failure.begin(), failure.end(), desc);
	for (int i = 0; i < N; i++) 
		answer.push_back(failure[i].second);

	return answer;
}
