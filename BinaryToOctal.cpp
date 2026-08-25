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
	
	int octal = 0;
	power = 1;
	
	while(decimal > 0){
		int digit = decimal % 8;
		
		octal += digit * power;
		
		power *= 10;
		decimal /= 8;
	}
	
	cout << "This is octal : "<<octal;	
	
	return 0;
}