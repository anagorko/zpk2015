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
	    int n;
	    cin >> n;
	    int t[n];
	    for (int i = 0; i < n; i++)
	        cin >> t[i];
	    int s;
	    s = NWD(t[0], t[1]);
	    for (int j = 2; j <= n-1; j++)
	        s = NWD(s, t[j]);
	    cout << s;
	}
