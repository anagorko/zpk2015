#include <iostream>
using namespace std;

int nwd(int a, int b)
{
    int c=a%b;
    while(c!=0)
    {
        a=b;
        b=c;
        c=a%b;
    }
    return b;
}

int main(){
int n;
cin >> n;
int t[n][2];

for (int i=0; i<n; i++)
    cin >> t[i][0] >> t[i][1];

for (int i=0; i<n; i++)
    cout << t[i][0]/ nwd(t[i][0],t[i][1]) << endl;
}
