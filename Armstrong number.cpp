#include<iostream>
#include<cmath>
#include<string>

using namespace std;

bool Armstrong(int n){
	int k = 0;
	int temp = n;
	while(temp > 0){
		k++;
		temp/=10;
	}
	
	int sum = 0;
	int num = n;
	
	while(num > 0){
		int dig = num%10;
		
		sum += pow(dig , k);
		
		num/=10;
	}
	
	return sum == n;
}

int main(){
	int n;
	cin >> n;
	
	if(Armstrong(n)){
		cout <<"The no. " << n <<" is armstrong";
	}
	else{
		cout <<"The no. " << n << " is not armstrong";
	}
	
	return 0;
}