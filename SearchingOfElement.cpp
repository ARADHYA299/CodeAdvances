#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>

using namespace std;


int main(){
	int n;
	cin >> n;
	vector<int> arr(n);
	
	for(int i=0;i<n;i++){
		cin >> arr[i];
	}
	
	int k;
	cin >> k;
	
	
	sort(arr.begin() , arr.end());
	
	int left = 0 , right = n-1;
	
	while(left  <= right){
		int mid = left + (right - left) / 2;
		
		if(arr[mid] == k){
			cout << mid;
			break;
		}
		
		else if(arr[mid] < k){
			left = mid+1;
		}
		
		else if(arr[mid] > k){
			right = mid-1;
		}
	}	
	return 0;
}