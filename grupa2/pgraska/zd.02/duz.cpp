#include <iostream>
#include <string>
using namespace std;


string porownanie(string a, string b) {

	string l, s, p;
	if (a.length() > b.length())
		return "l";
	else if (a.length() < b.length())
		return "p";
	else if (a.length() == b.length())
		return "r";
	else {
		for (int i = 0; i < a.length(); i++)
		{
			if (a[i] > b[i])
				return "l";
			else if (a[i] < b[i])
				return "p";
		}
	}

}


int main() {

	string a, znak, b;

	cout << "Podaj pierwsza liczbe" << endl;
	cin >> a;
	cout << "Podaj znak" << endl;
	cin >> znak;
	cout << "Podaj druga liczbe" << endl;
	cin >> b;

	cout << endl;
	cout << "Podano: " << a << " " << znak << " " << b << endl;



	if (znak == "==") {
		if(porownanie(a,b) == "r")
			cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
	}


	else if (znak == "!=") {
		if (porownanie(a, b) == "r")
			cout << "NIE" << endl;
		else
			cout << "TAK" << endl;
	}


	else if (znak == "<") {
		if (porownanie(a, b) == "p")
			cout << "TAK" << endl;
		else
			cout << "NIE" << endl;
	}


	else if (znak == ">") {
		if (porownanie(a, b) == "l")
			cout << "TAK" << endl;
		else
			cout << "NIE" << endl;
	}


	else if (znak == "<=") {
		if (porownanie(a, b) == "r" || porownanie(a,b) == "p")
			cout << "TAK" << endl;
		else
			cout << "NIE" << endl;
	}


	else if (znak == ">=") {
		if (porownanie(a, b) == "r" || porownanie(a,b) == "l")
			cout << "TAK" << endl;
		else
			cout << "NIE" << endl;
	}

	system("pause");
	cin.get();
	return 0;
}
