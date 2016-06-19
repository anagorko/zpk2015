#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "mrowka.h"

using namespace Mrowka;
using namespace std;




int main(int argc, char **argv){

    int rozmiar = 80;
    int ileKolorow = 2;
    int szer = 800;
    int wys = 600;
    int FPS = 60;
    vector <mrowa> Mrowy;
    vector <pole> NieBiale;

    //zmienne do petli
    bool done = false;
    bool redraw = true;



    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    al_init();
    if(!al_init())
        return -1;

    display = al_create_display(szer, wys); //utworzenie wyswietlacza

    if(!display)
        return -1;

    //instalacja addon—w
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_mouse();

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));



    al_set_window_title(display , "Mrowka Langtona 2016");
    al_start_timer(timer);
    Mrowy.clear();
    NieBiale.clear();
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {

            ALLEGRO_MOUSE_STATE klawisz;
            al_get_mouse_state(&klawisz);

            if(klawisz.buttons & 1)
                dodajMrowke(Mrowy, ev.mouse.x, ev.mouse.y);
            else if(klawisz.buttons & 2)
                dodajPole

        }




    }






}

