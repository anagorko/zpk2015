#include <iostream>
#include <algorithm>
using namespace std;
 
int main() 
{
int a, b, c, d, e, f, rok, A, B;

cin >> rok;

if (rok >= 1800 && rok <= 1899) {
A = 23;
B = 4;
}
else if (rok >= 1900 && rok <= 2099) {
A = 24;
B = 5;
}
else if (rok >= 2100 && rok <= 2199) {
A = 24;
B = 6;
}
else if (rok >= 2200 && rok <= 2299) {
A = 25;
B = 0;
}

a = rok % 19;
b = rok % 4;
c = rok % 7;
d = (a*19 + A) % 30;
e = (2*b + 4*c + 6*d + B) % 7;
f = d + e;

if (f <= 9) {
	cout << 22 + f << " " << 3;
}
else {
	cout << f - 9 << " " << 4;
}


}
