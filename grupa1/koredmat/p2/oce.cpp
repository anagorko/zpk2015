#include <iostream>
using namespace std;

int main() {
int l;
cin >> l;

int t[l], s[l];
for (int i=0; i<l-1; i++) {
        cin >> t[i];
        s[i]=0;
        }

for (int i=0; i<l-1; i++) {
        int j=1;
    while (j<=6) {if (t[i]=j) {s[j-1]++; j++;}
                    else j++;}
        }
for (int i=0; i<5; i++) {cout << s[i] << " ";}
    }






