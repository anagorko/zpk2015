#include <iostream>
using namespace std;

int main() {
int n;
cin>>n;

int t[n];
for (int i=0;i<n;i++)
{
cin>>t[i];
}

int w[6]={0}; // w: wynikowy wektor 6 cyfr, wypełniony na początku zerami

for (int j=0;j<n;j++) 
{
for (int k=1;k<=6;k++)
    {
if (t[j]==k) /*jesli na j-tym miejscu tablicy pojawi się liczba k to zliczam ją na k-1 miejscu tablicy wynikowej*/
    w[k-1]++;
    }

}


for (int l=0;l<6;l++){
cout<<w[l]<<" ";     }
}
