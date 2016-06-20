#include <iostream>
#include <conio.h>  //getch()
#include<cstdlib>  //system("cls")
#include <stdlib.h>
#include<time.h>  //srand(time(NULL))
#include<windows.h> //sleep()



using namespace std;

int szerokosc, wysokosc, szybkosc;
int gora, dol, lewo, prawo;
int wspolrzednaXweza, wspolrzednaYweza;
int wspolrzednaXjedzenie, wspolrzednaYjedzenie;
int klawisz;
int dlugosc=4, historiaWspolrzednejX[10000], historiaWspolrzednejY[10000];
int ile=0;
char waz=219, jedzonko=176, prawydolnyrog=188, prawygornyrog=187, lewygornyrog=201, lewydolnyrog=200, poziomo=205, pionowo=186;
char kierunek='p'; //p-prawo, l-lewo, g-gora, d-dol

char pole[35][35];
/*pole[0][0], pole[1][0], pole[2][0],...pole[34][0]
pole[0][1], pole[1][1], pole[2][1],...
pole[0][2], pole[1][2], pole[2][2],...
.
.
.
pole[0][34]                            pole[34][34]
*/

//p-pole jest puste w-na polu znajduje się wąż, j- jedzenie

void idzdoxy (int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X=x;
    dwPos.Y=y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}


int podstaw20sz (int &x)
{
    cout <<"Szerokosc planszy 5-35 [20]:\n" << endl;
     cin >> x;
     if (x<5 || x>35) x = 20;
}

int podstaw20wys (int &x)
{
    cout <<"Wysokosc planszy 5-35 [20]:\n" << endl;
     cin >> x;
     if (x<5 || x>35) x = 20;
}
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 228);
    cout << "\n\n:: TO JEST WONSZ!! ::\n\n" << endl;
    cout << "\n\:: TRZEBA BYC DOBRYM DLA WONSZA!! ::\n\n" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 46);
    cout << ":USTAW PLANSZE:\n" << endl;
    cout << "Szerokosc planszy 5-35 [20]:\n" << endl;
    cin >> szerokosc;
    if (szerokosc<5 || szerokosc>35) podstaw20sz(szerokosc);


    cout << "\nWysokosc planszy 5-35 [20]:\n" << endl;
    cin >> wysokosc;
    if (wysokosc<5 || wysokosc>35) podstaw20wys
        (wysokosc);

    cout << "\n\nUSTAW SPEEEED 1-100 [MAX 100]:" << endl;
    cin >> szybkosc;
    if ( szybkosc<1) szybkosc=1;
    if ( szybkosc>100) szybkosc=100;

    cout << "\n\n:: USTAW KLAWISZE ::\n\n" << endl;
    cout << "UP!" << endl;
    gora=getch();
    if(gora==224) if(kierunek!='d') gora=gora+getch();
    if(gora==0) gora=gora-getch();


    cout << "DOWN!!" << endl;
    dol=getch();
    if(dol==224) dol=dol+getch();
    if(dol==0) dol=dol-getch();

    cout << "LEFT!!!" << endl;
    lewo=getch();
    if(lewo==224) lewo=lewo+getch();
    if(lewo==0) lewo=lewo-getch();

    cout << "RIGHT!!!!" << endl;
    prawo=getch();
    if(prawo==224) prawo=prawo+getch();
    if(prawo==0) prawo=prawo-getch();
        cout << "\n\n 5!" << endl;
        Sleep(500);
        cout << "\n\n 4!" << endl;
        Sleep(500);
        cout << "\n\n 3!" << endl;
        Sleep(500);
        cout << "\n\n 2!" << endl;
        Sleep(500);
        cout << "\n\n 1!" << endl;
        Sleep(500);

//nadajemy wartosci 'p' tablicy pole
for(int i=0; i<wysokosc; i++)
{
    for(int j=0; j<szerokosc; j++)
    {
        pole[j][i]='p';
    }
}

srand(time(NULL)); //generator losowania


//losowanie pola dla weza
wspolrzednaXweza=rand()%szerokosc;
wspolrzednaYweza=rand()%wysokosc;

pole[wspolrzednaXweza][wspolrzednaYweza]='w';


//losowanie pola dla jedzenia
do{
    wspolrzednaXjedzenie=rand()%szerokosc;
    wspolrzednaYjedzenie=rand()%wysokosc;

}while (pole[wspolrzednaXjedzenie][wspolrzednaYjedzenie] !='p');

pole[wspolrzednaXjedzenie][wspolrzednaYjedzenie]='j';

system("CLS"); //czyszczenie ekranu

//rozpoczecie gry
for(;;)
{
    ile++;
    historiaWspolrzednejX[ile]=wspolrzednaXweza;
    historiaWspolrzednejY[ile]=wspolrzednaYweza;



//rysowanie planszy

idzdoxy(0,0); //wraca na poczatek



//górna ramka
cout << lewygornyrog;
for (int i=0; i<szerokosc; i++ /* i=i+1 i+=1 */)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << poziomo << poziomo;
    }
cout << prawygornyrog;
for (int i=0; i<wysokosc; i++)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << endl << pionowo; //lewa ramka
    for(int j=0; j<szerokosc; j++)
    {
       if (pole[j][i]=='p') cout << "  ";
       if (pole[j][i]=='w')
       {
           SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
           cout << waz << waz;
       }
       if (pole[j][i]=='j')
       {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << jedzonko << jedzonko;
       }

    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << pionowo; //prawa ramka
}

cout << endl;
//dolna ramka
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
cout <<lewydolnyrog;

    for (int i=0; i<szerokosc; i++ /* i=i+1 i+=1 */)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << poziomo << poziomo;

}
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
cout << prawydolnyrog;
Sleep(1/szybkosc); //czekaj
    if(kbhit()) //jesli zostanie nacisniety jakis klawisz
    {
        klawisz=getch();
        if(klawisz==224)klawisz+=getch();
        if(klawisz==0)klawisz-=getch();

        if(klawisz==gora)kierunek='g';
        if(klawisz==dol)kierunek='d';
        if(klawisz==lewo)kierunek='l';
        if(klawisz==prawo)kierunek='p';
    }




if(kierunek=='d') wspolrzednaYweza++;
if(kierunek=='g') wspolrzednaYweza--;
if(kierunek=='l') wspolrzednaXweza--;
if(kierunek=='p') wspolrzednaXweza++;

//przechodzenie przez sciany
if(wspolrzednaXweza==szerokosc) wspolrzednaXweza=0;
if(wspolrzednaXweza==-1) wspolrzednaXweza=szerokosc -1;

if(wspolrzednaYweza==wysokosc) wspolrzednaYweza=0;
if(wspolrzednaYweza==-1) wspolrzednaYweza=wysokosc -1;

//co jesli zderzy się z samym sobą
if(pole[wspolrzednaXweza][wspolrzednaYweza]=='w')
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    if(dlugosc<=5){cout << endl <<"\nFATALNIE!\n\nZdobyles " << dlugosc-4 << " wonszopunktuf! :) ";}
    if(dlugosc>5&&dlugosc<=10){cout << endl <<"\nSREDNIO!\n\nZdobyles " << dlugosc-4 << " wonszopunktuf! :) ";}
    if(dlugosc>10&&dlugosc<=25){cout << endl <<"\nNIEZLE!\n\nZdobyles " << dlugosc-4 << " wonszopunktuf! :) ";}
    if(dlugosc>25){cout << endl <<"\nMISZCZ!\n\nZdobyles " << dlugosc-4 << " wonszopunktuf! :) ";}
    break;
}


//co jesli zje jedzenie
if(pole[wspolrzednaXweza][wspolrzednaYweza]=='j')
{
    dlugosc++;
    //losowanie pola dla jedzenia
    do{
        wspolrzednaXjedzenie=rand()%szerokosc;
        wspolrzednaYjedzenie=rand()%wysokosc;

    }
    while (pole[wspolrzednaXjedzenie][wspolrzednaYjedzenie] !='p');

    pole[wspolrzednaXjedzenie][wspolrzednaYjedzenie]='j';


}
else  //kasowanie ogona
pole[historiaWspolrzednejX[ile-dlugosc]][historiaWspolrzednejY[ile-dlugosc]]='p';




pole[wspolrzednaXweza][wspolrzednaYweza]='w';



}//koniec pętli for(;;)

cout << "\n\n WONSZ UMARL!!" << endl;
Sleep(100);
Sleep(100);
Sleep(100);
Sleep(100);
getch();
    return 0;
}
