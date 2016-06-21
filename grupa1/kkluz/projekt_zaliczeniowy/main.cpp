#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>
#include<iostream>
using namespace std;

#define ScreenWidth 800
#define ScreenHeight 600


int main()
{
using namespace std;

 //tworze okno do rysowania
 ALLEGRO_DISPLAY *display;

 const float FPS = 60.0;

 enum Direction {UP, DOWN, LEFT, RIGHT};

 if(!al_init())
 al_show_native_message_box(NULL, NULL, NULL, "Could not initialize Allegro 5", NULL, NULL);
 //Definiuje rozmiar ekranu
 display = al_create_display(800, 600);
 al_set_window_position(display,200,100);
 //Dodaje tytul
 al_set_window_title(display, "Arkanoid");

 if(!display)
 al_show_native_message_box(NULL, NULL, NULL, "Could not create Allegro 5 display", NULL, NULL);

// definiuje zmienne globalne
 bool done = false, draw = true;
 int r = 10;
 int ballx = ScreenWidth/2, bally = ScreenHeight/1.1-r, velx = 5, vely = 5;
 int dir;
 int paddlex = ScreenWidth/2-60, paddley = ScreenHeight/1.1;
 int lives = 3;
 int score = 0;
 int x = 120;
 int y = 20;
 int BrickHeight = 20;
 int BrickWidth = 60;
 int i = 10;
 int j = 10;
 bool sticky = true;
 int Bricks[800][600]={0};
 int level = 0;
 int a , b;

// poziom pierwszy, przypisuje poszczególnym klockom "liczbe zyc"
if (level = 0)
{
for(int b = 20; b < 200; b = b + 80)
{
    for(int a = 120; a < 800; a = a + 200)
    {
        Bricks[a][b] = 1;
    }
}

for(b = 60; b < 200; b = b + 80)
{
    for(a = 120; a < 800; a = a + 200)
    {
        Bricks[a][b] = 2;
    }

}

for(int b = 20; b <= 180; b = b + 40)
{
    for(int a = 20; a < 800; a = a + 200)
    {
        Bricks[a][b] = 1;
    }
}}
// poziom drugi, przypisuje poszczególnym klockom "liczbe zyc"
else if (level = 1)
{
for(int b = 20; b < 200; b = b + 80)
{
    for(int a = 120; a < 800; a = a + 200)
    {
        Bricks[a][b] = 2;
    }
}

for(b = 60; b < 200; b = b + 80)
{
    for(a = 120; a < 800; a = a + 200)
    {
        Bricks[a][b] = 1;
    }

}

for(int b = 20; b <= 180; b = b + 40)
{
    for(int a = 20; a < 800; a = a + 200)
    {
        Bricks[a][b] = 2;
    }
}
}
//definiuje kolory uzyte do rysowania
 ALLEGRO_COLOR blue = al_map_rgb(44, 117, 255);
 ALLEGRO_COLOR yellow = al_map_rgb(255,255,0);
 ALLEGRO_COLOR green = al_map_rgb(0,255,0);


 al_init_primitives_addon();
 al_init_image_addon();
 al_install_mouse();
 al_install_keyboard();
 al_init_font_addon();
 al_init_ttf_addon();

//wczytuje czcionke w dwóch rozmiarach
 ALLEGRO_FONT *font = al_load_font("font.ttf",36,0);
 ALLEGRO_FONT *fontbig = al_load_font("font.ttf",80,0);

 ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
 ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
 al_register_event_source(event_queue, al_get_mouse_event_source());
 al_register_event_source(event_queue, al_get_timer_event_source(timer));
 al_register_event_source(event_queue, al_get_display_event_source(display));
 al_register_event_source(event_queue, al_get_keyboard_event_source());
 al_hide_mouse_cursor(display);
 al_start_timer(timer);


 while(!done)
 {
    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue, &events);

    if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        done = true;
    }
    else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        paddlex = events.mouse.x;
        //paddley = events.mouse.y;
    }
    else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
//przy wcisnieciu lewego klawisza myszy nastepuje zwolnienie pileczki
        if(events.mouse.button & 1)
            sticky = false;
            velx = 5;
            vely = 5;
            dir = UP;
    }

    if(events.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(events.keyboard.keycode)
        {
// po wcisnieciu strzalki do góry nastpeuje przyspieszenie pileczki
        case ALLEGRO_KEY_UP:
            velx = 1.5*velx, vely = 1.5*vely;
            break;
//po wcisnieciu klawisza escape nasteuje wyjscie z gry (done=true)
        case ALLEGRO_KEY_ESCAPE:
            done = true;
            break;
        }

    }
// zdefiniowanie kierunkow
    if(events.type == ALLEGRO_EVENT_TIMER)
    {
        switch(dir)
        {
        case DOWN:
           bally += vely;
           ballx -= velx;
            break;
        case UP:
           bally -= vely;
           ballx += velx;
           break;
        case RIGHT:
           ballx += velx;
           bally += vely;
            break;
        case LEFT:
           ballx -= velx;
           bally -= vely;
            break;
        }
//gdy pilka jest przyklejona do paletki ustawiam ja na jej srodku
        if(sticky)
        {
            ballx = paddlex + 60;
            bally = ScreenHeight/1.1-10;
        }
//kolizje ze scianami
                if (ballx < 0)
                {
                    velx = - velx;
                }
                 else if (ballx > ScreenWidth)
                {
                    velx = - velx;
                }
                 else if (bally > 600)
                {
                    lives--;
                    if (lives>0)
                    {
                     velx = 0, vely = 0;
                     sticky = true;
                    }
                    else
                    {
                        //gdy przegrywamy wyswietlam napis koniec gry
                        lives = 0;
                        al_draw_textf(fontbig, al_map_rgb(255,0,0),400,300,ALLEGRO_ALIGN_CENTER,"GAME OVER");
                        //al_flip_display();
                        //al_clear_to_color(al_map_rgb(255, 255, 255));
                        //lives = 0;
                        //sticky = true;
                        //ballx = ScreenWidth/2, bally = ScreenHeight/1.1-r,
                       // paddlex = ScreenWidth/2-60, paddley = ScreenHeight/1.1;
                    }
                }
                 else if (bally < 0)
                {
                    vely = - vely;
                }
                //odbicie od paletki, gdy po jej prawej stronie w prawo, po jej lewej w lewo
                else if (ballx<=(paddlex+120) && ballx>paddlex+60 && bally>ScreenHeight/1.1-10)
                {
                    vely = -vely;
                    velx = 5;
                }
                else if (ballx<=(paddlex+60) && ballx>=paddlex && bally>ScreenHeight/1.1-10)
                {
                    vely = -vely;
                    velx = -5;
                }

//zatrzymanie paletki aby nie uciekala poza ekran
if (paddlex < 0)
    paddlex = 0;

if (paddlex > ScreenWidth - 120)
    paddlex = ScreenWidth - 120;
}

//odbicie pilki od poziomych boków klocków
for (i=20; i<800; i=i+100){
    if ((bally == 40+r || bally == 20+r)  & ballx>=i & ballx<=i+BrickWidth)
        {
         Bricks[i][40]--;
         vely = -vely;
         score = score + 10;
        }

    else if ((bally == 80+r || bally == 60+r) & ballx>=i & ballx<=i+BrickWidth)
        {
         Bricks[i][80]--;
         vely = -vely;
         score = score + 10;
        }

    else if ((bally == 120+r || bally == 100+r) & ballx>=i & ballx<=i+BrickWidth)
        {
         Bricks[i][120]--;
         vely = -vely;
         score = score + 10;
        }

    else if ((bally == 160+r || bally == 140+r) & ballx>=i & ballx<=i+BrickWidth)
        {
         Bricks[i][160]--;
         vely = -vely;
         score = score + 10;
        }

    else if ((bally == 200+r || bally == 180+r) & ballx>=i & ballx<=i+BrickWidth)
        {
         Bricks[i][200]--;
         vely = -vely;
         score = score + 10;
        }
}
//odbicie pilki od pionowych boków klocków
for (j=20; j<200; j=j+40){
    if ((ballx == 20-r || ballx == 20+r)  & bally>=j & bally<=j+BrickHeight)
        {
         Bricks[20][j]--;
         velx = -velx;
         score = score + 10;
        }

    else if ((ballx == 120-r || ballx == 120+r) & bally>=j & bally<=j+BrickHeight)
        {
         Bricks[120][j]--;
         velx = -velx;
         score = score + 10;
        }

    else if ((ballx == 220-r || ballx == 220+r) & bally>=j & bally<=j+BrickHeight)
        {
         Bricks[220][j]--;
         velx = -velx;
         score = score + 10;
        }

    else if ((ballx == 320+r || ballx == 320-r) & bally>=j & bally<=j+BrickHeight)
        {
         Bricks[320][j]--;
         velx = -velx;
         score = score + 10;
        }

    else if ((ballx == 420+r || ballx == 420-r) & bally>=j & bally<=j+BrickHeight)
        {
         Bricks[420][j]--;
         velx = -velx;
         score = score + 10;
        }
}
//rysowanie klockow - tutaj nie dziala, powinny nie rysowac sie klocki, ktore maja "zero zyc"
        for(int j = 20; j <= 180; j = j + 40)
        {
            for(int i = 20; i < 800; i = i + 200)
            {
                if (Bricks[i][j]!=0){
                al_draw_filled_rectangle(i, j, i + BrickWidth, j + BrickHeight, blue);
                al_draw_filled_rectangle(i, j, i + BrickWidth, j + BrickHeight, blue);
            }}
        }

            for(int j = 60; j < 200; j = j + 80)
            {
                for(int i = 120; i < 800; i = i + 200)
                {
                    if (Bricks[i][j]!=0){
                    al_draw_filled_rectangle(i, j, i + BrickWidth, j + BrickHeight, green);
                }}

            }


            for(int j = 20; j < 200; j = j + 80)
            {
                for(int i = 120; i < 800; i = i + 200)
                {if (Bricks[i][j]!=0){
                    al_draw_filled_rectangle(i, j, i + BrickWidth, j + BrickHeight, blue);
                }}

 }
            //przejscie do kolejnego poziomu
            //if (Bricks[i][j]={0})
                //level++;
            //rysuje paletke i pilke
            al_draw_filled_rectangle(paddlex, paddley, paddlex + 120, paddley + 10, blue);
            al_draw_filled_circle(ballx ,bally ,10 ,yellow);
            //tworze liczniki na dole ekranu
            al_draw_textf(font, al_map_rgb(44,117,255),10,560,ALLEGRO_ALIGN_LEFT,"LIVES: %i", lives);
            al_draw_textf(font, al_map_rgb(44,117,255),200,560,ALLEGRO_ALIGN_LEFT,"SCORE: %i", score);
            al_draw_textf(font, al_map_rgb(44,117,255),500,560,ALLEGRO_ALIGN_LEFT,"TO FASTEN THE BALL PRESS ARROW UP");
            al_flip_display();
            al_clear_to_color(al_map_rgb(255, 255, 255));

 }

 //Zwalniam pamiec
 al_destroy_display(display);
 al_destroy_event_queue(event_queue);
 al_destroy_font(font);
 return 0;
}
