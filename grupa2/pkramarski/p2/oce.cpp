#include<iostream>
using namespace std;

int main(){
    int o;
    cin >> o;

    int t[o];
    for(int i = 0; i<o; i++)
        cin >> t[i];

    int licznik=0;

    for(int i = 1; i<=6; i++){
        for(int j = 0; j<o; j++){
            if(t[j]==i)
                licznik++;
    }
        cout << licznik << " ";
        licznik=0;
        }
}
