#include <iostream>
using namespace std;

int main(){

string word;
long int n,i=0;
bool pal = true;

cin>>word;
n=word.size();

while(pal==true && i<n/2){
    if(word[i]!=word[n-1-i])
        pal=false;
        i++;
}

if(pal)
    cout << "TAK" << endl;
else
    cout << "NIE" << endl;


}
