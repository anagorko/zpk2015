#include <iostream>
#include <string>
using namespace std;

int main() {
    string slowo;
    cin>>slowo;

    bool b;
    b=1;
    for (int i=0;i<slowo.size();i++)
    {
        if(slowo[i]!=slowo[slowo.size()-i-1]){b=0;}
    }
    if (b==0) cout<<"NIE";
    if (b==1) cout << "TAK";
}
