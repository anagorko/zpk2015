#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++)
    {
        cin >> t[i];
    }

   int max=0; /*deklaruję wartość maksymalną i wic i przypisuje im wartość 0*/
   int wic=0;

   for (int k = 0; k < n; k++)
    {
        if (t[k]>=max)  /*gdy kolejne elementy tablicy będą większe niż dotychczasowe max, to wic przyjmuje wartość dotychcasowego maksimum, a nowe maksimum to wartość k-tego elementu tablicy*/
            {
                wic=max; max=t[k];
            }
        else
            {
                if (t[k]>=wic)
                wic=t[k];
            }


    }
   cout<<wic;


}
