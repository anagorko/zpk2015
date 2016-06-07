
#include<iostream>
#include<cmath>
#include<string>
using namespace std;

int pierwsza_mniejsza(string napis1,string napis2){
    int a=1;
    int b=2;
    int i=0;
        while(napis1[i]==napis2[i]){
            i++;
        }
       if(min(napis1[i+1],napis2[i+1])==napis1[i+1]){
        return a;

       }else if(min(napis1[i+1],napis2[i+1])==napis2[i+1]){
        return b;

        }
}
int dlugosc_napisu(string napis){
            int dlugosc;
            for(int i; i<napis.length();i++){
                dlugosc++;
            }
            return dlugosc;

}

int main(){




string napis1;
string napis2;
string napis3;

cin >> napis1;
cin >> napis2;
cin >> napis3;

int rowne=0;
        for(int i= 0; i<napis1.length();i++){
            if(napis1[i]!=napis3[i]){
                rowne++;
                }
            }


if(napis2 == "==" && napis1.length() == napis3.length() && rowne == 0){
            cout<<"TAK"<<endl;
        }else if((napis2=="!=" &&napis1.length() == napis3.length() && rowne != 0) || napis2 == "!=" && napis1.length()!= napis3.length()){
            cout<<"TAK"<<endl;
    }else if((napis2 == "<" && napis1.size() < napis3.size()) || (napis2 == "<" && napis1.size() == napis3.size() && pierwsza_mniejsza == 1)){
            cout<<"TAK"<<endl;
    }else if((napis2 == ">" && napis1.length() > napis3.length()) || (napis2 == ">" && napis1.length() == napis3.length() && pierwsza_mniejsza == 2)){
            cout<<"TAK"<<endl;
    }else if((napis2 == "<=" && napis1.length() < napis3.length()) || (napis2 == "<" && napis1.length() == napis3.length() && pierwsza_mniejsza == 1) || (napis1.length() == napis3.length() && rowne == 0)){
            cout<<"TAK"<<endl;
    }else if((napis2 == ">=" && napis1.length() > napis3.length()) || (napis2 == ">" && napis1.length() == napis3.length() && pierwsza_mniejsza == 2) || (napis1.length() == napis3.length() && rowne == 0)){
            cout<<"TAK"<<endl;
    }else{
            cout<<"NIE"<<endl;
    }
        return 0;


}


