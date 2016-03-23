#include <iostream>
using namespace std;

int main()
{
    int a, i, n;
    cin>>a;
    n=0;
    while(a>0)
    {
    i=a%10;
    n=n*10+i;
    a=a/10;
    }
    cout << n <<endl;
}
