#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    while(true)
    {
        if(n == 1)
        {
            cout<<"TAK"<<endl;
            return 0;
        }
        if(n%2 != 0)
        {
            cout<<"NIE"<<endl;
            return 0;
        }
        n = n/2;
    }
}
