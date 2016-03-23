# include<iostream>
#include<cmath> /*konieczne do obliczenia pierwiastka*/

using namespace std;

int main(){
int n;
cin >> n;

bool pierwsza=true;

if (n==2)
pierwsza=true;

int p;
p=sqrt(n);
for (int i=2; i<=p; i++)

if (n%i==0){
pierwsza=false;
}

if(pierwsza)
    cout<<"pierwsza"<<endl;
else
    cout << "zlozona";

}
