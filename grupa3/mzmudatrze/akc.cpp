#include <iostream>
	using namespace std;
	
	int n, r = 0;
	bool exist = false;
	
	int find_thefirst(int tabl[], int p, int k, int l){
	    while (k > p){
	        int sr = (k + p) / 2;
	        if (tabl[sr] == l){
	            if (r == 0){
	                r = sr;
	            }
	        }
	        if (tabl[sr] < l){
	            p = sr + 1;
	        } else{
	            k = sr;
	        }
	    }
	    if (tabl[k] == l){
	       return k;
	    } else{
	        return -1;
	    }
	}
	
	int find_thelast(int tabl[], int p, int k, int l){
	    while (k > p){
	        int sr = (k + p + 1) / 2;
	        if (tabl[sr] <= l){
	            p = sr;
	        } else{
	            k = sr - 1;
	        }
	    }
	    if (tabl[p] == l){
	        return p;
	    } else{
	        return -1;
	    }
	}
	
	int main() {
	    int q;
	    cin >> n;
	    int t[n];
	    for (int i = 0; i < n; i++){
	        cin >> t[i];
	    }
	    cin >> q;
	    int s[q];
	    for (int i = 0; i < q; i++){
	        r = 0;
	        cin >> s[i];
	        exist = false;
	        int first = find_thefirst(t, 0, n - 1, s[i]);
	        exist = false;
	        int last = find_thelast(t, r, n - 1, s[i]);
	        if (first == -1 || last == -1){
	            cout << 0 << endl;
	        } else{
	            cout << last - first + 1 << endl;
	        }
	    }
	}
