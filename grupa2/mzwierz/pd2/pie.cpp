#include <iostream>
using namespace std;

int main(){

int n,x;
cin >> n >> x;
int t[n];

for (int i=0; i<=n-1;i++){
    cin >> t[i];
    }

int pierwszy = -1;
int ostatni = -1;

for (int i=0; i <=n-1; i++){
    if (t[i]==x && pierwszy==-1)
    {
        pierwszy = i+1;
        ostatni=pierwszy;
        }
    else if(t[i]==x)
    {
        ostatni = i+1;
    }
}

cout << pierwszy<< " "<< ostatni;

}
