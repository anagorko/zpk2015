#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

int bin(int t[],int p1, int k1, int z){

      while( k1!=p1 & k1!=p1+1  ){
           if (t[(k1+p1)/2] == z) { return (k1+p1)/2;}
           if (t[(k1+p1)/2] > z) {k1=(k1+p1)/2;}
           else p1=(k1+p1)/2;
                    }
                    return -1;
                    }



int main()
{
    //wczytanie danych
    int n, m, i, j, lewy, prawy, l, p;
    cin>>n;
    int * a = new int[n];
    for(i=0; i<n; i++){
            cin>>a[i];
        }
    cin>>m;
    int * b = new int[m];
    for(int i=0; i<m; i++){
            cin>>b[i];
        }

    for(j=0;j<m;j++){

        if (bin(a,0,n-1,b[j])==-1) {cout<<0<<endl;}
        else {
            lewy=bin(a,0,n-1,b[j]);
            prawy=lewy;
            l=lewy;
            p=prawy;
            while(p!=-1) {p=bin(a,p,n-1,b[j]); if (p!=-1) {prawy=p;} if(p==-1 & prawy==n-2) {prawy=n-1;}
                            }
            while(l!=-1) {l=bin(a,0,l,b[j]);   if (l!=-1) {lewy=l;} if(l==-1 & lewy==1) {lewy=0;}
                            }
            cout<< prawy-lewy+1<<endl;
        }

    }




   }

