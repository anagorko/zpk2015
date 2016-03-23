#include <iostream>
#include <string>
using namespace std;

bool wieksze(string a, string b) {
    if (a.size() > b.size())
        return true;
    else if (a.size() < b.size())
        return false;
    else {
        for (int i = 0; i < a.size(); i++)
            if (a[i] < b[i])
                return false;
            else if (a[i] > b[i])
                return true;
        return false;
    }
}

bool rowne(string a, string b) {
    if (a.size() != b.size())
        return false;
    else {
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                return false;
        return true;
    }
}

int main() {
    string a, b;
    string c;
    cin >> a >> c >> b;

    bool odp = true;

    if (c == ">")
        odp = wieksze(a, b);
    else if (c == "<")
        odp = wieksze(b, a);
    else if (c == "==")
        odp = rowne(a, b);
    else if (c == "!=")
        odp = !rowne(a, b);
    else if (c == ">=")
        odp = !wieksze(b, a);
    else if (c == "<=")
        odp = !wieksze(a, b);

    if (odp)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
