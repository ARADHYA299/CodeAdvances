#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
	string word;
	
	cin >> word;
	
	unordered_map<char,int> freq;
	
	for(auto& a : word){
		freq[a]++;
	}
	
	vector<pair<char,int>> arr(freq.begin() , freq.end());
	
	sort(arr.begin() , arr.end() , [](auto& a , auto& b){
		return a.second > b.second;
	});
	
	cout << arr[0].first;
	
	return 0;
}