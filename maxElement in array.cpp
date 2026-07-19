#include<iostream>
#include<algorithm>
#include<vector>


using namespace std;



int main(){
	int arr[5] = {8, 10, 5, 7, 9};
	
	int maxEl = arr[0];
	
	for(int i=1;i<5;i++){
		if(arr[i] > maxEl){
			maxEl = arr[i];
		}
	}
	
	cout << maxEl;
	
	return 0;
}