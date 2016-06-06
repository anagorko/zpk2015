#include <iostream>
#include <string>
using namespace std;

int wieksza(string a, string b)
{
	if (a.size() > b.size()){
		return 1;
	}

	if (a.size() < b.size()) {
		return -1;
	}

	if (a.size() == b.size()){
		while (a.size()){
			if (a[0]>b[0]){
				return 1;
			}
			else{
				if (a[0] < b[0]){
					return -1;
				}
			}

			if ((a.size() == 1)&&(a[0] == b[0])) {
					return 0;
			}
			a.erase(0, 1);
			b.erase(0, 1);
		}
	}
}

int main()
{
	string a, b, znak;
	cin >> a >> znak >> b;

	if ((znak == "==") && (wieksza(a, b) == 0)){
		cout << "TAK" << endl;
		return 0;
	}

	if ((znak == "!=") && (wieksza(a, b) != 0)){
		cout << "TAK" << endl;
		return 0;
	}

	if ((znak == ">") && (wieksza(a, b) == 1)){
		cout << "TAK" << endl;
		return 0;
	}

	if ((znak == "<") && (wieksza(a, b) == -1)){
		cout << "TAK" << endl;
		return 0;
	}

	if ((znak == ">=") && (wieksza(a, b) > -1)){
		cout << "TAK" << endl;
		return 0;
	}

	if ((znak == "<=") && (wieksza(a, b) < 1)){
		cout << "TAK" << endl;
		return 0;
	}
	cout << "NIE" << endl;
}
