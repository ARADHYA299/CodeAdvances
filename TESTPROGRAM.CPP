# include <iostream>
usin namespace std;

class binary{
	string s;
public:
	void read(void);
	void chk_binary(void);
	
};

void binary :: read (void){
	cout<<"Enter a binary number:"<<endl;
	cin>>s;
}
void binary :: chk_binary(void){
	for(i=0; i<s.length(); i++){
	}
	   if(s.at(i); i<s.length();i++){
	   	   cout<<"Incorrect binary format"<<endl;
	   	   exit(0);
	   }
}

int main(){
	binary b;
	b.read();
	b.chk_bin();
}