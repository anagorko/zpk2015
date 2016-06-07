
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;


int NWD(int a, int b){

int x, y;
x=a;
y=b;
int r= a%b;
while(r!=0){
    a=b;
    b=r;
    r=a%b;
}

return b;

}




int main() {
 int z;
 cin >> z;
 int t[z][3];
 for(int i=0; i<z;++i){
    cin>>t[i][0] >>t[i][1];
    t[i][2]=NWD(t[i][0],t[i][1]);
 }
 for(int i=0;i<z; ++i)
cout<<t[i][0]/t[i][2]<<endl;


}


