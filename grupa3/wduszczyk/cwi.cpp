

#include <iostream>
#include <string>
using namespace std;

int main()
{
int x, y;
cin>>x>>y;

if (x==0){
    if (y==0){
        cout<<0<<endl;
        } 
        else {
            cout<<"OY"<<endl;
            }
    } 
    else {
        if (y==0){
                    cout<<"OX"<<endl;
            } else 
            {
            if (x>0){
                if (y>0){ cout<<"I"<<endl; } 
                else {cout<<"IV"<<endl;}
            }
            else{
                if (y>0) {cout<<"II"<<endl;}
                else{cout<<"III"<<endl;}
            }
            }
}
}