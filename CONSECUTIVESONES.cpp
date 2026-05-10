# include<iostream>
using namespace std;

void findones(int arr[] , int n){
	int count = 0 , maxcount =0;
	for(int i=0;i<n;i++){
		if(arr[i] == 1){
			count++;
			maxcount = max(count , maxcount);
		}
	    else{
	    	count = 0;
		}
	}
    cout<<"The number of consecutive ones are : "<<maxcount<<endl;


}

int main(){
	int n;
	cin>>n;
	
	int arr[n];
	cout<<"Enter the elements of the array : "<<endl;
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	
	cout<<"The current array is : "<<endl;
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" "<<endl;
	}
	
	findones(arr,n);
	
	return 0;
}
