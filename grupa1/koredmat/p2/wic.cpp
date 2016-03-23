#include <iostream>
using namespace std;

int main() {
int n;
cin >> n;
int p[n];
for (int i=0; i<n; i++) {cin >> p[i];}

int m, wm;
m=p[0];
wm=p[0];

for (int i=0; i<n; i++) {
        if (m<p[i]) m=p[i];}

for (int i=0; i<n; i++) {
        if (wm<p[i] && p[i]!=m) wm=p[i];}
cout << wm;
    }






