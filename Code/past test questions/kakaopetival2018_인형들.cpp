#include<iostream>
#include<vector>
#include<cstdio>
#include <cmath>
using namespace std;
typedef long double floata;
vector<int> nums;
int n,k;
floata avg(int start, int end){
	floata s = 0;
	for(int i=start;i<=end;i++){
		s += nums[i];
	}
	floata size = end-start+1;
	floata ans = s/size;
	
	return  ans;
}
floata deviation(int start, int end){
	floata a =avg(start,end);
	floata s = 0;
	for(int i=start;i<=end;i++){
		s +=powl(floata(nums[i])-a,2.0);
	}
	floata size = end-start+1;
	floata ans = sqrtl(s/size);
	return ans;
}
int main(){
	
	cin>>n>>k;
	
	for(int i =0;i<n;i++){
		int data;
		cin>>data;
		nums.push_back(data);
	}
	floata minval = 9999999999999999;
	for(int i= k;i<=n;i++){
		for(int j = 0;j<n-i+1;j++){
			if(j+i-1<j) continue;
			floata tmp = deviation(j,j+i-1);
			//cout<<j <<"~"<<j+i-1<<":";
			//cout<<tmp<<endl;
			if(tmp<minval){
				minval =tmp;
			}
		}
	}
	printf("%Lf\n",minval);
	
	return 0;
} 