#include <iostream>
using namespace std;

int main(){
    int n=0;
    int pomiar=0;
    int i=1;
    while(i>=0){
    
        cin>>i;
        if (pomiar<i){
                n++;
        pomiar=i;
    
        }
    }
    cout<<n;

}
