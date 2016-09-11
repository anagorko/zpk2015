#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>
#include<iostream>
#include<vector>
#define ScreenWidth 800
#define ScreenHeight 600
using namespace std;

class Pilka{
public:
    const float r = 6;
    int score = 0, poziom = 1;
    float x, y;
    float x_vel, y_vel;
    int liczba_zyc;
    bool przyklejony_do_paletki, koniec_gry;
    Pilka();
    ~Pilka();
    void rysuj_pilke();
    void kolizja_ze_sciana(float x, float y, float z, float x_vel, float y_vel, int liczba_zyc);
    void kolizja_z_klockiem(float x, float y, float w,  int tab[4][8]);
    void kolizja_z_paletka(float x, float z, float y, float x_vel, float y_vel);
};

Pilka::Pilka(){
x = ScreenWidth/2-6;
y = ScreenHeight/1.1-10;
x_vel = 5;
y_vel = 5;
liczba_zyc = 3;
przyklejony_do_paletki = true;
koniec_gry = false;
}

Pilka::~Pilka(){}

void Pilka::rysuj_pilke(){
    al_draw_filled_circle(x ,y ,r ,al_map_rgb(255,255,0));
}

void Pilka::kolizja_ze_sciana(float x, float y, float z, float x_vel, float y_vel, int liczba_zyc){
    if (x < 0 || x > ScreenWidth)
        x_vel = - x_vel;
    else if (y < 0)
            y_vel = - y_vel;
    else if (y > ScreenHeight)
        liczba_zyc--;
        if (liczba_zyc>0)
        {
            x_vel = 0;
            y_vel = 0;
            x = z + 60;
            y = ScreenHeight/1.1-10;
        }
        else
            //gdy przegrywamy wyswietlam napis koniec gry
            koniec_gry = true;
}

void Pilka::kolizja_z_klockiem(float x, float y, float w, int tab[4][8])
{
    for(int j = 0; j < 8; j++)
    {
            for(int i = 0; i < 4; i++)
            {
                if (x>=x+j*80 && x<w+j*80 && y==y+i*60)
                tab[i][j]--;
                score+=50;
            }
    }
}

void Pilka::kolizja_z_paletka(float x, float z, float y, float x_vel, float y_vel)
{
if (x<=z+120 && x>z+70 && y>ScreenHeight/1.1-10)
{
    y_vel = -y_vel;
    x_vel = 5;
}
else if (x<=z+70 && x>=z+50 && y>ScreenHeight/1.1-10)
{
    y_vel = 5;
    x_vel = 0;
}
else if (x<=z+50 && x>=z && y>ScreenHeight/1.1-10)
{
    y_vel = -y_vel;
    x_vel = -5;
}
}

class Klocki{
public:
    const int x = 100, y = 100, w = 160, z = 120;
    int liczba_zyc;
    int pozostale_klocki=0;
    int tab [32];
    void rysuj_klocki();
    Klocki(int liczba_zyc);
    ~Klocki();
};

Klocki::Klocki(int liczba_zyc)
{
// dla poziomu pierwszego wszystkie klocki mają 1 życie (klockow jest 32)
//dla poziomu 2 są to losowe liczby ze zbioru {1,2}
    for( int i = 0; i < 32; i++ )
    {
        tab[i]=liczba_zyc;
        pozostale_klocki+=tab[i];
    }
}

Klocki::~Klocki(){}


void Klocki::rysuj_klocki()
{
    for (int a=0; a<32; a++)
    {
        if (a<8)
        {
            if (tab[a]!=0 && tab[a]==1){
                al_draw_filled_rectangle(x+(a%8)*80, y, w+(a%8)*80, z, al_map_rgb(0,255,0));
            continue;}
            else if (tab[a]!=0 && tab[a]==2){
                al_draw_filled_rectangle(x+(a%8)*80, y, w+(a%8)*80, z, al_map_rgb(0,96,0));
            continue;}
        }
        else if (a<16)
        {
            if (tab[a]!=0 && tab[a]==1){
                al_draw_filled_rectangle(x+(a%8)*80, y+60, w+(a%8)*80, z+60, al_map_rgb(0,255,0));
        continue;}
        else if (tab[a]!=0 && tab[a]==2){
                al_draw_filled_rectangle(x+(a%8)*80, y+60, w+(a%8)*80, z+60, al_map_rgb(0,96,0));
        continue;}
        }
        else if (a<24)
        {
            if (tab[a]!=0 && tab[a]==1){
                al_draw_filled_rectangle(x+(a%8)*80, y+120, w+(a%8)*80, z+120, al_map_rgb(0,255,0));
        continue;}
        else if (tab[a]!=0 && tab[a]==2){
                al_draw_filled_rectangle(x+(a%8)*80, y+120, w+(a%8)*80, z+120, al_map_rgb(0,96,0));
        continue;
        }}
        else
        {
            if (tab[a]!=0 && tab[a]==1)
                al_draw_filled_rectangle(x+(a%8)*80, y+180, w+(a%8)*80, z+180, al_map_rgb(0,255,0));
            else if (tab[a]!=0 && tab[a]==2)
                al_draw_filled_rectangle(x+(a%8)*80, y+180, w+(a%8)*80, z+180, al_map_rgb(0,96,0));
        continue;
        }
    }
}

class Paletka{
public:
    float x,w;
    const float y = ScreenHeight/1.1;
    const float h = ScreenHeight/1.1 + 6;
    Paletka();
    ~Paletka();
    void rysuj_paletke(float x, float y, float w, float h);
    void odswiez(float x);
};

Paletka::Paletka()
{
    x = ScreenWidth/2-60;
    w = ScreenWidth/2+60;
}

Paletka::~Paletka(){}

void Paletka::rysuj_paletke(float x, float y, float w, float h)
{
    al_draw_filled_rectangle(x, y, w, h, al_map_rgb(44, 117, 255));
}

void Paletka::odswiez(float x){
    if (x < 60)
        x = 60;
    else if (x > ScreenWidth - 120)
         x = ScreenWidth - 120;
}


int main()
{

 ALLEGRO_DISPLAY *display;

 const float FPS = 60.0;

 enum Direction {UP, DOWN, LEFT, RIGHT};

 if(!al_init())
 al_show_native_message_box(NULL, NULL, NULL, "Could not initialize Allegro 5", NULL, NULL);
 //Definiuje rozmiar ekranu
 display = al_create_display(ScreenWidth, ScreenHeight);
 al_set_window_position(display,200,100);
 //Dodaje tytul
 al_set_window_title(display, "Arkanoid");

 if(!display)
 al_show_native_message_box(NULL, NULL, NULL, "Could not create Allegro 5 display", NULL, NULL);

 int dir;
 al_init_primitives_addon();
 al_init_image_addon();
 al_install_mouse();
 al_install_keyboard();
 al_init_font_addon();
 al_init_ttf_addon();

//wczytuje czcionke w dwóch rozmiarach
 ALLEGRO_FONT *font = al_load_font("font.ttf",36,0);
 ALLEGRO_FONT *fontbig = al_load_font("font.ttf",80,0);

 //gdy brak plików ttf wyswietla błąd
if (font == NULL) cout <<"ERR_CANT_LOAD_FONT"<< endl;
if(fontbig == NULL) cout << "ERR_CANT_LOAD_FONT"<<endl;

 ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
 ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
 al_register_event_source(event_queue, al_get_mouse_event_source());
 al_register_event_source(event_queue, al_get_timer_event_source(timer));
 al_register_event_source(event_queue, al_get_display_event_source(display));
 al_register_event_source(event_queue, al_get_keyboard_event_source());
 al_hide_mouse_cursor(display);
 al_start_timer(timer);

 Pilka ball;
 Paletka paddle;
 Klocki bricks(1);


 while(!ball.koniec_gry)
 {
    // tworzę kolejkę zdarzeń
    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue, &events);

    if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        ball.koniec_gry = true;
    }
    else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        paddle.x = events.mouse.x - 60;
        paddle.w = events.mouse.x + 60;
    }
    else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
//po wcisnieciu lewego klawisza myszy nastepuje zwolnienie pileczki
        if(events.mouse.button & 1)
            ball.przyklejony_do_paletki = false;
            ball.x_vel = 5;
            ball.y_vel = 5;
            dir = UP;
    }

    if(events.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(events.keyboard.keycode)
        {
// po wcisnieciu strzalki do góry nastepuje przyspieszenie pileczki
        case ALLEGRO_KEY_UP:
            ball.x_vel = 1.3*ball.x_vel, ball.y_vel = 1.3*ball.y_vel;
            break;
//po wcisnieciu klawisza escape nasteuje wyjscie z gry (done=true)
        case ALLEGRO_KEY_ESCAPE:
            ball.koniec_gry = true;
            break;
        }

    }

// przyspieszanie i zwalnianie pilki
    if(events.type == ALLEGRO_EVENT_TIMER)
    {
        switch(dir)
        {
        case DOWN:
           ball.y += ball.y_vel;
           ball.x -= ball.x_vel;
            break;
        case UP:
           ball.y -= ball.y_vel;
           ball.x += ball.x_vel;
           break;
        }

//gdy pilka jest przyklejona do paletki ustawiam ja na jej srodku
        if(ball.przyklejony_do_paletki)
        {
            ball.x = paddle.x + 60;
            ball.y = ScreenHeight/1.1-10;
        }


//rysuje paletke, pilke i klocki
 paddle.rysuj_paletke(paddle.x,paddle.y,paddle.w,paddle.h);
 ball.rysuj_pilke();
 bricks.rysuj_klocki();


 //kolizje ze scianami
 if (ball.x < 0 || ball.x > ScreenWidth)
 {
    ball.x_vel *= - 1;
 }

 if (ball.y > ScreenHeight)
 {
     ball.liczba_zyc--;
    if (ball.liczba_zyc>0)
    {
        ball.x_vel = 0, ball.y_vel = 0;
        ball.przyklejony_do_paletki = true;
    }
    else
    {
//gdy przegrywamy wyswietlam napis koniec gry
     ball.liczba_zyc = 0;
     al_draw_textf(fontbig, al_map_rgb(255,0,0),400,200,ALLEGRO_ALIGN_CENTER,"GAME OVER");
    }
}

if (ball.y < 0)
{
ball.y_vel *= -1;
}

//odbicie od paletki, gdy po jej prawej stronie w prawo, po jej lewej w lewo

if (ball.x<=(paddle.x+120) && ball.x>paddle.x+80 && ball.y>ScreenHeight/1.1-10)
{
    ball.y_vel *= -1;
    ball.x_vel = 5;
}
if (ball.x<=(paddle.x+80) && ball.x>paddle.x+60 && ball.y>ScreenHeight/1.1-10)
{
    ball.y_vel *= -1;
    ball.x_vel = 4;
}
if (ball.x<=(paddle.x+60) && ball.x>paddle.x+40 && ball.y>ScreenHeight/1.1-10)
{
    ball.y_vel *= -1;
    ball.x_vel = -4;
}
if (ball.x<=(paddle.x+40) && ball.x>=paddle.x && ball.y>ScreenHeight/1.1-10)
{
    ball.y_vel *= -1;
    ball.x_vel = -5;
}

//kolizja z poziomymi bokami klocków
if (bricks.pozostale_klocki!=0){
al_draw_textf(font, al_map_rgb(44,117,255),560,10,ALLEGRO_ALIGN_LEFT,"LEVEL: %i", ball.poziom);
for (int a=0; a<32; a++)
    {
        if (a<8)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) &&(ball.y>=119)&& (ball.y<=121) )||
                (bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=119-20)&& (ball.y<=121-20)))
            {
                ball.score+= 100;
                ball.y_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else if (a<16)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=179)&& (ball.y<=181))||
                (bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=179-20)&& (ball.y<=181-20)))
            {
                ball.score+= 100;
                ball.y_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else if (a<24)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=239)&& (ball.y<=241))||
                (bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=239-20)&& (ball.y<=241-20)))
            {
                ball.score+= 100;
                ball.y_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else
        {
            if ((bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=299)&& (ball.y<=301))||
                (bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=299-20)&& (ball.y<=301-20)))
            {
                ball.score+= 100;
                ball.y_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
    }
//kolizja z pionowymi bokami klocków

for (int a=0; a<32; a++)
    {
        if (a<8)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=99) && (ball.x<=101) && (ball.y>=bricks.y)&& (ball.y<=bricks.z))||
                (bricks.tab[a]!=0 && (ball.x>=99+60) && (ball.x<=101+60) && (ball.y>=bricks.y)&& (ball.y<=bricks.z)))
            {
                ball.score+= 100;
                ball.x_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }


        }
        else if (a<16)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=99+80) && (ball.x<=101+80) && (ball.y>=bricks.y+60)&& (ball.y<=bricks.z+60))||
                (bricks.tab[a]!=0 && (ball.x>=99+80+60) && (ball.x<=101+80+60) && (ball.y>=bricks.y+60)&& (ball.y<=bricks.z+60)))
            {
                ball.score+= 100;
                ball.x_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else if (a<24)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=99+160) && (ball.x<=101+160) && (ball.y>=bricks.y+120)&& (ball.y<=bricks.z+120))||
                (bricks.tab[a]!=0 && (ball.x>=99+160+60) && (ball.x<=101+160+60) && (ball.y>=bricks.y+120)&& (ball.y<=bricks.z+120)))
            {
                ball.score+= 100;
                ball.x_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else if (a<32)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=99+240) && (ball.x<=101+240) &&(ball.y>=bricks.y+180)&& (ball.y<=bricks.z+180))||
                (bricks.tab[a]!=0 && (ball.x>=99+240+60) && (ball.x<=101+240+60) && (ball.y>=bricks.y+180)&& (ball.y<=bricks.z+180)))
            {
                ball.score+= 100;
                ball.x_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
    }
}

else if (bricks.pozostale_klocki==0)
{
       ball.x = paddle.x + 60;
       ball.y = ScreenHeight/1.1-10;
       ball.x_vel = 0, ball.y_vel = 0;
       ball.przyklejony_do_paletki;
    for( int i = 0; i < 32; i++)
    {
     if(i%2){
        bricks.tab[i]=1;
        }
    else{
        bricks.tab[i]=2;
        }
    }

    bricks.pozostale_klocki=48;
    ball.poziom ++;

if (bricks.pozostale_klocki!=0 && ball.poziom==2){
        al_draw_textf(font, al_map_rgb(44,117,255),560,10,ALLEGRO_ALIGN_LEFT,"LEVEL: %i", ball.poziom);
for (int a=0; a<32; a++)
    {
        if (a<8)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) &&(ball.y>=119)&& (ball.y<=121) )||
                (bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=119-20)&& (ball.y<=121-20)))
            {
                ball.score+= 100;
                ball.y_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else if (a<16)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=179)&& (ball.y<=181))||
                (bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=179-20)&& (ball.y<=181-20)))
            {
                ball.score+= 100;
                ball.y_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else if (a<24)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=239)&& (ball.y<=241))||
                (bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=239-20)&& (ball.y<=241-20)))
            {
                ball.score+= 100;
                ball.y_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else
        {
            if ((bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=299)&& (ball.y<=301))||
                (bricks.tab[a]!=0 && (ball.x>=bricks.x+(a%8)*80) && (ball.x<=bricks.w+(a%8)*80) && (ball.y>=299-20)&& (ball.y<=301-20)))
            {
                ball.score+= 100;
                ball.y_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
    }
//kolizja z pionowymi bokami klocków

for (int a=0; a<32; a++)
    {
        if (a<8)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=99) && (ball.x<=101) && (ball.y>=bricks.y)&& (ball.y<=bricks.z))||
                (bricks.tab[a]!=0 && (ball.x>=99+60) && (ball.x<=101+60) && (ball.y>=bricks.y)&& (ball.y<=bricks.z)))
            {
                ball.score+= 100;
                ball.x_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }

        }
        else if (a<16)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=99+80) && (ball.x<=101+80) && (ball.y>=bricks.y+60)&& (ball.y<=bricks.z+60))||
                (bricks.tab[a]!=0 && (ball.x>=99+80+60) && (ball.x<=101+80+60) && (ball.y>=bricks.y+60)&& (ball.y<=bricks.z+60)))
            {
                ball.score+= 100;
                ball.x_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else if (a<24)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=99+160) && (ball.x<=101+160) && (ball.y>=bricks.y+120)&& (ball.y<=bricks.z+120))||
                (bricks.tab[a]!=0 && (ball.x>=99+160+60) && (ball.x<=101+160+60) && (ball.y>=bricks.y+120)&& (ball.y<=bricks.z+120)))
            {
                ball.score+= 100;
                ball.x_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
        else if (a<32)
        {
            if ((bricks.tab[a]!=0 && (ball.x>=99+240) && (ball.x<=101+240) &&(ball.y>=bricks.y+180)&& (ball.y<=bricks.z+180))||
                (bricks.tab[a]!=0 && (ball.x>=99+240+60) && (ball.x<=101+240+60) && (ball.y>=bricks.y+180)&& (ball.y<=bricks.z+180)))
            {
                ball.score+= 100;
                ball.x_vel *= -1;
                bricks.tab[a]--;
                bricks.pozostale_klocki--;
                continue;
            }
        }
    }
}
}
if (bricks.pozostale_klocki!=0 && ball.poziom==3){
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_textf(fontbig, al_map_rgb(44,117,0),400,200,ALLEGRO_ALIGN_CENTER,"CONGRATULATIONS!!!!!!");
}



//wykrywam kolizje
//ball.kolizja_z_paletka(ball.x, paddle.x, ball.y, ball.x_vel, ball.y_vel);
//ball.kolizja_z_klockiem(ball.x, ball.y, ball.y, bricks.tab);


//korekta paletki, aby nie wyjeżdżała za ekran
//paddle.odswiez(paddle.x);


//tworze liczniki na dole ekranu
al_draw_textf(font, al_map_rgb(44,117,255),10,560,ALLEGRO_ALIGN_LEFT,"LIVES: %i", ball.liczba_zyc);
al_draw_textf(font, al_map_rgb(44,117,255),200,560,ALLEGRO_ALIGN_LEFT,"SCORE: %i", ball.score);
al_draw_textf(font, al_map_rgb(44,117,255),460,560,ALLEGRO_ALIGN_LEFT,"TO SPEED UP THE BALL PRESS ARROW UP");
al_flip_display();
al_clear_to_color(al_map_rgb(255, 255, 255));

 }}

 //Zwalniam pamiec
 al_destroy_display(display);
 al_destroy_event_queue(event_queue);
 al_destroy_font(font);
 return 0;
}

