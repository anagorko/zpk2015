#include <iostream>
using namespace std;

int main() 
{
    int n, m;
    cin >> n >> m;
    int cena[n][m];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> cena[i][j];
        }
    }

    int x = 100*1000, y = 0;

    for(int i = 0; i < n - 1; i++)
        for(int k = i; k < n; k++ )
        {
            for(int j = 0; j < m; j++)
            {
                if(cena[k][j] < cena[i][j])
                    y += cena[k][j];
                else
                    y += cena[i][j];
            }

            if(y < x)
                x = y;

            y = 0;
            }


    cout << x << endl;
    
return 0;
}
