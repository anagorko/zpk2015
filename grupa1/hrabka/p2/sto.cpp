
#include <iostream>

using namespace std;

int main()
{
    int a,b,k, x, y;
    cin >> a >> b >> k;

    x=a/k;
    y=b/k;
    if(x==0 || y==0)
    {
        cout<<0;
        return 0;
    }
    if(x==1 || y==1)
    {
        cout<<(x+y-1);
        return 0;
    }
    cout<< 2*(x+y-2);

    return 0;
}
