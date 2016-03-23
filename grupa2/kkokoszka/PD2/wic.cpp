#include <iostream>
using namespace std;

int main(){
    int n,i,j,l,a;
        cin>>n;
    int t[n];
        for(i=0;i<n;i++){
        cin>>t[i];
        }
        for(i=0;i<n;i++){
            l=0;
        for(j=0;j<n;j++){
                if(t[j]>t[i]){
                    l=l+1;
                }
            }
                 if (l==1){
                     a=t[i];
                }
            }
        cout<<a;

}
