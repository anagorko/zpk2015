#include <iostream>
	using namespace std;
	
	int NWD(int a, int b){
	    while (a != 0 && b != 0){
	        if (a % b == 0 || b % a == 0){
	            if (a >= b)
	                return b;
	            else
	                return a;
	        }
	        if (a > b)
	            a = a % b;
	        else
	            b = b % a;
	    }
	}
	
	int main() {
	    int z;
	    cin >> z;
	    int dzielnik[z];
	    int n[z]; 
	    int d[z];
	    for (int i = 0; i < z; ++i){
	        cin >> n[i] >> d[i];
	        dzielnik[i] = NWD(n[i], d[i]); //najw wspol dzielnik dla iteh wart
	    }
	    for (int i = 0; i < z; ++i)
	        cout << n[i] / dzielnik[i] << endl;
	
	}
