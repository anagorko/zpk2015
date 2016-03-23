#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;


int main() {
   int n;
   cin >> n;
   bool x = false;
   for (int i=2;i<=floor(sqrt(n));i++){
    if (n%i==0 ){
        x = true;
        break;
    }
   }
   switch (x)
   {
       case true:
            cout << "zlozona";
            break;
       case false:
            cout << "pierwsza";
            break;
   }
}
