#include <iostream>
using namespace std;

int main()
{
    int n,pala,dwoja,troja,czwora,piatka,szostka;
        cin>>n;
    int t[n];
    for(int i=0;i<n;i++){
        cin>>t[i];
    }
        pala=0;
        dwoja=0;
        troja=0;
        czwora=0;
        piatka=0;
        szostka=0;
    for (int i=0;i<n;i++){
        if(t[i]==1){
            pala=pala+1;
        }
        if(t[i]==2){
            dwoja=dwoja+1;
        }
        if(t[i]==3){
            troja=troja+1;
        }
        if(t[i]==4){
            czwora=czwora+1;
        }
        if(t[i]==5){
            piatka=piatka+1;
        }
        if(t[i]==6){
            szostka=szostka+1;
        }

    }

    cout<<pala<<" "<<dwoja<<" "<<troja<<" "<<czwora<<" "<<piatka<<" "<<szostka;
}

