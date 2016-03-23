#include <iostream>
using namespace std;


int main() {
    int l = 0;

    int p, p2;

    cin >> p;
    p2=p;

    while (p != -1) {
        cin >> p;
        if(p > p2)
        {
            l++; 
            p2=p; 
        }
    }

    cout << l << endl;
}
