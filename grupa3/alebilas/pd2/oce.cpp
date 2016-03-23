#include <iostream>
using namespace std;

int main(){

int n;
int x;
cin >> n;

int o[6];

// uzupelniamy tablice ocen

// uzupelniam tablice wynikow
for(int i=0; i<6; i++){
    o[i]=0;
}

for(int i=0; i<n; i++){
cin >> x;
    switch(x){
        case 1:
            o[0]++;
            break;
        case 2:
            o[1]++;
            break;
        case 3:
            o[2]++;
            break;
        case 4:
            o[3]++;
            break;
        case 5:
            o[4]++;
            break;
        case 6:
            o[5]++;
            break;
    }
}

 for(int i=0;i<6;i++)
        cout << o[i] << " ";

}
