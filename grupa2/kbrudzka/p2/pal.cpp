#include <iostream>
using namespace std;

int main() {

string s;

cin>>s;
int n= s.length();
bool pal=true;

for (int i=0;i<n;i++){
if (s[i]!=s[n-i-1])
pal=false;
}

if (pal==true) cout<<"TAK";
else cout<<"NIE";

}

