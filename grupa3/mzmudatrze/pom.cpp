#include <iostream>
using namespace std; 

int main() {
    int x;
    int pomiar;
    int a=0;
    
    cin>>x;
    
    while ( x!=-1 )
        {   
            cin >> x;
            
            if (x>pomiar)
                { 
                    a++;
                    x=pomiar;
                }
        }
        cout << a << endl;
        
}
