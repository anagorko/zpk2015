#include <iostream>
using namespace std;

int main() {
 int s;
 cin>>s;
 int t[s];
 for (int i=0; i<s; i++) {cin >> t[i];}

int a,b,c;
a=t[0];

for (int i = 1; i < s-1; i++) {
    b=t[i];
    while(b!= 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    t[0]=a;
}
    cout << t[0];
}





