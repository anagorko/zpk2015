#include <iostream>
using namespace std;

int znajdz (long long xmax, long long p, long long q){
    long long xmin = 1;

    while (xmax > xmin){
        long long sr = (xmax + xmin) / 2;
        if (sr > 1000000){
            xmax = sr - 1;
        } else{
            long long f = sr * sr * sr + p * sr;
            if (f > q){
                xmax = sr - 1;
            }else if (f == q){
                return sr;
            }else {
                xmin = sr + 1;
            }
        }
        }
    if (xmin == xmax){
        if (xmin * xmin * xmin + p * xmin == q){
            return xmin;
        }
    }
    return -1;
}

int main(){
    int z;
    cin >> z;
    long long p[z], q[z], c[z];
    for (int i = 0; i < z; i++){
        cin >> p[i];
        cin >> q[i];
    }
    for (int i = 0; i < z; i++){
        long long xmax = q[i] / p[i];
        c[i] = znajdz (xmax, p[i], q[i]);
    }
    for (int i = 0; i < z; i++){
        if (c[i] > 0){
            cout << c[i] << endl;
        } else {
            cout << "NIE" << endl;
        }
    }

}
