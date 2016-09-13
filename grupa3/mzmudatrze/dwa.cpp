#include <iostream>
using namespace std;
    int sum_min(int x[], int y[], int z){
    int sum = 0;
      for(int i = 0; i < z; ++i){
        if (x[i] >= y[i])
          sum += y[i];
              else
          sum += x[i];
  }
  return sum;
  }
int main() {
int n, m;
cin >> n >> m;
  int x[n][m];
int y[m], r[m];
      for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
          cin >> x[i][j];
int price_min = 100000;
    for (int i = 0; i < n - 1; ++i){
    for (int j = i + 1; j < n; ++j){
    for (int k = 0; k < m; ++k){
        y[k] = x[i][k];
        r[k] = x[j][k];
}
int price = sum_min(x, r, m);
  if (price < price_min)
      price_min = price;
}
}
cout << price_min << endl;
}
