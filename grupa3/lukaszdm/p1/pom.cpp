#include <iostream>
using namespace std;

int main(){
    int prev=0, curr=0, n=0;

        while(curr!=-1){
            cin >> curr;
                if(curr!=prev)
                    n++ ;
            prev=curr;
        }
        cout << n-1 << endl;
}


