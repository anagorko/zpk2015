#include <iostream>
using namespace std;

int main() 
{
    int a;
    cin >> a;
    int m[a];
    
    for (int i=0; i<=a-1; i++)
        cin >> m[i];

    for (int i=0; i<=a-1; i+=2)
            cout << m[i] << " ";

    cout << endl;

    for (int i=1; i<=a-1; i+=2)
        cout << m[i] << " ";
        
return 0;
}
