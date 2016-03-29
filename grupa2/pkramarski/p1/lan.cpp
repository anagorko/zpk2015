#include<iostream>
using namespace std;

int main(){
    int tel, rok;
    cin >> tel >> rok;

    int lan=tel%10;
    lan *= 2;
    lan += 5;
    lan *= 50;
    lan += 1764;
    lan -=rok;
    cout << lan << endl;
}
