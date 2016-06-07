#include <iostream>
using namespace std;

int main(){

string slowo;
cin >> slowo;
int s=slowo.size();
bool palindrom=true;

int d=s/2;



for(int i=0;i<d;i++){
        if(slowo[i]!=slowo[s-1-i]){
            palindrom=false;
            }

}
if(palindrom){
cout<<"TAK"<<endl;
}
else{
    cout<<"NIE"<<endl;

}


}
