
#include <iostream>;
using namespace std;

int main(){

unsigned long long  i;
cin>>i;
int reszta=0;
while((i/2)!=0){
    reszta=reszta+i%2;
    i=i/2;
    }

    if(reszta == 0){
        cout<<"TAK"<<endl;
        }else{
        cout<<"NIE"<<endl;
        }
}
