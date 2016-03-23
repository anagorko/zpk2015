#include <iostream>
using namespace std;

int main() {
    int n, l;
    int u=-1;
    int v=-1;
    cin >> n;
    cin>>l;
    int t[n];

    for(int i=0;i<n;i++){
        cin >> t[i];
    }

    for(int i=0; i<n; i++)
    {  if(t[i]==l)
        {u=i+1;
        break;}
    }

    for(int i=0; i<n;i++)
    {
        if(t[i]==l)
        v=i+1;
    }

    cout << u <<" "<<v;
}
