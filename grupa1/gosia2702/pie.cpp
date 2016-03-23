#include <iostream>
using namespace std;

int main() {
    int n,x,p,o ;
    p=0;
    o=0;
    cin >> n >> x  ;
   int c[n];
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (c[i]==x & p==0) {p=i+1;o=p;}
        if (c[i]==x & p>0) {o=i+1;}
            };

        if (p==0) {p=-1; o=-1;}
        cout<<p<<" " <<o;

}
