#include <iostream>
using namespace std;

int mniejsza_od(int t[],int n, int limit){

   int maks = 0;

   for(int i =0; i<n ; ++i){
        if(t[i]>maks && t[i]<limit)
            maks=t[i];
}
return maks;

}


int main(){
 int k;

 cin >> k;
 int t[k];
 for(int i=0; i<k; ++i)
    cin >> t[i];
 int x = mniejsza_od(t, k, mniejsza_od(t, k, 1000001));

 cout << x << endl;

}
