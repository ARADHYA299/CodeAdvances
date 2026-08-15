#include<iostream>
using namespace std;

class student{
	private:
		int phonenumber;
	public:
		char name;
		
	
	  void print(){
		cout<<"The name is: "<<endl;
		cin>>name;
		
	}
	
	
	int getphonenumber(){
		return phonenumber;
	}
	char getname(){
		return name;
	}
	void setphonenumber(int p){
		phonenumber = p;
	}
	void setname(char n){
		name = n;
	}
};

int main(){
	student A;
	cout<<"The name is:"<<A.getname()<<endl;
	A.setphonenumber(1234);
	cout<<"The phonenumber is:"<<A.getphonenumber()<<endl;
	
	return 0;
}