#include<iostream>
using namespace std;

int main(){
    int l;
    cin >> l;
    int t[l];
    for(int i=0; i<=l-1;i++)
    cin >> t[i];

    for(int i=0; i<=l-1;i+=2)
    cout << t[i] << " ";

    cout << endl;

    for(int i=1; i<=l-1;i+=2)
    cout << t[i] << " ";
}
