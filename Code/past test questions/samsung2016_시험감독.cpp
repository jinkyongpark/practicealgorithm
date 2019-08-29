#include <iostream>
using namespace std;
typedef long long int ll;
const ll MAX = 1000010;
ll a[MAX],b,c,n;
int main(){
	cin>>n;
	for(ll i =0;i<n;i++) cin>>a[i];
	cin>>b>>c;
	ll ans = 0;
	for(ll i=0;i<n;i++) {
		a[i] -= b;
		ans++;
		if(a[i]<0) continue;
		if((a[i]/c)*c == a[i]){ //딱 떨어짐
			ans += (a[i]/c);
		}
		else
			ans +=(a[i]/c + 1);
	}
	cout<<ans;
	return 0;
}
