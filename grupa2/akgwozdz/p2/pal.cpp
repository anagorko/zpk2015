#include <iostream>
#include <string>
using namespace std;
 
int main() 
{
    string s;
    bool palindrom;
    palindrom = true;
    int n, i;
    cin >> s;
    n=s.size();
    for (i = 0; i<=n-1; i++)
        if(s[i]==s[n-1])
            n--;
        else
            palindrom = false;

    if (palindrom == true)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;  
}
