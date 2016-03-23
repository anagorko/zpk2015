#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
int t[4]={2,4,8,6};
int n;
cin >> n;
if (n==0) {cout << 1;}
else { cout << t[(n-1)%4];}
}
