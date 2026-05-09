# include<iostream>
using namespace std;

void shiftRight(int arr[] , int k , int n){
	if(n==0){
		return;
	}
	if(k>n){
		cout<<"Enter valid value"<<endl;
	}
	int temp[k];
	for(int i=n-k;i<n;i++){
		temp[i-n+k] = arr[i];
	}
	for(int i=n-k-1; i>=0;i--){
		arr[i+k] = arr[i];
	}
	for(int i=0;i<k;i++){
		arr[i] = temp[i];
	}
}

int main(){
	int n , k;
	cin>>n>>k;
	
	int arr[n];
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	cout<<"Current array"<<endl;
	for(int i=0;i<n;i++){
		cout<<arr[i]<<"";
	}
	shiftRight(arr , k ,n);
	
	cout<<"Array after shifting"<<endl;
	for(int i=0;i<n;i++){
		cout<<arr[i]<<"";
	}
	
	return 0;
	
}