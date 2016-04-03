#include<iostream>
using namespace std;

int main(){
    int n, c;
    cin >> n >> c;

    int t[n];
    for (int i=0; i<n; i++)
        cin >> t[i];

    int pie = -1;
    int ost = -1;

    for(int i=0; i<n; i++)
        if(t[i]==c) {
            pie = i+1;
            break;
        }

    for(int j=n;j>=0;j--)
        if(t[j]==c){
            ost = j+1;
            break;
        }

    cout << pie << " " << ost << endl;
}
