#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include <cstdlib>
#include<cmath>

/*
INSTRUKCJA
ruch -> strzalka w góre LUB lewy przycisk myszki
wyjscie -> ESC

na podstawie materialów z przedmiotu Zaawansowane Programowanie Komputerowe (WNE UW)
oraz http://fixbyproximity.com/2d-game-development-course/
*/


using namespace std;

const int screen_w = 800;   // szerokosc ekranu (screen width)
const int screen_h = 500;    // wysokosc ekranu (screen height)
bool done = false;

const float FPS = 60;       // Frames Per Second


int main()
{
    // ZMIENNE DOT. RURY
	int pipeWidth = 0;          // szerokosc wejściowa rury
	int pipeHeight = 0;         // dlugosc wejściowa rury
	float scale = 1.3;          // skala do stworzenia wyswietlanej wielkosci rury

	int pipeX = 300;            // zmienna przechowujaca obecna pozycjê w poziomie rury
	int pipeGap = 180;          // odleglosc między kolejnymi rurami

    srand(time(NULL));
	int pipeHole = 200;         //  wielkość dziury miedzy górna a dolna rura
    int los[1000];              // zmienna pomocnicza losujaca wysokosc rysowania lewego górnego rogu rury
    for(int i=0; i<1000; i++)
            los[i] =  -4*(rand()%100);


	// ZMIENNE DOT. PTAKA
    const int birdX = 40;       // ptak sie nie przesuwa, jest na stalej pozycji w poziomie
    int birdY = screen_h / 3;   // wysokosc, na której początkowo znajduje siê ptak
    int birdWidth = 0;          // szerokosc wejściowa bitmapy z ptakiem
    int birdHeight = 0;         // dlugosc wejściowa bitmapy z ptakiem
	int birdWidthDest =36;      // szerokosc docelowa ptaka, do wyświetlenia
	int birdHeightDest = 28;    // długosc docelowa ptaka, do wyświetlenia

    // POZOSTAŁE ZMIENNE
    int wynik=0;          //zmienna przechowuj¹ca wynik gracza, wypisywany do konsoli

	//allegro zmienne
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *image = NULL;
	ALLEGRO_BITMAP *imageBird = NULL;
    ALLEGRO_BITMAP *imagePipe = NULL;
    ALLEGRO_TIMER *timer = NULL;

	//program init
	 if(!al_init()) {
        cerr << "Blad podczas inicjalizacji allegro." << endl;
        return -1;
    }

    if (!al_init_primitives_addon()) {
        cerr << "Blad podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }

    if(!al_init_image_addon()) {
        cerr << "Blad podczas inicjalizacji dodatku 'image'." << endl;
        return -1;
    }

    if(!al_install_keyboard()) {
        cerr << "Blad podczas inicjalizacji klawiatury." << endl;
        return -1;
    }

        if(!al_install_mouse()) {
        cerr << "Blad podczas inicjalizacji myszki." << endl;
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        cerr << "Blad podczas inicjalizacji zegara." << endl;
        return -1;
    }

    display = al_create_display(screen_w, screen_h);
    if(!display) {
        cerr << "Blad podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        cerr << "Blad podczas inicjalizacji kolejki zdarzeñ." << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }


	//addon init
	al_init_primitives_addon();
    al_init_font_addon();
	al_init_ttf_addon();
    al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();

    ALLEGRO_FONT *napisy = al_load_font("arial.ttf", 24, 0);
	image = al_load_bitmap("obrazki/background.png");
    imageBird = al_load_bitmap("obrazki/birdy.png");
    imagePipe = al_load_bitmap("obrazki/pipe0.png");
    pipeWidth =  al_get_bitmap_width(imagePipe);
	pipeHeight = al_get_bitmap_height(imagePipe);
	birdWidth = al_get_bitmap_width(imageBird);
	birdHeight = al_get_bitmap_width(imageBird);
	event_queue = al_create_event_queue();

    int pipeWidthDest = scale*pipeWidth;     // szerokosc docelowa rury, do wyświetlenia
	int pipeHeightDest = scale*pipeHeight;   // długosc docelowa rury, do wyświetlenia

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);

	while(!done)
	{
	 	ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

       if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            birdY += 2;
            pipeX -= 2;

            for(int n=0; n<1000; n++)
            {
                if (birdX==pipeX+(pipeGap*n))               // punkt za kazda pokonana rure
                wynik++;
            }

             if (birdY>=screen_h - birdHeightDest+10)        // koniec gry jesli ptak uderzy w ziemię, dodane 10 w celu lepszego dopasowania
             {
                done = true;
				break;
             }

        }

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:                // zakoncz gre, jesli ESC zostanie wcisniete
				done = true;
				break;
            case ALLEGRO_KEY_UP:                    // ptak skacze do góry, jeśli strzalka w góre wcisnieta
				birdY -= screen_h/10;
                //al_draw_bitmap(imageBird, birdX, birdY, 0);
                al_draw_scaled_bitmap(imageBird,0,0, birdWidth, birdHeight,birdX, birdY, birdWidthDest, birdHeightDest, 0);
			}

		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1)                  // ptak skacze do góry, jeśli lewy klawisz myszki klikniety
				{
                birdY -= screen_h/10;
                al_draw_scaled_bitmap(imageBird,0,0, birdWidth, birdHeight,birdX, birdY, birdWidthDest, birdHeightDest, 0);
                }

		}

		al_draw_scaled_bitmap(image,0, 0, screen_w, screen_h, 0, 0, screen_w, screen_h, 0); //rysowanie planszy
		al_draw_scaled_bitmap(imageBird,0,0, birdWidth, birdHeight,birdX, birdY, birdWidthDest, birdHeightDest, 0); //rysowanie ptaka

// petla rysujaca rury
        for(int n=0; n<1000; n++)
        {
            al_draw_scaled_bitmap(imagePipe, 0, 0, pipeWidth, pipeHeight,pipeX+(pipeGap*n), los[n], pipeWidthDest, pipeHeightDest, 0);
            al_draw_scaled_rotated_bitmap(imagePipe, 0, 0, pipeX+(pipeGap*n)+pipeWidthDest, los[n] + 2*pipeHeightDest + pipeHole, scale, scale, M_PI , 0);

           if((birdX>pipeX+(pipeGap*n) && birdX<pipeX+(pipeGap*n)+pipeWidthDest) || (birdX+birdWidthDest>pipeX+(pipeGap*n) && birdX+birdWidthDest<pipeX+(pipeGap*n)+pipeWidthDest))
                 {
                 if(birdY >= los[n]+pipeHeightDest+pipeHole-birdHeightDest+10 || birdY <=los[n]+pipeHeightDest)
                     {
                        done = true;
                        break;
                     }
                 }

        }
// wypisywanie wyniku
        al_draw_textf(napisy, al_map_rgb(255, 0, 255), screen_w, 0, ALLEGRO_ALIGN_RIGHT, "Wynik = %i", wynik);

        al_flip_display();
    }
    
//usuwanie obiektów
    al_destroy_font(napisy);
    al_destroy_bitmap(imagePipe);
    al_destroy_bitmap(imageBird);
    al_destroy_bitmap(image);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);						

cout << "YOU LOST!" << endl;
cout << "your score: " << wynik << endl;
	return 0;
}

