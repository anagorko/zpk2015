#include <iostream>
using namespace std;

int main(){

int n;
cin >> n;
int grade[n];
int stat[6];
for(int i=0;i<=5;i++)
    stat[i]=0;

for(int i=0; i<n; i++){
    cin >> grade[i];
    if(grade[i]==1)
        stat[0]++;
    if(grade[i]==2)
        stat[1]++;
    if(grade[i]==3)
        stat[2]++;
    if(grade[i]==4)
        stat[3]++;
    if(grade[i]==5)
        stat[4]++;
    if(grade[i]==6)
        stat[5]++;
}

for(int i=0;i<=5;i++)
    cout<<stat[i]<<" ";

}
