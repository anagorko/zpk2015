#include<iostream>
#include <vector>
#include <cmath>
using namespace std;

long long pierwiastek(long long p, long long q){
    long long start = 0;
    long long end = 1000000;
    long long x = (start + end)/2;
    long long pierwiastek = -1;
        while(start < end){
            if(x * (x*x + p) >= q){
                if(x * (x*x + p) == q){
                    pierwiastek = x;
                    break;
                }
                end = x;
                x = (start + end)/2;
            }
            else
                start = x + 1;
                x = (start + end)/2;
        }
        return pierwiastek;
}

int main(){
    vector<long long> wyniki;
    long long liczba_zagadek;
    long long p, q;
    cin >> liczba_zagadek;

    for (int i = 0;i < liczba_zagadek;i++){
		cin >> p >> q;
		wyniki.push_back(pierwiastek(p,q));
	}

	for(int j = 0;j < liczba_zagadek;j++){
        if(wyniki[j] == -1)
            cout << "NIE" << endl;
        else
            cout << wyniki[j] << endl;
	}
};
