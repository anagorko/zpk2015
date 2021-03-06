#include <iostream>
#include <string>
#include <cctype>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>            // do rysowania komorek - prostokatow
#include <cstdlib>                                  // srand
#include <ctime>                                    // time(NULL)

#include "Gra.h"
#include "Amazing.h"
#include "Amoeba.h"
#include "Coral.h"
#include "HighLife.h"
#include "TrzyStany.h"
#include "Artist.h"
#include "WireWorld.h"
#include "Wlasna.h"
#include "wczytywanie.h"
#include "Wlasna2.h"



int main()
{
    srand(time(NULL));                                          // uruchimienie generatora liczb pseudolosowych w zaleznosci od aktualnego czasu

    ALLEGRO_DISPLAY *display = NULL;                            // wskaznik do ekranu gry
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;                    // wskaznik do kolejki zdarzen
    ALLEGRO_KEYBOARD_STATE klawiatura;                          // zmienna stanu klawiatury
    ALLEGRO_TIMER *zegar;


    const int sizeField = 10;                                   // rozmiar pola

    if(!al_init())
    {
        std::cout << "Nie moze uruchomic biblioteki Allegro" << std::endl;
        return -1;
    }

    if(!al_init_primitives_addon())             // do rysowania kwadratow
    {
        std::cout << "Nie mozna zainicjowac biblioteki prymitywow" << std::endl;
        return -1;
    }

    if(!al_install_keyboard())
    {
        cout << "Nie mozna zainicjowac klawiatury" << endl;
        return -1;
    }

    cout << "Gra w zycie" << endl;

    const int liczba_cykli = wczytajWartosc(5, 100, "Podaj liczbe cykli z przedzialu [5; 100]:");
    const int szerokosc_okna = wczytajWartosc(10, 40, "Podaj szerokosc okna (liczba komorek) [10; 40]:");
    const int wysokosc_okna = wczytajWartosc(10, 40, "Podaj wysokosc okna (liczba komorek) [10; 40]:");
    const double czestotliwosc = wczytajWartosc(0.1, 2.0, "Podaj czestotoliwosc taktowania w sekundach z przedzialu [0.1; 2.0] w sekundach:");

    cout << "Wybierz zestaw regul gry sposrod\n"
    << "1 - Amazing\n"
    << "2 - Amoeba\n"
    << "3 - Coral\n"
    << "4 - Highlife\n"
    << "5 - 3 stany\n"
    << "6 - Artist\n"
    << "7 - Wired World\n"
    << "8 - Dowolna liczba stanow\n"
    << "9 - Dowolna liczba stanow z wybieranym rodzajem zliczanych sasiadow" << endl;

    Gra *gra;                                                   // wskaznik do gry
    switch(wczytajWartosc(1, 9, "Zestaw regul: "))
    {
    case 1:
        gra = new Amazing(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;
    case 2:
        gra = new Amoeba(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;
    case 3:
        gra = new Coral(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;
    case 4:
        gra = new HighLife(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;

    case 5:
        gra = new TrzyStany(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;

    case 6:
        gra = new Artist(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;

    case 7:
        gra = new WireWorld(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;

    case 8:
        gra = new Wlasna(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;

    case 9:
        gra = new Wlasna2(szerokosc_okna, wysokosc_okna, liczba_cykli);
        break;
    }

    display = al_create_display(szerokosc_okna * sizeField, wysokosc_okna * sizeField);
    if(!display)
    {
        std::cout << "Nie moze utworzyc ekranu" << std::endl;
        delete gra;
        return -1;
    }

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_window_title(display, "  Gra w Zycie  ");

    al_set_target_bitmap(al_get_backbuffer(display));

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        cout << "Nie mozna utworzyc kolejki zdarzen!" << endl;
        al_destroy_display(display);
        delete gra;
        return -1;
    }

    zegar = al_create_timer(czestotliwosc);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(zegar));

    ALLEGRO_EVENT ev;                                           // zdarzenie
    al_start_timer(zegar);

    gra->rysuj();
    for(int i = 0; i < liczba_cykli; ++i)
    {
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            al_get_keyboard_state(&klawiatura);
            if(al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))        // przerwanie wcisnieciem klawisza ESCAPE
                break;
        }


        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            gra->wykonajCykl();
            gra->rysuj();
            gra->print();
        }
    }
    al_stop_timer(zegar);

    delete gra;

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(zegar);

    return 0;
}

