#include <iostream>
using namespace std;

int fun (int t[], int tab[], int n, int q, int j)
{
    int p, k, s;
    for(int i=0;i<=q-1;i++)
    {
        p=0;
        k=n-1;
        while(p<k)
        {
            s=(p+k+1)/2;
            if(t[s]<=tab[i])
                p=s;
            else
                k=s-1;
        }
        if(p==k && t[k]==tab[i])
            {
                j++;
                if(k!=0 && t[k-1]==t[k])
                {
                    fun(t,tab,k,q,j);
                    return 0;
                }
            }
        cout<<"j="<<j<<endl;
        j=0;
    }
}


int main()
{
int n,q,j=0;
cin>>n;
int t[n-1];
for(int i=0;i<=n-1;i++)
{
cin>>t[i];
}

cin>>q;
int tab[q-1];
for(int i=0;i<=q-1;i++)
{
cin>>tab[i];
}
fun(t,tab,n,q,j);
}
//program nie dziala poprawnie. problem jest z n ktore powinno pozostac takie samo.
