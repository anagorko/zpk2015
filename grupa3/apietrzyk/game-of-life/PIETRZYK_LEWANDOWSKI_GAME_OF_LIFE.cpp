#include<iostream>
#include <fstream>
#include <string>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <string>

const int w = 800; //wysokosc ekranu
const int h = 800; //szerokosc ekranu

int **Tablica;
int **TablicaBufor;

class Plansza
{
	public:
    Plansza() {
        w;
        h;
    };
    Plansza(string plik_plansza); //wczytywanie planysz z pliku
    int **Tablica;
    int **TablicaBufor;
    int WPlanszy=800;
    int HPlanszy=800;
    int WPixel=5; // element skalujacy
    int HPixel=5; // element skalujacy
	void UtworzTablice(); //pusty konstruktor
	void LosoweZycia(); //zapelnia plansze w sposob losowy
	bool DodajZycie(int x,int y); // dodaj żywą komórkę
	int LiczSasiadow(int x,int y); //policz sasiadow dla elementu (x,y)
	void PrzeliczPlansze();
	int PrzeliczPlanszeUzytkownik(int tab_umier[], int tab_zywy[], int ile_umier, int ile_zywy);
	void Obraz();
	bool CzyZywa(int x, int y);
};

void Plansza::UtworzTablice() // tworzenie dwoch tablic - normalnej i służącej do buforowania
{
	Tablica=new int*[w];
	TablicaBufor=new int*[w];
	for(int i=0;i<w;i++)
	{
		Tablica[i]=new int[h];
		TablicaBufor[i]=new int[h];
		for(int j=0;j<h;j++)
		{
			Tablica[i][j]=0;
			TablicaBufor[i][j]=0;
		}
	}
}

Plansza::Plansza(string plik_plansza) //wczytywanie schematu z pliku
{
    ifstream plik;
    plik.open( plik_plansza.c_str() );
    if( !plik.good() )
    {
        cout << "Plik niepoprawny" << endl;
    };

    plik>>WPlanszy>>HPlanszy;
    int WSrodek=floor((w-WPlanszy)/(2*WPixel));
    int HSrodek=floor((h-HPlanszy)/(2*HPixel));

    int j = WSrodek; // aby wczytane komórki były na sordku planszy
    int i = HSrodek;
    UtworzTablice();
        for(j;j<WSrodek+WPlanszy;j++){
            for(i;i<HSrodek+HPlanszy;i++)
            {
                plik>>Tablica[i][j];
                TablicaBufor[i][j]=Tablica[i][j];
            }
            i=HSrodek;
        }
    plik.close();
}

bool Plansza::DodajZycie(int x,int y)
{
	if(x<0||y<0||x>=WPlanszy||y>=HPlanszy)
	{
		return false;
	}
	Tablica[x][y]=1;
	return 1;
}

bool Plansza::CzyZywa(int x, int y){
    if (x<0 || x>=w) { return 0; }
    if (y<0 || y>=h) { return 0; }
    else return (Tablica[x][y]==1);
}

int Plansza::LiczSasiadow(int x,int y)
{
int suma=0;

suma =  CzyZywa(x-1,y-1) + CzyZywa(x,y-1) +
        CzyZywa(x+1,y-1) + CzyZywa(x+1,y) +
        CzyZywa(x+1,y+1) + CzyZywa(x,y+1) +
        CzyZywa(x-1,y+1) + CzyZywa(x-1,y);

    return suma;
}

void Plansza::Obraz()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
	for(int j=0;j<h;j++)
		{
		for(int i=0;i<w;i++)
		{
				if(Tablica[i][j]!=0)
				al_draw_pixel( WPixel*i, HPixel*j, al_map_rgb(255,255,255));
		}

		}
    al_flip_display();
    al_rest(2);
}

void Plansza::PrzeliczPlansze(){
    int ile;
    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++) {
            if(Tablica[x][y]==0){
                ile = LiczSasiadow(x,y);
                if(ile==3)
                    TablicaBufor[x][y]=1;
            }

            if(Tablica[x][y]==1){
                ile = LiczSasiadow(x,y);
                if(ile==2 || ile ==3)
                    TablicaBufor[x][y]=1;
                else
                    TablicaBufor[x][y]=0;
            }
        }
    }
    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            Tablica[x][y]=TablicaBufor[x][y];
        }

    }
}

int Plansza::PrzeliczPlanszeUzytkownik(int tab_umier[], int tab_zywy[], int ile_umier, int ile_zywy){ // klasa, która działa dla funkcji generowanych przez uzytkownika
    int ile;
    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++) {
            if(Tablica[x][y]==0){
                ile = LiczSasiadow(x,y);
                for(int j=0; j<ile_zywy;j++){
                    if(ile==tab_zywy[j]) {TablicaBufor[x][y]=1; break;}
                }

            }

            if(Tablica[x][y]==1){
                ile = LiczSasiadow(x,y);
                for(int j=0; j<ile_umier;j++){
                    if(ile==tab_umier[j]) {TablicaBufor[x][y]=0; break;}
                }
           }
        }
    }
    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            Tablica[x][y]=TablicaBufor[x][y];
        }

    }
}

int main(int, char**)
{
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    ALLEGRO_FONT *title = al_load_font("arialn.ttf", 24, 0);
    ALLEGRO_FONT *body = al_load_font("arialn.ttf", 12, 0);
    ALLEGRO_FONT *counter = al_load_font("arialn.ttf", 20, 0);
    ALLEGRO_FONT *element = al_load_font("arialn.ttf", 10, 0);
    ALLEGRO_FONT *title2 = al_load_font("arialn.ttf", 50, 0);

    ALLEGRO_DISPLAY *display = al_create_display(w, h);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_EVENT ev;
    ALLEGRO_TIMER *timer = al_create_timer(1);
    ALLEGRO_BITMAP* bitmap;

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    Start:

    while (true) {


        al_clear_to_color(al_map_rgb(40, 30, 75));

        al_draw_rectangle(w / 2 - 200, 200, w / 2 + 200, 330, al_map_rgb(255, 255, 255), 5);
        al_draw_text(title2, al_map_rgb(200, 200, 200), w / 2 , 240, ALLEGRO_ALIGN_CENTRE, "GRA O ŻYCIE");

        al_draw_filled_rounded_rectangle(w / 2 - 110, 350, w / 2 + 110, 420, 20, 20, al_map_rgb(0, 0, 0));
        al_draw_text(counter, al_map_rgb(200, 200, 200), w / 2 , 370, ALLEGRO_ALIGN_CENTRE, "SYMULACJA - GÓRA");

        al_draw_filled_rounded_rectangle(w / 2 - 110, 440, w / 2 + 110, 510, 20, 20, al_map_rgb(0, 0, 0));
        al_draw_text(counter, al_map_rgb(200, 200, 200), w / 2 , 460, ALLEGRO_ALIGN_CENTRE, "INFORMACJE - DÓŁ");

        al_draw_filled_rounded_rectangle(w / 2 - 110, 530, w / 2 + 110, 600, 20, 20, al_map_rgb(0, 0, 0));
        al_draw_text(counter, al_map_rgb(200, 200, 200), w / 2 , 550, ALLEGRO_ALIGN_CENTRE, "WYJŚCIE - ESCAPE");

        al_flip_display();

        al_wait_for_event(event_queue, &ev);


        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    goto Symulacja;
                break;

                case ALLEGRO_KEY_DOWN:
                    goto Informacja;
                break;

                case ALLEGRO_KEY_ESCAPE:
                    goto Koniec;
                break;
                }
            }
        }



    Symulacja:

    while (true) {
        al_clear_to_color(al_map_rgb(40, 30, 75));

        al_draw_text(title2, al_map_rgb(200, 200, 200), w / 2 , 120, ALLEGRO_ALIGN_CENTRE, "SYMULACJA");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 250, ALLEGRO_ALIGN_CENTRE, "WCZYTAJ MAPĘ - GÓRA");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 300, ALLEGRO_ALIGN_CENTRE, "GRA UŻYTOWNIKA - DÓŁ");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 450, ALLEGRO_ALIGN_CENTRE, "ESCAPE - WYJŚCIE");

        al_flip_display();
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    goto Wczytaj_mape;
                break;

                case ALLEGRO_KEY_DOWN:
                    goto Gra_uzytkownika;
                break;

                case ALLEGRO_KEY_ESCAPE:
                    goto Koniec;
                break;
                }
            }
    }


    Wczytaj_mape:

        while (true) {

        al_clear_to_color(al_map_rgb(40, 30, 75));

        al_draw_text(title2, al_map_rgb(200, 200, 200), w / 2 , 120, ALLEGRO_ALIGN_CENTRE, "WCZYTAJ PLANSZE");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 250, ALLEGRO_ALIGN_CENTRE, "WCZYTAJ PLANSZE 1 - GÓRA");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 300, ALLEGRO_ALIGN_CENTRE, "WCZYTAJ PLANSZE 2 - DÓŁ");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 350, ALLEGRO_ALIGN_CENTRE, "POWRÓT - LEWO");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 450, ALLEGRO_ALIGN_CENTRE, "ESCAPE - WYJŚCIE");

        al_flip_display();
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    goto Wczytaj_mape1;
                break;

                case ALLEGRO_KEY_DOWN:
                    goto Wczytaj_mape2;
                break;

                case ALLEGRO_KEY_LEFT:
                    goto Symulacja;
                break;

                case ALLEGRO_KEY_ESCAPE:
                    goto Koniec;
                break;
                }
            }
    }

    Wczytaj_mape1:

        while (true) {
        int ileOkresow;
        int odKtorego;

        cout << "Ile okresow ma trwac symulacja?";
        cin>>ileOkresow;
        cout << "Od ktorego okresu chcesz ogladac symulacje?";
        cin>>odKtorego;

        Plansza *p=NULL;
        p=new Plansza("plansza_numer_1.txt");

        for (int i=0; i<=ileOkresow; i++) {
            if(i<odKtorego)
                {
                p->PrzeliczPlansze();
                }
            else{
                p->PrzeliczPlansze();
                p->Obraz();
            }
        };
        goto Symulacja;
    }

    Wczytaj_mape2:

        while (true) {
        int ileOkresow;
        int odKtorego;

        cout << "Ile okresow ma trwac symulacja? ";
        cin>>ileOkresow;
        cout << "Od ktorego okresu chcesz ogladac symulacje? ";
        cin>>odKtorego;

        Plansza *p=NULL;
        p=new Plansza("plansza_numer_2.txt");

        for (int i=0; i<=ileOkresow; i++) {
            if(i<odKtorego)
                {
                p->PrzeliczPlansze();
                }
            else{
                p->PrzeliczPlansze();
                p->Obraz();
            }
        };

        goto Symulacja;
    }

    Gra_uzytkownika:

    while (true) {

        Plansza p;
        p.UtworzTablice();
        p.Obraz();

        int liczba_komorek;
        int WKomorka,Hkomorka;
        cout<<"Jak duzo chcesz dodac zywych komorek? "<<endl;
        cin>>liczba_komorek;
        for(int j=0;j<liczba_komorek;j++)
            {
            cout<<"Podaj wspolrzedne (mozliwe wartosci od 1 do 180) komorki numer: " << j+1 <<endl;
            cin>>WKomorka>>Hkomorka;
            p.DodajZycie(WKomorka,Hkomorka);
            };

        int liczba_umier;
        cout<<"Ile bedzie regul przy, ktorych komorka bedzie umierac? "<<endl;
        cin>>liczba_umier;
        int tablica_umier[liczba_umier];
        for(int j=0;j<liczba_umier;j++)
            {
            cout<<"Podaj liczbe sasiadow przy ktorej komorka umiera. Regula umierania numer: " << j+1 << endl;
            cin>>tablica_umier[j];
            };

        int liczba_zywy;
        cout<<"Ile bedzie regul przy, ktorych komorka bedzie ozywac? "<<endl;
        cin>>liczba_zywy;
        int tablica_zywy[liczba_zywy];
        for(int j=0;j<liczba_zywy;j++)
            {
            cout<<"Podaj liczbe sasiadow przy ktorej komorka ozywa. Regula ozywania numer: " << j+1 <<endl;
            cin>>tablica_zywy[j];
            };

        int ileOkresow;
        int odKtorego;

        cout << "Ile okresow ma trwac symulacja? ";
        cin>>ileOkresow;
        cout << "Od ktorego okresu chcesz ogladac symulacje? ";
        cin>>odKtorego;

        for (int i=0; i<=ileOkresow; i++) {
            if(i<odKtorego)
                {
                p.PrzeliczPlanszeUzytkownik(tablica_umier, tablica_zywy, liczba_umier, liczba_zywy);
                }
            else{
                p.PrzeliczPlanszeUzytkownik(tablica_umier, tablica_zywy, liczba_umier, liczba_zywy);
                p.Obraz();
            }
        };
        goto Symulacja;
    }

    Informacja:

    while (true) {
        al_clear_to_color(al_map_rgb(40, 30, 75));

        al_draw_text(title2, al_map_rgb(200, 200, 200), w / 2 , 120, ALLEGRO_ALIGN_CENTRE, "INFORMACJE");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 200, ALLEGRO_ALIGN_CENTRE, "Po więcej informacji zapraszamy do:");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 240, ALLEGRO_ALIGN_CENTRE, "en.wikipedia.org/wiki/Conway%27s_Game_of_Life");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 500, ALLEGRO_ALIGN_CENTRE, "POWRÓT - GÓRA");
        al_draw_text(title, al_map_rgb(200, 200, 200), w / 2 , 550, ALLEGRO_ALIGN_CENTRE, "ESCAPE - WYJŚCIE");

        al_flip_display();
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    goto Start;
                break;

                case ALLEGRO_KEY_ESCAPE:
                    goto Koniec;
                break;
                }
            }
    }

    Koniec:

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

 return 0;
}

