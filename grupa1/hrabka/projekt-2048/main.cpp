#include <iostream>

#include <string>
#include <sstream> // patch na toString
#include <fstream> // pliki

#include <cstdlib> // string -> int (atoi)

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "board.h"

using namespace std;

const int w = 700;
const int h = 800;

const int margin = 50;
const int field_size = 150;

const int best_score_count = 5;

string filename = "scores.txt";

ALLEGRO_FONT *font;
ALLEGRO_EVENT_QUEUE *event_queue;

// http://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-so-g
namespace patch {
    template < typename T > std::string to_string(const T& n) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

void draw_square(int x, int y, int value) {
    al_draw_line(x+1, y+1, x+field_size, y+1, al_map_rgb(0,0,0), 2);
    al_draw_line(x+field_size, y+1, x+field_size, y+field_size, al_map_rgb(0,0,0), 2);
    al_draw_line(x+field_size, y+field_size, x+1, y+field_size, al_map_rgb(0,0,0), 2);
    al_draw_line(x+1, y+field_size, x+1, y+1, al_map_rgb(0,0,0), 2);

    // draw value inside square if value != -1
    if (value != -1) {
        al_draw_text(font, al_map_rgb(0,0,0), x + field_size/2, y + field_size/4, ALLEGRO_ALIGN_CENTRE, patch::to_string(value).c_str());
    }
}

void draw_board(Board* board) {
    al_clear_to_color(al_map_rgb(255,255,0));
    for(int r=0; r<4; r++) {
        for(int c=0; c<4; c++) {
            draw_square(margin + c*field_size, margin + r*field_size, board -> get_value(r, c));
        }
    }
    al_flip_display();
}

void draw_menu(int selected){
    al_clear_to_color(al_map_rgb(255,255,0));
    if (selected==1){
        al_draw_text(font, al_map_rgb(0,255,0), w/2+0.1, h/2-0.1*h, ALLEGRO_ALIGN_CENTRE, "PLAY");
    }
    else {
        al_draw_text(font, al_map_rgb(0,0,0), w/2+0.1, h/2-0.1*h, ALLEGRO_ALIGN_CENTRE, "PLAY");
    }
    if (selected==2){
         al_draw_text(font, al_map_rgb(0,255,0), w/2+0.1, h/2, ALLEGRO_ALIGN_CENTRE, "SCORES");
    }
    else{
        al_draw_text(font, al_map_rgb(0,0,0), w/2+0.1, h/2, ALLEGRO_ALIGN_CENTRE, "SCORES");
    }
    if (selected==3){
        al_draw_text(font, al_map_rgb(0,255,0), w/2+0.1, h/2+0.1*h, ALLEGRO_ALIGN_CENTRE, "EXIT");
    }
    else{
        al_draw_text(font, al_map_rgb(0,0,0), w/2+0.1, h/2+0.1*h, ALLEGRO_ALIGN_CENTRE, "EXIT");
    }
    al_flip_display();
}

void draw_scores(int* scores) {
    al_clear_to_color(al_map_rgb(255,255,0));
    for(int i=0; i<best_score_count; i++) {
        string text = patch::to_string(i + 1).append(". ").append(patch::to_string(scores[i]));
        al_draw_text(font, al_map_rgb(0,0,0), w/4, 0.1*h + i * h * 0.8/best_score_count, ALLEGRO_ALIGN_LEFT, text.c_str());
    }
    al_flip_display();

    // czekaj na przycisk
    ALLEGRO_EVENT ev;
    while(true) {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            break;
        }
        cout<<"Non key-down event"<<endl;
    }
}

bool check_if_lost(Board* board) {
    if(board->key_left(false)) {
        return false;
    }
    if(board->key_right(false)) {
        return false;
    }
    if(board->key_up(false)) {
        return false;
    }
    if(board->key_down(false)) {
        return false;
    }
    return true;
}

int play_game() {
    Board *board = new Board();
    board -> random_field();
    board -> print();


    draw_board(board);

    bool lost = false;
    while(!lost) {

        ALLEGRO_EVENT ev;

        // czekaj na naciśnięcie klawisza
        al_wait_for_event(event_queue, &ev);
        if(ev.type != ALLEGRO_EVENT_KEY_DOWN) {
        //    cout<<"Other event (not key down): ";
            continue;
        }

        bool board_changed;
        if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            board_changed = board -> key_down();
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
            board_changed = board -> key_up();
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
            board_changed = board -> key_left();
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
            board_changed = board -> key_right();
        } else {
            cout<<"Other key"<<endl;
            continue;
        }

        if(!board_changed) {
            cout<<"No changes on board"<<endl;
            continue;
        }

        // narysuj planszê po ruchu
        draw_board(board);
        //al_rest(1);

        // dodanie losowego pola i
        board->random_field();

        // sprawdzenie koñca gry
        lost = check_if_lost(board);

        draw_board(board);
    }
    cout<<"Game over! Your score is "<<(*board).count_points()<<" points"<<endl;

    return board -> count_points();
}

void sort_scores(int* scores) {
    int temp;
    for (int i=0; i <= best_score_count-1; i++){
        for (int a=0; a <= best_score_count-2-i; a++){
            if(scores[a]<scores[a+1])
            {
                temp=scores[a];
                scores[a]=scores[a+1];
                scores[a+1]=temp;
            }
        }
    }
    cout<<"Sorted scores"<<endl;
    for(int i=0; i<best_score_count; i++) {
        cout<<scores[i]<<endl;
    }
}

// pliki: http://www.cplusplus.com/doc/tutorial/files/

void load_scores(int* scores){
    string line;
    ifstream file(filename.c_str());
    if (file.is_open()) {
        int index = 0;
        while (getline (file, line) ) {
            cout << line << '\n';
            scores[index] = atoi(line.c_str());
            index++;
        }
        file.close();
    } else {
        cout << "File not found, init scores with 0s";
        for(int i=0; i<best_score_count; i++) {
            scores[i] = 0;
        }
    }
}

void save_scores(int* scores){
    ofstream file (filename.c_str());
    if (file.is_open()) {
        for(int i=0; i<best_score_count; i++) {
            file<<scores[i]<<endl;
        }
    }
    else cout << "Unable to write scores";
}

int main(int, char**) {
    cout<<"Started main method."<<endl;

    ALLEGRO_DISPLAY *display = NULL;
    al_init();
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    font = al_load_ttf_font("arial.ttf",72,0 );

    // zainicjalizuj kolejkê zdarzeñ z klawiatury
    al_install_keyboard();
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    int best_scores[best_score_count];
    load_scores(best_scores);

    //poczatek menu
    int selected=1;
    ALLEGRO_EVENT ev;
    while (true){
        draw_menu(selected);
        al_wait_for_event(event_queue, &ev);
        if(ev.type != ALLEGRO_EVENT_KEY_DOWN) {
            continue;
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            if (selected!=3){
                selected++;
            }
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
            if (selected!=1){
                selected--;
            }
        }
        else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            if (selected==1){
                cout<<"play game"<<endl;
                int points = play_game();
                // sprawdzenie, czy dodac nowy wynik
                if(points > best_scores[best_score_count - 1]) {
                    best_scores[best_score_count - 1] = points;
                    sort_scores(best_scores);
                }
            }
            if (selected==2){
                cout<<"scores"<<endl;
                draw_scores(best_scores);
            }
            if (selected==3){
                save_scores(best_scores);
                al_destroy_display(display);
                return 0;
            }
        } else {
            cout<<"Other key"<<endl;
            continue;
        }
    }
    //koniec menu

    al_destroy_display(display);
    return 0;
}
