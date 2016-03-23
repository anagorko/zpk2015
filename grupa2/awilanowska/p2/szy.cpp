#include <iostream>
using namespace std;

int main() {
    int liczba, k;
    cin >> liczba >> k;
    string tekst;
    cin >> tekst;

    if (liczba == 1) {
        for (int i = 0; i < tekst.length(); i++) {
            if ((int)tekst[i] >= 65 && (int)tekst[i] <= 90)
                if (((int)tekst[i] + k) <= 90)
                    cout << (char)(tekst[i] + k);
                else
                    cout << (char)(tekst[i] + k - 26);
            else if ((int)tekst[i] >= 97 && (int)tekst[i] <= 122)
                if (((int)tekst[i] + k) <= 122)
                    cout << (char)(tekst[i] + k);
                else
                    cout << (char)(tekst[i] + k - 26);
            else
                cout << tekst[i];
        }
    }

    else if (liczba == 2) {
        for (int i = 0; i < tekst.length(); i++) {
            if ((int)tekst[i] >= 65 && (int)tekst[i] <= 90)
                if (((int)tekst[i] - k) >= 65)
                    cout << (char)(tekst[i] - k);
                else
                    cout << (char)(tekst[i] - k + 26);
            else if ((int)tekst[i] >= 97 && (int)tekst[i] <= 122)
                if (((int)tekst[i] - k) >= 97)
                    cout << (char)(tekst[i] - k);
                else
                    cout << (char)(tekst[i] - k + 26);
            else
                cout << tekst[i];
        }
    }

    cout << endl;
}
