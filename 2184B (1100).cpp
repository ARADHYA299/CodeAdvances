#include<bits/stdc++.h>

using namespace std;

class Solution{
	public:
		void Solve(){
			long long s , k , m;
			if(!(cin >> s >> k >> m)) return;
			
			long long num_flips = m/k;
			
			long long rem_time = m%k;
			
			long long T;
			
			if(s <= k){
				T = s;
			}
			else{
				if(num_flips % 2 == 0){
					T = s;
				}
				else{
					T = k;
				}
			}
			
			long long result = T - rem_time;
			
			cout << max(0LL , result) << "\n";
		}
};



int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Solution hourGlass;
	
	int t;
	cin >> t;
	while(t--){
		hourGlass.Solve();
	}
	
	return 0;
}