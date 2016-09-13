#include <iostream>
	using namespace std;
	
	int main() {
	    int x;
	    int y;
	    int o = -1;
	    int p = -1;
	      cin >> x >> y;
	    int t[x];
	      for (int i = 0; i < x; i++)
	        cin >> t[i];
	      for (int i = 0; i < x; i++)
	        if (t[i] == y)
	            o = i + 1;
	          for (int i = x-1; i >= 0; i--)
	              if (t[i] == y)
	                p = i + 1;
	    cout << p << " " << o << endl;
	}
