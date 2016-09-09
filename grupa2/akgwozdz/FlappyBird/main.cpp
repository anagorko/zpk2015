#include <iostream>
#include <string>
#include <sstream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "board.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_FONT *font;
ALLEGRO_TIMER *timer = NULL;

void init_allegro() {
    // zainicjalizuj wysswietlacz
    display = NULL;
    al_init();
    al_init_primitives_addon();
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(WIDTH, HEIGHT);

    // zainicjalizuj kolejke zdarzen z klawiatury
    al_install_keyboard();
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // zainicjalizuj timer
    timer = al_create_timer(0.03);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    // zainicjalizuj czcionke
    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_ttf_font("arial.ttf",72,0 );
}

void paint(Board* board) {
    al_clear_to_color(al_map_rgb(153,217,234));

    // rysowanie przeszkód
    for(int i=0; i<4; i++) {
        Obstacle *o = board -> obstacles[i];
        al_draw_line(o->x, 0, o->x, o->up, al_map_rgb(136,0,21), 4);
        al_draw_line(o->x, o->down, o->x, HEIGHT, al_map_rgb(136,0,21), 4);
    }

    // rysowanie ptaka
    al_draw_line(15, board -> bird -> y - 5, 15, board -> bird -> y + 5, al_map_rgb(255,255,0), 10);

    al_flip_display();
}

void print_rules() {
    al_draw_text(font, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2 - 100, ALLEGRO_ALIGN_CENTRE, "Przycisk - START");
    al_draw_text(font, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Escape - WYJŚCIE");
    al_flip_display();
}

void draw_points(int points) {
    ostringstream stream;
    stream << points;
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH - 100, HEIGHT - 80, ALLEGRO_ALIGN_CENTRE, stream.str().c_str());
    al_flip_display();
}

bool wait_for_any_key_or_exit() {
    ALLEGRO_EVENT ev;
    while(true) {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                // wyjscie
                return false;
            }
            // nie-wyjscie
            return true;
        }
    }
}

void play_game() {
    Board* board = new Board(WIDTH, HEIGHT);
    paint(board);
    wait_for_any_key_or_exit();

    int points = 0;
    bool speedIncreased = false;
    ALLEGRO_EVENT ev;
    while(true) {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_CHAR) {
            // nacisniety przycisk - zwieksz predkosc
            if(speedIncreased == true) {
                // zwieksz predkosc tylko raz pomiedzy zdarzeniami z timera
                continue;
            }
            board -> increase_bird_v();
            speedIncreased = true;
        }

        // tylko po timerze przejdz do nastepnej klatki
        if(ev.type != ALLEGRO_EVENT_TIMER) {
            continue;
        }

        speedIncreased = false;
        int addedPoint = board -> move_objects();
        points += addedPoint;
        if(board -> check_collision()) {
            // koniec gry, jezeli jest kolizja
            break;
        }
        paint(board);
        draw_points(points);
    }
}

int main()
{
    init_allegro();

    print_rules();

    while(wait_for_any_key_or_exit()) {
        play_game();
        print_rules();
    }

    al_destroy_display(display);
    return 0;
}
