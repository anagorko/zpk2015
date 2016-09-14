#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Word
{
public:
	string PolishWord;
	string EnglishWord;
	int Rank;
	Word(string polish, string english, int rank)
	{
		PolishWord = polish;
		EnglishWord = english;
		Rank = rank;
	}

};

class WordRegistry 
{
public:
	vector<Word> words;
	void addWord(Word word) 
	{
		load();
		words.push_back(word);
	}

	void save()
	{
		ofstream file("slowa.txt");
		for (int i = 0; i < words.size(); i++)
		{
			file << words[i].PolishWord << endl << words[i].EnglishWord << endl << words[i].Rank << endl;
		}
	}
	void load()
	{
		words.clear();
		string line;
		ifstream myfile("slowa.txt");
		vector<string> lineData;
		if (!myfile) 
		{
			system("cls");
			cout << "Brak słow, prosze jakies dodac." << endl;
			system("pause");
		}
		else
		{
			while (getline(myfile, line))
			{
				lineData.push_back(line);
			}
			for (int i = 0; i < lineData.size(); i++)
			{
				string polish, english;
				int rank;
				polish = lineData[i];
				i++;
				english = lineData[i];
				i++;
				istringstream iss(lineData[i]);
				iss >> rank;
				Word w(polish, english, rank);
				words.push_back(w);
			}
		}
	}
		
	void show_words()
	{
		load();
		for (Word& w : words)
		{
			cout << w.PolishWord << " - " << w.EnglishWord << endl;
		}
	}

	void polish_english()
	{
		ifstream myfile("slowa.txt");
		if (myfile)
		{
			system("cls");
			vector<Word> selected = select();
			srand(time(NULL));
			int i = rand() % selected.size();

			cout << selected[i].PolishWord << endl;
			system("pause");
			cout << selected[i].EnglishWord << endl;
			system("pause");
			rate(selected[i].PolishWord);
			save();
		}
		
	}

	void english_polish()
	{
		ifstream myfile("slowa.txt");
		if (myfile)
		{
			system("cls");
			vector<Word> selected = select();
			srand(time(NULL));
			int i = rand() % selected.size();
			system("cls");
			cout << selected[i].EnglishWord << endl;
			system("pause");
			cout << selected[i].PolishWord << endl;
			system("pause");
			rate(selected[i].PolishWord);
			save();
		}
		
	}

	void rate(string word)
	{
		for (int i = 0; i < words.size(); i++)
		{
			if (words[i].PolishWord == word)
			{
				cout << "Ocen znajomosc slowa w skali od 1 do 5." << endl;
				int rank;
				cin >> rank;
				while (rank < 1 || rank > 5 || !cin)
				{
					cin.clear();
					cin.ignore();
					cout << "Podana wartosc jest nieprawidlowa." << endl;
					cout << "Prosze podac wartosc od 1 do 5." << endl;
					cin >> rank;					
				}
				words[i].Rank = rank;
				break;
			}
		}
	}

	vector<Word> select()
	{
		load();
		srand(time(NULL));
		vector<Word> rankWords;
		int rank = 0;
		int j = 0;
		while (rankWords.size() == 0)
		{
			j = rand() % 100;
			if (j <= 40)
				rank = rand() % 1;
			else if (j > 40 && j <= 60)
				rank = 2;
			else if (j > 60 && j <= 78)
				rank = 3;
			else if (j > 78 && j <= 92)
				rank = 4;
			else
				rank = 5;
			for (int i = 0; i < words.size(); i++)
			{
				if (rank == words[i].Rank)
				{
					Word w(words[i].PolishWord, words[i].EnglishWord, words[i].Rank);
					rankWords.push_back(w);
				}

			}
			
		}
		return rankWords;
	}

	static WordRegistry& getInstance() {
		static WordRegistry registry;
		return registry;
	}
};

int main() {

	system("COLOR F0");
	system("title FISZKI");
	system("cls");

	for (int star = 0; star < 80; star++)
		cout << "_";
	cout << "" << setw(50) << "FISZKI :" << setw(30) << "";

	for (int star = 0; star < 80; star++)
		cout << "_";
	cout << endl;
	cout << endl;
	cout << "Wybierz opcje" << endl;
	cout << endl;
	cout << "1. Dodaj slowo." << endl;
	cout << "2. Polski - Angielski." << endl;
	cout << "3. Angielski - Polski." << endl;
	cout << "4. Pokaz liste wszystkich slow." << endl;
	cout << "5. Wyjdź." << endl;

	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		system("cls");
		string polish, english;
		cout << "Wprowadz polskie slowo:" << endl;
		cin >> polish;
		cout << "Wprowadz angielskie slowo:" << endl;
		cin >> english;
		Word w(polish, english, 0);
		WordRegistry::getInstance().addWord(w);
		WordRegistry::getInstance().save();

		system("pause");
		main();
	}
		break;
	case 2:
		system("cls"); 
		char esc;
		do
		{
			WordRegistry::getInstance().load();
			WordRegistry::getInstance().polish_english();
			cout << "Czy chcesz grac dalej? [y/n]" << endl;
			cin >> esc;
		} 
		while (esc != 'n');
		
		main();
		break;
	case 3:
		system("cls");
		while (esc != 'n')
		{
			WordRegistry::getInstance().load();
			WordRegistry::getInstance().english_polish();
			cout << "Czy chcesz grac dalej? [y/n]" << endl;
			cin >> esc;
		}

		main();
		break;
	case 4:
		system("cls");
		WordRegistry::getInstance().show_words();
		system("pause");
		main();
		break;
	case 5:
		exit;
	}
	
}
