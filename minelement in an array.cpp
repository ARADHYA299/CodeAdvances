#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


int main(){
	
	int n;
	
	cin >> n;
	
	vector<int>nums(n);
	
	for(int i = 0 ; i < n ; i++){
		cin >> nums[i];
	}
	
	
	auto minEl = *min_element(nums.begin() , nums.end());
	
	cout << minEl;
	
	return 0;
}