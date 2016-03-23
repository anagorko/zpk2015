#include <iostream>
using namespace std;

int main()
{
    int A, B, K, bok1, bok2;
    cin >> A >> B >> K;
    bok1=A/K;
    bok2=B/K;
        if (bok2==0 || bok1==0)
            cout << 0;
            else if (bok1==1)
            cout << bok2;
        else if (bok2==1)
            cout << bok1;
        else
            cout << bok2*2 + 2*(bok1-2);

return 0;
}
