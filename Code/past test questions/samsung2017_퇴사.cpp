#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 20;
int t[MAX],cost[MAX];
int n, maxans = -987987987;
vector<int> benefit;
bool check[MAX], impossible[MAX];
void countMaxBenefit(int startday){
	if(startday>n){
		int s = 0;
		for(int i=0;i<benefit.size();i++)
			s += benefit[i];
		maxans = max(maxans, s);
		return ;
	}
	for(int i = startday;i<=n;i++){
		if(check[i]) continue;
		if(impossible[i]){
			countMaxBenefit(i+1);
		}
		else{
		int nextday = i;
		for(;nextday<i+t[i]; nextday++) check[nextday] = true;
			benefit.push_back(cost[i]);
			countMaxBenefit(nextday);
			benefit.pop_back();
			for(int j = i ; j<nextday; j++) check[j] = false;
		}
	}
}
int main(){
	cin>>n;
	for(int day =1;day<=n;day++){
		cin>>t[day]>>cost[day];
		if(t[day]+day-1>n) impossible[day] = true;
	}
	countMaxBenefit(1);
	cout<<maxans;
	return 0;
}
