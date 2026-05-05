#include<bits/stdc++.h>

using namespace std;

void solve(){
	long long n , k;
	
	cin >> n >> k;
	
	if(n%2 == k%2 && n >= k*k){
		cout << "YES" << "\n";
	}
	else{
		cout << "NO" << "\n";
	}
}




int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int t;
	cin >> t;
	
	while(t--){
		solve();
	}
	
	return 0;
}