#include <iostream>

using namespace std;

int main()
{
	int A, B, K;
	cin >> A >> B >> K;

	int wariantA = 2 * (A / K) + 2 * ((B - 2 * K) / K);
	int wariantB = 2 * ((A - 2 * K) / K) + 2 * (B / K);

	cout << wariantA ? wariantA > wariantB : wariantB;

	system("pause");
	cin.get();
	return 0;
}
