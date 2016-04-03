#include <iostream>
using namespace std;

int main() {
    int A, B, K;
    cin >> A >> B >> K;

    if(B>A){
        int C = B;
        B = A;
        A = C;
    }
    if(A>0 && B>0 && K>0 && A>=K && B>=K && A>=B){
        if(B>=K && B<2*K){
            int D = A/K;
            cout << D << endl;
        }
        if(B>=2*K && B<3*K){
            int D = 2*(A/K);
            cout << D << endl;
        }
        if(B>=3*K){
            int D = 2*(A/K);
            int E = 2*((B-2*K)/K);
            int F = D + E;
            cout << F << endl;
        }
    }
    else cout << 0 << endl;
}
