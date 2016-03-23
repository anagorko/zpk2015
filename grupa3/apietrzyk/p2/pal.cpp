#include <iostream>
#include <string>
 
using namespace std;
 
int main(){
	
	string s, o;
	cin >> s;
	
	int d = s.length();
	
	for (int i=0; i<d; i++){
		o+=s[d-i-1];
	}
	
	bool pal;
	if (o==s)
	{
		pal = true;
		cout << "TAK" <<endl;
	}
	else {
		pal = false;
		cout << "NIE" <<endl;
	}
}
