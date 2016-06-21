#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include <cstdlib>

/*
INSTRUKCJA
ruch -> strza³ka w górê LUB lewy przycisk myszki
wyjœcie -> ESC

na podstawie materia³ów z przedmiotu Zaawansowane programowanie komputerowe (WNE UW)
oraz http://fixbyproximity.com/2d-game-development-course/
*/


using namespace std;

const int screen_w = 800;   // szerokosc ekranu (screen width)
const int screen_h = 500;    // wysokosc ekranu (screen height)
bool done = false;

const float FPS = 60;       // Frames Per Second


int main()
{
	int pipeWidth = 0;      //szerokoœæ rury
	int pipeHeight = 0;     //d³ugoœæ rury
	int pipeX = 300;        //zmienna przechowuj¹ca obecn¹ pozycjê w poziomie rury
    const int birdX = 40;       // ptak siê nie przesuwa, jest na sta³ej pozycji w poziomie
    int birdY = screen_h / 3;   // wysokoœæ, na której znajduje siê ptak
    srand(time(NULL));

    int los[1000];                  //zmienna pomocnicza losuj¹ca wysokoœæ rury
     for(int i=0; i<1000; i++)
            los[i] =  -3*(rand()%100);

    int wynik=0;          //zmienna przechowuj¹ca wynik gracza, wypisywany do konsoli
    int counting=0;

	//allegro zmienne
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *image = NULL;
	ALLEGRO_BITMAP *imageBird = NULL;
    ALLEGRO_BITMAP *imagePipe = NULL;
    ALLEGRO_TIMER *timer = NULL;

	//program init
	 if(!al_init()) {
        cerr << "B³¹d podczas inicjalizacji allegro." << endl;
        return -1;
    }

    if (!al_init_primitives_addon()) {
        cerr << "B³¹d podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }

    if(!al_init_image_addon()) {
        cerr << "B³¹d podczas inicjalizacji dodatku 'image'." << endl;
        return -1;
    }

    if(!al_install_keyboard()) {
        cerr << "B³¹d podczas inicjalizacji klawiatury." << endl;
        return -1;
    }

        if(!al_install_mouse()) {
        cerr << "B³¹d podczas inicjalizacji myszki." << endl;
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        cerr << "B³¹d podczas inicjalizacji zegara." << endl;
        return -1;
    }

    display = al_create_display(screen_w, screen_h);
    if(!display) {
        cerr << "B³¹d podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        cerr << "B³¹d podczas inicjalizacji kolejki zdarzeñ." << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }


	//addon init
	al_init_primitives_addon();
    al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();

	image = al_load_bitmap("obrazki/background.png");
    imageBird = al_load_bitmap("obrazki/birdy.png");
    imagePipe = al_load_bitmap("obrazki/pipe.png");
    pipeWidth =  al_get_bitmap_width(imagePipe);
	pipeHeight = al_get_bitmap_height(imagePipe);
	event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);

	while(!done)
	{
	    counting++;
	 	ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

       if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            birdY += 2;
            pipeX -= 2;

            for(int n=0; n<1000; n++)
            {
                if (birdX==pipeX+(150*n))
                wynik++;
            }

             if (birdY>=screen_h)
             {
                done = true;
				break;
             }

        }

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
            case ALLEGRO_KEY_UP:
				birdY -= screen_h/10;
                al_draw_bitmap(imageBird, birdX, birdY, 0);
			}

		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1)
				{
                birdY -= screen_h/10;
                al_draw_bitmap(imageBird, birdX, birdY, 0);
                }

		}

		al_draw_scaled_bitmap(image,0, 0, screen_w, screen_h, 0, 0, screen_w, screen_h, 0);
		al_draw_bitmap(imageBird,birdX, birdY, 0);
	//	al_draw_rotated_bitmap(imagePipe, 5, 10, screen_w / 2, screen_h / 2, degree * 3.14159 / 180, 0);

        for(int n=0; n<1000; n++)
        {
            al_draw_scaled_bitmap(imagePipe,0,0, pipeWidth, pipeHeight,pipeX+(150*n), los[n], 50, 900, 0);
           /* if((pipeX+(150*n)==birdX )&& (birdY >= (los[n]+pipeHeight/2)+50 || birdY <=(los[n]+pipeHeight/2)-300))
                     {
                        done = true;
                        break;
                     }*/
        }
        al_flip_display();
    }

    al_destroy_bitmap(imagePipe);
	al_destroy_bitmap(imageBird);
	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

cout << "koniec" << endl;
cout << "twój wynik: " << wynik << endl;
	return 0;
}

