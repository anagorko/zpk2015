#include <iostream>
using namespace std;

int main(){
    long long int n;
    cin >> n;
    int silnia = 1;
    if (n==0)
        silnia = 1;
    else {
        for(int i=1; i<=n; i++) {
            silnia=silnia*i;
        }
    }
    cout << silnia << endl;
}
