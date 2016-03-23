#include <iostream>
using namespace std;
 

 
int main() {
    
    string slowo;
    cin >> slowo;
    int n= slowo.size();
    int p=1;
    
    for(int i=0;i<n/2;i++)
    {   if(slowo[i]!=slowo[n-1-i])
        {p=0;
        break;
        }
    }
    
    if(p==1)
        cout<<"TAK";
    else
        cout<<"NIE";
        
}
