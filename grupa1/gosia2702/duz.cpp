#include<iostream>
#include<cstring>
using namespace std;

int main()
{
    string x, y, z ;


    cin>>x>>z>>y;;

    if (z=="<" | z=="<=") {

        if (x.size()<y.size() ) { cout<<"TAK"; return 0;}
        else {
                if (x.size()>y.size() ) { cout<<"NIE"; return 0;}
                else {
                if (x.size()==y.size()) { for(int i=0; i< x.size();i++) if (x[i]>y[i]) {cout<<"NIE"; return 0;}}
                else {cout<<"TAK"; return 0;}
        } }


    }


    if (z==">" | z==">=") {

        if (x.size()>y.size() ) {cout<<"TAK"; return 0;}
        else { if (x.size()<y.size() ) {cout<<"NIE"; return 0;}
                else {
                if (x.size()==y.size()) { for(int i=0; i< x.size();i++) if (x[i]<y[i]) {cout<<"NIE"; return 0;}}
                else {cout<<"TAK"; return 0;}

    } } }




    if (z=="==") {
        if(x.size()!=y.size()) {cout<<"NIE"; return 0 ;}
        else { if(x.size()==y.size()) {for(int i=0; i< x.size();i++) if (x[i]!=y[i]) {cout<<"NIE"; return 0;}}
        else {cout<<"TAK"; return 0;}

    } }





}
