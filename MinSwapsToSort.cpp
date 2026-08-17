#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int selectionSort(vector<int>&arr){
	int n = arr.size();
	int minSwaps = 0;
	
	for(int i=0;i<n;i++){
		int minIdx = i;
		
		for(int j=i+1;j<n;j++){
			if(arr[j] < arr[i]){
				minIdx = j;
			}
		}
		
		if(minIdx != i){
			swap(arr[i] , arr[minIdx]);
			minSwaps++;
		}
	}
	return minSwaps;
}

int main(){
	int n;
	cin>>n;
	
	vector<int>arr(n);
	for(int i=0;i<n;i++){
		cin >> arr[i];
	}
	
	int minSwaps = selectionSort(arr);
	
	cout << minSwaps;
	
	return 0;
}