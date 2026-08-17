#include<iostream>
#include<vector>

using namespace std;


int main(){
	
	int binary;
	cin >> binary;
	
	int power = 1;
	int decimal = 0;
	
	while(binary > 0){
		int digit = binary % 10;
		
		decimal += digit * power;
		
		power *= 2;
		binary /= 10;
			
	}
	
	cout << decimal ;	
	
	return 0;
}