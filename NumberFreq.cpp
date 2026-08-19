#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int main(){
	int n ;
	cin >> n;
	
	vector<int> arr(n);
	for(int i=0;i<n;i++){
		cin >> arr[i];
	}
	
	vector<int> order;
	unordered_map<int,int> mp;
	
	for(auto&a : arr){
		if(mp.find(a) == mp.end()){
			order.push_back(a);
		}
		mp[a]++;
	}
	
	
	
	
	for(auto a : order){
		cout << a << " " << mp[a] << endl;
	}
	
	return 0;
	
}