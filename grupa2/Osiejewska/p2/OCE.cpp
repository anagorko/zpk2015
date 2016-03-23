#include <iostream>
using namespace std;

int main(){
int a;
cin >> a;

int t[a];
for (int i=0; i<a; i++)
cin >> t[i];

int s[6] = {};
int c;

for (int i=0; i<a; i++){
c=t[i];
s[c-1]=s[c-1]+1;

}
for(int i=0; i<6; i++)
cout << s[i] << " ";
}
