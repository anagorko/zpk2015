#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
long long  w(long long p,long long q,long long x){
return x*x*x+ p*x - q;
}

int main(){

bool v;
int i,n;
long long int l, r, s, p, q;

cin>>n;
long long int *a = new long long[n];
long long int *b = new long long[n];

for (i=0; i<n;i++){
    cin>>a[i];
    cin>>b[i];
    }

for(i=0; i<n; i++){

        v=false;
        p=a[i];
        q=b[i];
        l=0;
        r=100000;

        while (r-l>1 & !v) {
                s=(l+r)/2;

            if (w(p,q,s)>0 ) {r=s; }
            if (w(p,q,s)<0 ) {l=s; }
            if (w(p,q,s)==0 ) {v=true;}
        }
        if(w(p,q,s)==0) {cout<<s<<endl;}
           else { cout<<"NIE"<<endl;}

}
}
