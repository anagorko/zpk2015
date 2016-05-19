#include <iostream>
#include <string>

using namespace std;

int main() {
    
    int numer, rok;
    cin >> numer >> rok;
   
    int w = numer%10;
    
    w*=2;
    w+=5;
    w*=50;
    w+=1764;
    w-=rok;

    cout << w;

    }