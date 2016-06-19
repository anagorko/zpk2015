#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define screenWidth 640
#define screenHeight 480
#define TPS 60

/**** Plik naglowkowy klasy game ****/

class Game
{
    public:
        ALLEGRO_DISPLAY *display = NULL;
        ALLEGRO_BITMAP *image = NULL;
        ALLEGRO_BITMAP *title = NULL;
        ALLEGRO_BITMAP *wall = NULL;
        ALLEGRO_BITMAP *woodbox = NULL;
        ALLEGRO_BITMAP *lazarus = NULL;
        ALLEGRO_BITMAP *button = NULL;
        ALLEGRO_BITMAP *stone = NULL;
        ALLEGRO_FONT *font = NULL;

        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        ALLEGRO_TIMER *timer = NULL;
        ALLEGRO_SAMPLE *move_sound = NULL;
        ALLEGRO_SAMPLE *point = NULL;
        ALLEGRO_SAMPLE *song = NULL;

        ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;

        Level current_level;

        Game();
        bool done = false;
        bool next_level=false;
        virtual ~Game();
        void start();
        void draw_level(Level level);
        Level get_next_level();
        void move_left();
        void move_right();
        int type();
        void box_act();
        void game_over();
        void victory();

    protected:
        vector<Level> levels;
    private:
        // 0 - menu
        // 1 - w grze
        // 2 - po grze
        int game_state = 0;
        int loaded_level = -1;
        int typ=-1;
        // polozenie gracza na planszy
        int player_pos_x;
        int player_pos_y;

        // polozenie skrzynki, ktora spada
        int box_pos_x = -1;
        int box_pos_y = -1;


        void create_levels();
        void draw_metal_box(int x, int y);
        void draw_wood_box(int x, int y);
        void draw_stone_box(int x, int y);//5
        void draw_player(int x, int y);
        void draw_point(int x, int y);
        void draw_squares();


};

#endif // GAME_H
