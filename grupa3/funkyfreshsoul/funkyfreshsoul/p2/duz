#include <iostream>
#include <cstring>
using namespace std;

int porownaj(string a, string b)
{
if(a.size()>b.size())
    return 2;
if(a.size()<b.size())
    return 3;
if(a.size()== b.size())
    {
        while(1){
                if(a.size()==1)
                    if(a[0]==b[0])
                        return 1;
                if(a[0]>b[0])
                    return 2;
                else if(a[0]<b[0])
                    return 3;
                a.erase (0,1);
                b.erase (0,1);
            }
        }
}

int main()
{
    string a,b,znak;
    cin >> a >> znak >> b;

    if(znak=="==")
    if(porownaj(a,b)==1){
        cout<<"TAK"<<endl;
        return 0;
    }

    if(znak=="!=")
    if(porownaj(a,b)>1){
        cout<<"TAK"<<endl;
        return 0;
    }

    if(znak==">")
    if(porownaj(a,b)==2){
        cout<<"TAK"<<endl;
        return 0;
    }

    if(znak=="<")
    if(porownaj(a,b)==3){
        cout<<"TAK"<<endl;
        return 0;
    }

    if(znak==">=")
    if(porownaj(a,b)<3){
        cout<<"TAK"<<endl;
        return 0;
    }

    if(znak=="<=")
    if(porownaj(a,b)!=2){
        cout<<"TAK"<<endl;
        return 0;
    }
    cout<<"NIE"<<endl;
}
