#include <iostream>
using namespace std;

int main()
{
    unsigned int t;
    cin >> t;
    unsigned int g = t / 3600;
    unsigned int m = (t % 3600)/60;
    unsigned int s = t % 60;
    cout << g << "g" << m << "m" << s << "s" << endl;
}
