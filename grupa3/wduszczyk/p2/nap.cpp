// Example program
#include <iostream>
#include <string>

using namespace std;

int main()
{

	
	int n, l ;
	cin >> n;
	
    int t[n];
    
    for (int i = 1; i <= n; i++)
        cin >> t[i];

    for (int i = 1; i <=n; i++)
        if (i % 2 != 0)
            cout << t[i]<<" ";
            
            cout<< endl;

    for (int i = 1; i<=n; i++)
        if (i % 2 == 0)
            cout << t[i] << " ";
    cout << endl;
}