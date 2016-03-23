#include <iostream>
using namespace std;
 

 
int main() {
    int n;
    cin >> n;
    int t[6];
    
    for (int i=0;i<6;i++)
    {   t[i]=0;
    }
     
     
    int k;
    
    for(int i=0;i<n;i++)
    { cin >> k;
      t[k-1]= t[k-1]+1;
    }
    
    for(int i=0;i<6;i++)
    { cout<<t[i]<<" ";
    }
    
}
