#include <iostream>
using namespace std;

int main(){
int n, m;
cin >> n >> m;

int t[n][m];
for (int i=0; i<n; i++){
    for(int j=0; j<m; j++)
        cin >> t[i][j];
}
int pom;
for (int j=0; j<m; j++){
    for(int i=0; i<n; i++){
        if(t[i][j]>t[i+1][j]){
        pom=t[i][j];
        t[i][j]=t[i+1][j];
        t[i+1][j]=pom;
        }
    }
}
int suma=0;
for (int j =0; j<m; j++)
    suma+=t[0][j];
cout << suma << endl;
}
