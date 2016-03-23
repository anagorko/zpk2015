#include <iostream>
using namespace std;
 
int main() {
    int n, l;
    cin >> n;
    cin>>l;
    int t[n];
    for(int i=0;i<n;i++)
        cin >> t[i];
    
    int s=-1;
    int k=-1;
    
    for(int i=0; i<n; i++)
    {  if(t[i]==l)
        {s=i+1;
        break;}
    }
    
    for(int i=0; i<n;i++)
    {
        if(t[i]==l)
        k=i+1;
    }
    
    cout << s <<" "<<k;
}
