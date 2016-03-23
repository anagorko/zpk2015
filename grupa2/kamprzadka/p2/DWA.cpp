//DWA
#include<iostream>
#include<math.h>
#include <iomanip>
using namespace std;

int main()
{
    int m, n;
    cin>>n>>m;
    if(n<2 || m>100 || m<1) return 0;
    
    int d[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) cin>>d[i][j];
        
    int nm=1000, sp=0;
    
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            for(int k=0;k<m;k++){
                if(d[i][k]>=d[j][k]) sp+=d[j][k]; 
                else sp+=d[i][k];
            }
        if(nm>=sp) nm=sp; 
        sp=0;
        }
    }
    cout<<nm<<endl;
}
