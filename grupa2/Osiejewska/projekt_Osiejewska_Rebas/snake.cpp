#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>


using namespace std;
ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *mcfont;
ALLEGRO_FONT *font1;
ALLEGRO_EVENT events;
ALLEGRO_BITMAP *head;
ALLEGRO_BITMAP *wall;
ALLEGRO_BITMAP *body;
ALLEGRO_BITMAP *coin1;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *frameTimer;
ALLEGRO_TIMER *seconds;
ALLEGRO_KEYBOARD_STATE keyState;
int curF = 0;
int frameC = 0;
int frameD = 2;
int frameW = 40;
int frameH = 40;
int timeS = 0;
int timeF = 0;
int score = 0;
int angle = 0;
int wallTX[50], wallTY[50], walls = 0;
int snakeX[50], snakeY[50];
int length = 1;
int tempx;
int tempy;
int x=0, y=0;
int i=0;
int wallsNumber;

int coinX;
int coinY;

volatile int counter;
volatile int ticks=0;
volatile int framerate;
volatile int resting, rested;
int mki = 1;
int width = 800;
int height = 650;


typedef enum { nothing = 0, apple, snake } object;
enum direction { DOWN, LEFT, RIGHT, UP };
int dir = DOWN;

void game_over();
void load_bitmaps();
void menu();
void create_coin();
void check_if_coin();
void create_walls();
bool detect_collison();
void move_snake();
int main();


void game_over()
{
    al_draw_text(mcfont, al_map_rgb(255, 255, 255), 170, 100, 0,
                 "Game over. Press Enter");
    al_flip_display();
    while (1 == 1)
    {

        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (events.keyboard.keycode == ALLEGRO_KEY_ESCAPE);
            else if (events.keyboard.keycode == ALLEGRO_KEY_ENTER);
            exit(0);
        }
    }

}

void load_bitmaps()
{
    head = al_load_bitmap("white.png");
    if (!head)
    {
        fprintf(stderr, "Could not load 'head.png'.\n");
    }
    body = al_load_bitmap("pobrane.png");
    if (!body)
    {
        fprintf(stderr, "Could not load 'pobrane.png'.\n");
    }
    coin1 = al_load_bitmap("coin.png");
    if (!coin1)
    {
        fprintf(stderr, "Could not load 'neue_bitmap_2.jpg'.\n");
    }
    wall = al_load_bitmap("brown.jpg");
    if (!coin1)
    {
        fprintf(stderr, "Could not load 'wall.jpg'.\n");
    }
    font1 = al_load_font("OpenSans-Regular.ttf", 15, 0);
    if (!font1)
    {
        fprintf(stderr, "Could not load 'Minecrafter_3.ttf'.\n");
    }
    mcfont = al_load_font("OpenSans-Regular.ttf", 30, 0);
    if (!mcfont)
    {
        fprintf(stderr, "Could not load 'Minecrafter_3.ttf'.\n");
    }
}

void menu()
{
    al_draw_text(font1, al_map_rgb(255, 255, 255), 170, 100, 0,
                 "Snake v0.1");

    al_draw_text(font1, al_map_rgb(255, 255, 255), 100, 150, 0,
                 "Your aim is to collect coins. The more coins you get the longer snake becomes.");
    al_draw_text(font1, al_map_rgb(255, 255, 255), 100, 170, 0,
                 "You control snake with arrows. Beware of walls and obstacles as well as tail of your snake.");


    al_draw_text(mcfont, al_map_rgb(255, 255, 255), 100, 200, 0,
                 "Select level:");
    al_draw_text(mcfont, al_map_rgb(128, 247, 8), 170, 250, 0,
                 "Press E - EASY");
    al_draw_text(mcfont, al_map_rgb(247, 176, 8), 170, 300, 0,
                 "Press M - MEDIUM");
    al_draw_text(mcfont, al_map_rgb(247, 8, 6), 170, 350, 0,
                 "Press H - HARD");
    al_draw_text(mcfont, al_map_rgb(255, 255, 255), 300, 500, 0,
                 "Press Esc to Exit");
    al_flip_display();
}

bool detect_collison()
{
    if(x<0 || x>=width || y<0 || y>=height) return true;
    for (int k=0; k<wallsNumber; k++)
    {
        if (x==wallTX[k] && y==wallTY[k]) return true;
    }
    for (int i=0; i<score; i++)
    {
        if(x==snakeX[i] && y==snakeY[i]) return true;
    }
    return false;
}

void create_coin()
{

    int randy, randx;

    coinY = randy = 40 * (rand() % 15);
    coinX = randx = 40 * (rand() % 15);
}

void check_if_coin()
{
    if(x==coinX && y==coinY)
    {
        length++;
        score++;
        create_coin();
    }
}

void create_walls()
{
    srand(time( NULL ));
    wallsNumber = rand() % 10;

    for (int j=0; j<wallsNumber; j++)
    {
        int wallX = 40 * (rand() % 15);
        int wallY = 40 * (rand() % 15);

        wallTX[j] = wallX;
        wallTY[j] = wallY;
    }

}

void move_snake()
{
    tempx=x;
    tempy=y;
    al_wait_for_event(event_queue, &events);
    if (events.type == ALLEGRO_EVENT_TIMER)
    {
        if (events.timer.source == seconds)
            timeS++;
        if (events.timer.source == timer)
        {

            al_get_keyboard_state(&keyState);
            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && dir != LEFT)
                dir = RIGHT;
            else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && dir != RIGHT)
                dir = LEFT;
            else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && dir != DOWN)
                dir = UP;
            else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && dir != UP)
                dir = DOWN;

            for(int i=length; i>0; i--)
            {
                snakeY[i]=snakeY[i-1];
                snakeX[i]=snakeX[i-1];
            }
            snakeX[0]=tempx;
            snakeY[0]=tempy;


            switch (dir)
            {
            case RIGHT:
                x += 40;
                break;
            case LEFT:
                x -= 40;
                break;
            case UP:
                y -= 40;
                break;
            case DOWN:
                y += 40;
                break;
            }
            if (detect_collison()) game_over();
            check_if_coin();
            al_clear_to_color(al_map_rgb(0, 0, 0));

            for(int i=0; i<length; i++)
            {
                al_draw_bitmap(body, snakeX[i], snakeY[i], 0);
            }

            al_draw_bitmap(head, x, y, 0);

            al_draw_bitmap_region(coin1, curF * frameW, 0, frameW, frameH, coinX, coinY,
                                  0);
            for (int j=0; j<wallsNumber; j++)
            {
                al_draw_bitmap(wall, wallTX[j], wallTY[j], NULL);
            }
            std::ostringstream ss;
            ss << score;
            std::string result = "Coins: " + ss.str();
            const char * c = result.c_str();
            al_draw_textf(font1, al_map_rgb(250, 0, 250), 5, 5, 0, c);
            std::ostringstream ss2;
            ss2 << timeS;
            std::string result2 = "Time: " + ss2.str();
            const char * c2 = result2.c_str();
            al_draw_textf(font1, al_map_rgb(250, 0, 250), 705, 5, 0, c2);

            al_flip_display();
        }
    }

}

void set_timer(int time){
    timer = al_create_timer(1.0 / time);
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); //dodawanie timerów do kolejki
    al_start_timer(timer);
}

int main()
{
    al_init();
    display = al_create_display(width, height); //stwórz ekran
    al_set_window_position(display, 400, 300); //pozycja ekranuf
    al_init_font_addon(); //inicjalizacja fontów
    al_init_ttf_addon(); //inicjalizacja fontów ttf
    al_install_keyboard();
    al_init_image_addon();

    seconds = al_create_timer(1);

    event_queue = al_create_event_queue(); //deklaracja kolejki
    al_register_event_source(event_queue, al_get_timer_event_source(seconds));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(seconds);
    srand(time(NULL));
    create_coin();

    dir = DOWN; //poczatkowo waz porusza sie w dol
    load_bitmaps();
    menu();
    while (true )
    {
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                exit(0);
            }
            else if (events.keyboard.keycode == ALLEGRO_KEY_M)
            {
                set_timer(10);
                create_walls();
                while (true)
                {
                    move_snake();
                    ticks++;
                }

            }
            else if (events.keyboard.keycode == ALLEGRO_KEY_E)
            {
                set_timer(5);
                create_walls();
                while (true)
                {
                    move_snake();
                    ticks++;
                }

            }
            else if (events.keyboard.keycode == ALLEGRO_KEY_H){
                 set_timer(20);
                 create_walls();
                 while (true)
                {
                    move_snake();
                    ticks++;
                }

            }
        }
    }

    al_destroy_display(display);
    return 0;
}

