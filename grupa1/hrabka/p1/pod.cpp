#include <iostream>

using namespace std;

int main()
{
    int a, b, c, i;
    cin >> a >> b >> c;
    for(i=0; a<=b; a++)
    {
        if(a%c == 0)
        {
            i++;
        }
    }
    cout << i << endl;

    return 0;
}
