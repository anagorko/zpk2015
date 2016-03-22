#include <iostream>
using namespace std;

int main() {
    int nr, rok, wyn;
    
    cin >> nr >> rok;
    
    wyn=nr%10; 	/*ostatnia cyfra*/
    wyn*=2;		
    wyn+=5;
    wyn*=50;
    wyn+=1766; /* mamy 2016 rok, wiec trzeba bylo zmodyfikowac tresc zadania*/
    wyn-=rok;

    cout << wyn << endl;
}
