# include <iostream>
using namespace std;

class shop{
	int itemID[100];
	int itemPrice[100];
	int counter;
	public:
		void initcounter(void) { counter =  0;}
		void setPrice(void);
		void displayPrice(void);
};

void shop :: setPrice(void){
	cout<<"Enter ID of your item"<<endl;
	cin>>itemID[counter];
	cout<<"Enter the price of your item"<<endl;
	cin>>itemPrice[counter];
	counter ++;
}

void shop :: displayPrice(void){
	for (int i=0 ; i<counter ; i++){
		cout << "The price of item with ID" << itemID[i]<< "is" << itemPrice[i] <<endl;
	}
}

int main(){
	shop NGS;
	NGS.setPrice();
	NGS.setPrice();
	NGS.setPrice();
	NGS.setPrice();
	NGS.setPrice();
	NGS.displayPrice();
	
	return 0;
	
}