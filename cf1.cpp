# include<bits/stdc++.h>
 using namespace std;
 
 int main(){
 		
 	int t;
 	
 	cin>>t;
 	
 	while(t--){
 		int n;
 		cin>>n;
 		vector<int> arr(n);
 		
 		int max_val = INT_MIN;
 		
 		
 		for(int i=0;i<n;i++){
 			cin>> arr[i];
 			max_val = max(max_val , arr[i]);
		 }
		 
		 cout<< fixed << setprecision(6) <<max_val<<endl; 
	 }
 	
 	return 0;
 }