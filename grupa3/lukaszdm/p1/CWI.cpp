#include <iostream>
using namespace std;

int main(){
    int x;
    int y;
    cin >> x >> y;

    if(x==0 && y==0 ){
        cout << "0" << endl;
    }
    if(x==0 && y!=0){
       cout<<"OY" << endl;
    }
    if(x!=0 && y==0){
        cout <<"OX" << endl;
    }
    if(x>0 && y>0){
        cout << "I" << endl;
    }
    if(x>0 && y< 0) {
        cout<< "IV" << endl;
    }
    if(x<0 && y< 0){
        cout<< "III" << endl;
    }
    if(x<0 && y> 0){
        cout<< "II" << endl;
    }

}
