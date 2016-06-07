#include <iostream>
using namespace std;

int main(){
int liczba_ocen;
int ocena;
int tablica[liczba_ocen];
int liczba_jedynek=0;
int liczba_dwojek=0;
int liczba_trojek=0;
int liczba_czworek=0;
int liczba_piatek=0;
int liczba_szostek=0;

cin>>liczba_ocen;
for(int i=0;i<liczba_ocen;i++){

    cin>>ocena;
    if(ocena==1){
        liczba_jedynek++;
            }
            else{
                if(ocena==2){
                    liczba_dwojek++;
                }else{
                if(ocena==3){
                    liczba_trojek++;

                }else{
                if(ocena==4){
                    liczba_czworek++;

                }else{
                if(ocena==5){
                    liczba_piatek++;

                }else{
                    if(ocena==6)
                liczba_szostek++;}

                }
                }

                }

            }
    }
cout<<liczba_jedynek<<" "<<liczba_dwojek<<" "<<liczba_trojek<<" "<<liczba_czworek<<" "<<liczba_piatek<<" "<<liczba_szostek<<endl;
}
