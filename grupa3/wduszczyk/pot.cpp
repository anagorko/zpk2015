#include <iostream>
#include <string>
using namespace std;



int main()
{

    long long a,w;
    cin>>a;
    w=1;
    if (a<=0){cout<<1;}
    else{
    while (w<=a) {cout<<w<<endl;
    w*=2;}   
}
}