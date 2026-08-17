#include<iostream>
#include<algorithm>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
	int n , m;
	
	cin >> n >> m;
	
	vector<vector<int>> mat(n , vector<int>(m));
		
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin >> mat[i][j];		
		}
	}
	
	vector<int>Cons;
	
	int totalConsumption = 0;
	for(int i=0;i<n;i++){
		int sum = 0;
		
		for(int j=0;j<m;j++){
			sum += mat[i][j];
		}
		
		
		Cons.push_back(sum);
		
		totalConsumption += sum;
		
		cout << "The consumption for house : " << i + 1 << " is : " << sum << endl;
	}
	int avgCons = totalConsumption / n;
	
	cout << "The average consumption for society is : " << avgCons << endl;
	
	for(int i=0;i<Cons.size();i++){
		if(Cons[i] > avgCons){
			cout << "More than average consumption for house : " << i+1 << " ";
		}
	}
	
	return 0;
	
}