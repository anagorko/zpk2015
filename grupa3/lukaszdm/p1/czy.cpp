#include <iostream>
using namespace std;

int main(){
    /* 10 5 18 9 30 15 48 24...
        9 30 15 48 24....
        8 4 2 1
        7 24 12 6 3 12 6 3
        100 50 25 78 39 120 60 30 15 tylko pot«gi dwojki*/

    long long c;
    cin >>c;
    while(c%2==0 && c!=1)
        c/=2;
    if(c==1)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;



}


