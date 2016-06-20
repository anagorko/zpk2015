#include<iostream>
#include <cstdio>
#include <iomanip>
#include <stdio.h>      /* printf, fopen */
#include <stdlib.h>          /* exit, EXIT_FAILURE */

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h> //plik nagłówkowy dla rysowania figur itp.
#include <math.h>

#include "wyrazenia.h"

using namespace std;
/*rozmiar okienka z wykresem*/
const int w = 800;
const int h = 600;
/*rozmiar okienka konsoli*/
const int w1 = 400;
const int h1 = 300;

double a = -5;//min x
double b = 5;//max x*/

double sup, inf, v[w]; //sup, inf oraz tablica wartosci funkcji o dlugosci jak szerokosc okienka dla osi OX
float mouse_x, mouse_y;//polozenie myszki


string text;
ALLEGRO_FONT    *font;

/******************************************************************************************************************/
/*  odpowiednie odczytywanie wpisanego wzoru w OPN                                                                 */
/******************************************************************************************************************/
double f(string expr, double x)
{
    double res = calculate_expression(expr, x);
   // printf("f(%f)=%f\n", x, res);
    return res;
}

/*****************************************************************************************************************************/
/*ustalenie polozenia osi OX i OY                                                                                           */
/***************************************************************************************************************************/
int zero_x(double x_min_arg, double x_max_arg)
{   a = x_min_arg;
    b = x_max_arg;
 /*chce widziec zawsze os OY nawet gdy podany zakres rysowania wykresu jest tylko w jednej polowce
 np tylko prawej albo tylko lewej*/
         if(a<=0 && b>0){ return w * (0 - a) / (b - a);}
        if(a<0 && b<=0){ return w-10;}
        if(a>=0 && b>0){return 10;}

}

int zero_y()
{
/*tutaj tez zawsze chce pokazac os oy, nawet, gdy wszystkie wartosci funkcji zawarte sa tylko
w jednej polowce(np tylko gornej albo tylko dolnej)*/
    if(inf<0 && sup>0){return h - h * (0-inf) / (sup - inf);}
        if(inf<0 && sup<=0){return 10;}
        if(inf>=0 && sup>0){return h-10;}
    }


/******************************************************************************************************************/
/*             przeliczanie w petli wartosci wpisanej funkcji                                                     */
/******************************************************************************************************************/
void calculate(string expr, double x_min_arg, double x_max_arg)
{
    font = al_load_ttf_font("arial.ttf",10,0 );
    sup = -10000000;
    inf = 10000000;
    a = x_min_arg;
    b = x_max_arg;
//musze uwzglednic te przesuniecia osi ktore chce zrobic
if (a<0 && b>0){
    for (int i = 0; i < w; i++){ v[i] = f(expr, a + ((b - a) * i) / w );
        if (v[i] > sup && v[i]!=INFINITY) { sup = v[i]; }
        if (v[i] < inf && v[i]!=-INFINITY) { inf = v[i]; }
    }}
else if (a<0 && b<=0){
    for (int i = 0; i < w; i++){ v[i] = f(expr, a + ((b - a) * i) / (w-10) );
        if (v[i] > sup && v[i]!=INFINITY) { sup = v[i]; }
        if (v[i] < inf && v[i]!=-INFINITY) { inf = v[i]; }
    }}

 else if (a>=0 && b>0) {
    for (int i = 0; i < w; i++){ v[i] = f(expr, a + ((b - a) * (i-10)) / (w-10) );
        if (v[i] > sup && v[i]!=INFINITY) { sup = v[i]; }
        if (v[i] < inf && v[i]!=-INFINITY) { inf = v[i]; }
    }}

   //cout << "sup = " << sup << endl;
   //cout << "inf = " << inf << endl;
}



/******************************************************************************************************************/
/* funkcja rysuje w okienku wykresu odpowiednie osie oraz zaznacza wartosci funkcji                                */
/* ale w konwencji, jak zwykle rysuje sie wykresy, a nie jak w standardzie c++, czyli ze oś OY rośnie do dołu ekranu*/
/******************************************************************************************************************/

void draw_graph_window(ALLEGRO_BITMAP *bitmap, double x_min_arg, double x_max_arg) {
    al_set_target_bitmap(bitmap);

    al_clear_to_color(al_map_rgb(255,255,255));
/*rysowanie osi ox i oy, ale gdy maja one byc poza wykresem, to jakby osiami beda krawedzie wykresu zeby
zaznaczyc jakos te wartosci*/
//male kreseczki na osiach i siatke podzialowa
        for (int j = 0; j<=w; j+=40){
            al_draw_line(j,0, j, h, al_map_rgb(190,190,190), 0.5);
            al_draw_line(0,j, w,j , al_map_rgb(190,190,190), 0.5);

            al_draw_line(j,zero_y()-2, j, zero_y()+2, al_map_rgb(0,0,0), 2);
            al_draw_line(zero_x(x_min_arg, x_max_arg)-2,j, zero_x(x_min_arg, x_max_arg)+2,j , al_map_rgb(0,0,0), 2);
        }
//osie glowne
    al_draw_line(0, zero_y(), w, zero_y(), al_map_rgb(0,0,0), 2);
    al_draw_line(zero_x(x_min_arg, x_max_arg),0, zero_x(x_min_arg, x_max_arg), h, al_map_rgb(0,0,0), 2);


//1.przypadek gdy sup i inf maja rozny znak
    if (a<=0 && b>0 && inf<0 && sup>0){
        for (int i =0; i < w; i++) {
                al_draw_pixel(i,  h - (v[i] / (sup - inf) * h )+ inf / (sup - inf) * h , al_map_rgb(0,0,128));
        }
    }

    else if (a>=0 && b>0 && inf<0 && sup>0){
        for (int i = 10; i < w; i++){
            al_draw_pixel(i,  h - (v[i] / (sup - inf) * h) + inf/(sup - inf) * h, al_map_rgb(0,0,128));
        }
     }

    else if (a<0 && b<=0 && inf<0 && sup>0){
        for (int i = 0; i < w - 10; i++) {
            al_draw_pixel(i,  h - v[i] / (sup - inf) * h + inf /(sup - inf) * h, al_map_rgb(0,0,128));
        }
     }

//2. przypadek gdy sup i inf maja ten sam znak <0
  else if (a<=0 && b>0 && inf<0 && sup<=0){
        for (int i =0; i < w; i++) {
                al_draw_pixel(i,  h - v[i] / (-sup - inf) * (h-10) +inf/ (-sup - inf) * (h-10)  , al_map_rgb(0,0,128));
        }
    }

    else if (a>=0 && b>0 && inf<0 && sup<=0){
        for (int i = 10; i < w; i++){
            al_draw_pixel(i,  h - v[i] / (-sup - inf) * (h-10) + inf/(-sup - inf) * (h-10)  , al_map_rgb(0,0,128));
        }
     }

    else if (a<0 && b<=0 && inf<0 && sup<=0){
        for (int i = 0; i < w - 10; i++) {
            al_draw_pixel(i,  h - v[i] / (-sup - inf) * (h-10) + inf/(-sup - inf) * (h-10) , al_map_rgb(0,0,128));
        }
     }


//3. przypadek gdy sup i inf maja ten sam znak >0
 else if (a<=0 && b>0 && inf>=0 && sup>0){
        for (int i =0; i < w; i++) {
                al_draw_pixel(i,  h - 10 - v[i] / (sup + inf) * (h-10), al_map_rgb(0,0,128));
        }
     }

    else if (a>=0 && b>0 && inf>=0 && sup>0){
        for (int i = 10; i < w; i++){
            al_draw_pixel(i,  h - 10  - v[i] / (sup + inf) * (h-10), al_map_rgb(0,0,128));
        }

     }

    else if (a<0 && b<=0 && inf>=0 && sup>0){
        for (int i = 0; i < w - 10; i++) {
            al_draw_pixel(i,  h - 10 - v[i] / (sup + inf) * (h-10), al_map_rgb(0,0,128));
        }
    }


      al_flip_display();
}



/*****************************************************************************************************************************/
/*    funkcja do wypelniania okioenek z zakresami x_min i x_max i rysowania okienek i "przyciskow"                          */
/***************************************************************************************************************************/
void fill_input_window(ALLEGRO_BITMAP *bitmap) {
    font = al_load_ttf_font("arial.ttf",18,0 );
   //to jest na poczatku wyglad okienka gdy jeszcze nic nie wpisalismy
    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgb(169, 169, 169));
    al_draw_rectangle(2,2,398, 298,al_map_rgb(105,105,105),1);

    al_draw_text(font,al_map_rgb(255,255,255), 5,10,0, "Podaj wzór funkcji:");
    //obszar pisania funkcji
    al_draw_text(font,al_map_rgb(255,255,255), 15,55,0, "f(x) =");
    al_draw_filled_rectangle(70,50,350, 80, al_map_rgb(255, 248, 220));
    al_draw_rectangle(70,50,350, 80, al_map_rgb(0,0,0),1);

    //obszar ustawiania zakresu osi wykresu funkcji
    al_draw_text(font,al_map_rgb(255,255,255), 25,105,0, "min x =");
    al_draw_filled_rectangle(85,100,165, 130,al_map_rgb(255, 248, 220));
    al_draw_rectangle(85,100,165, 130,al_map_rgb(0,0,0),1);
    al_draw_filled_rectangle(140,100,165, 130,al_map_rgb(176, 196, 222));
    al_draw_rectangle(140,100,165, 115,al_map_rgb(0,0,0),1);
    al_draw_rectangle(140,115,165, 130,al_map_rgb(0,0,0),1);
    /*strzalki*/
    al_draw_line(145,110,152, 105,al_map_rgb(0,0,0),1);
    al_draw_line(152,105,160, 110,al_map_rgb(0,0,0),1);
    al_draw_line(145,120,152, 125,al_map_rgb(0,0,0),1);
    al_draw_line(152,125,160, 120,al_map_rgb(0,0,0),1);


    al_draw_text(font,al_map_rgb(255,255,255), 195,105,0, "max x =");
    al_draw_filled_rectangle(260,100,340, 130, al_map_rgb(255, 248, 220));
    al_draw_rectangle(260,100,340, 130, al_map_rgb(0,0,0),1);
    al_draw_filled_rectangle(315,100,340, 130, al_map_rgb(176, 196, 222));
    al_draw_rectangle(315,100,340, 115, al_map_rgb(0,0,0),1);
    al_draw_rectangle(315,115,340, 130, al_map_rgb(0,0,0),1);
    /*strzalki*/
    al_draw_line(320,110,327, 105,al_map_rgb(0,0,0),1);
    al_draw_line(327,105,335, 110,al_map_rgb(0,0,0),1);
    al_draw_line(320,120,327, 125,al_map_rgb(0,0,0),1);
    al_draw_line(327,125,335, 120,al_map_rgb(0,0,0),1);


font = al_load_ttf_font("arial.ttf",16,0 );
    al_draw_filled_rounded_rectangle(70,160,190, 190,3,3, al_map_rgb(144, 238, 144));
    al_draw_rounded_rectangle(70,160,190, 190,3,3,al_map_rgb(0,0,0),1);
    al_draw_text(font,al_map_rgb(0,0,0), 90, 165,0, "OK! Rysuj");

    al_draw_filled_rounded_rectangle(230,160,350, 190,3,3, al_map_rgb(255, 182, 193));
    al_draw_rounded_rectangle(230,160,350, 190,3,3,al_map_rgb(0,0,0),1);
    al_draw_text(font,al_map_rgb(0,0,0), 260,165,0, "Zamknij");

    al_flip_display();

}


/*****************************************************************************************************************************/
/*   funkcja wypelniajaca okienko wpisywania wzoru funkcji                                                                  */
/***************************************************************************************************************************/
void draw_input_window_f(ALLEGRO_BITMAP *bitmap, double x_min_arg, double x_max_arg) {
//musze tło zostawiać caly czas tak samo wypelnione wiec korzystan z poprzedniej funkcji
    fill_input_window(bitmap);
    //wypisuywanie funkcji z klawiatury:
   al_draw_text(font,al_map_rgb(0,0,0), 75,55,0, text.c_str());
    //wypisanie wartosci minimalnej i maksymalnej
/*ale muszę uchronić się przed wpisywaniem blednych zakresow x
i tak jest uzytkownik bedzie chcial ustawic x_min>=x_max (co nie ma sensu)
to wtedy automatycznie ustawiam ten drugi argument, ktory akurat nie jest sterowany jako o 1 większy lub mniejszy*/

    al_draw_textf(font,al_map_rgb(0,0,0), 95,105,0, "%.0f", x_min_arg);//printf jakby tutaj dziala zeby konwertowac do const char *
    al_draw_textf(font,al_map_rgb(0,0,0), 270,105,0, "%.0f", x_max_arg);

    al_flip_display();
}


/*****************************************************************************************************************************/
/*                        MAIN                                                                                              */
/***************************************************************************************************************************/
int main(int argc, char** argv)
{
bool click_function=false;
bool click_min_p=false;
bool click_max_p=false;
bool click_min_m=false;
bool click_max_m=false;
double x_min=-5;
double x_max=5;

   ALLEGRO_DISPLAY *display = NULL, *input_display = NULL;//okienko do wykresow
    ALLEGRO_BITMAP *graph_bitmap, *input_bitmap;//okienko do kontaktu z uzytkownikiem

    if (!al_init() || !al_install_keyboard() || !al_install_mouse()) {
        cout << "Inicjalizacja nie powiodla sie." << endl; return -1;
    }
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

//czcionka - inicjowanie
al_init_font_addon();
al_init_ttf_addon();

    display = al_create_display(w, h);
    graph_bitmap = al_get_backbuffer(display);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display,"Graph");

    input_display = al_create_display(w1, h1);
    input_bitmap = al_get_backbuffer(input_display);
    al_set_window_position(input_display, 815, 0);
    fill_input_window(input_bitmap);//okienko konsoli musi miec od razu odpowiedni wyglad
    al_set_window_title( input_display,"Edit function - ONP");



ALLEGRO_EVENT_QUEUE *event_queue = NULL;
event_queue = al_create_event_queue();

//if(!display) analogicznie dla wszytskich okienek
    if (!event_queue ) {
        cout << "Inicjalizacja nie powiodla sie." << endl; return -1;
    }

al_register_event_source(event_queue, al_get_keyboard_event_source());
al_register_event_source(event_queue, al_get_mouse_event_source());

//czcionka - inicjowanie
al_init_font_addon();
al_init_ttf_addon();
font = al_load_ttf_font("arial.ttf",20,0 );

    if (!font) {
        cout << "Inicjalizacja czcionki nie powiodla sie." << endl; return -1;
    }

//chcemy, zeby moc obslugiwac program i myszką i klawiaturą
//gdy jest jakas akcja z naszej strony
 while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

//musze reagowac na klikniecia myszką oraz wciskanie klawiatury
/*switch (ev.type) {
            case ALLEGRO_EVENT_KEY_CHAR: cout << "ALLEGRO_EVENT_KEY_CHAR"<< ev.keyboard.unichar << endl; break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: cout << "ALLEGRO_EVENT_MOUSE_BUTTON_DOWN";break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: cout << "ALLEGRO_EVENT_MOUSE_BUTTON_UP";break;
            case ALLEGRO_EVENT_MOUSE_AXES: cout << "ALLEGRO_EVENT_MOUSE_AXES"; break;//nie chce zeby cos sie dzialo
            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY: cout << "ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY"; break;//nie chce zeby cos sie dzialo
            case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY: cout << "ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY"; break;//nie chce zeby cos sie dzialo
            default: break;
}
 cout << endl;*/

 /*przechowuje informacje czy klikniete myszka w odpowiedni prostokącik*/
 if (ev.type ==ALLEGRO_EVENT_MOUSE_AXES){/*nic nie robie gdy po prostu sobie przesuwam myszkę*/}

 else if (ev.type ==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
             mouse_x = ev.mouse.x;
             mouse_y = ev.mouse.y;

    if (mouse_x >=70 && mouse_x<=350 && mouse_y>=50 && mouse_y<=80){
                click_function=true; click_min_p=false; click_max_p=false; click_min_m=false; click_max_m=false;}

/*gdy kliknieto w strzalke do manewrowania zakresem x
tutaj od razu kontroluje to zeby zakres mial sens tzn byl dlugosci co najmniej 1 */
    else if (mouse_x >=140 && mouse_x<=165 && mouse_y>=100 && mouse_y<=115){
            x_min+=1;
            if (x_min<x_max-1)draw_input_window_f(input_bitmap, x_min, x_max);
            else x_max = x_min+1; draw_input_window_f(input_bitmap, x_min, x_max);}

    else if (mouse_x >=140 && mouse_x<=165 && mouse_y>=115 && mouse_y<=130){
            x_min-=1;
            if (x_min<x_max-1)draw_input_window_f(input_bitmap, x_min, x_max);
            else x_max = x_min+1; draw_input_window_f(input_bitmap, x_min, x_max);}

    else if (mouse_x >=315 && mouse_x<=340 && mouse_y>=100 && mouse_y<=115){
            x_max+=1;
            if (x_min<x_max-1)draw_input_window_f(input_bitmap, x_min, x_max);
            else x_min = x_max-1; draw_input_window_f(input_bitmap, x_min, x_max);}

    else if (mouse_x >=315 && mouse_x<=340 && mouse_y>=115 && mouse_y<=130){
            x_max-=1;
            if (x_min<x_max-1)draw_input_window_f(input_bitmap, x_min, x_max);
            else x_min = x_max-1; draw_input_window_f(input_bitmap, x_min, x_max);}

/*gdy kliknieto w przycisk "OK!Rysuj" to wywolana te sama procedura jak przy Enter*/
    else if (mouse_x >=70 && mouse_x<=190 && mouse_y>=160 && mouse_y<=190){
            draw_input_window_f(input_bitmap, x_min, x_max);
                calculate(text, x_min, x_max);
                draw_graph_window(graph_bitmap, x_min, x_max);}

/*gdy kliknieto w przycisk "Zamknij" to zamykam działanie programu*/
    else if (mouse_x >=230 && mouse_x<=350 && mouse_y>=160 && mouse_y<=190){
            exit (EXIT_FAILURE);}

/*na wszystkie inne klikniecia myszka program nie reaguje*/
    else {};
}

/* naciśniecie entera zawsze skutkuje narysowaniem sie wykresu funkcji bez wzgledu gdzie jest kursor*/
 else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                draw_input_window_f(input_bitmap, x_min, x_max);
                calculate(text, x_min, x_max);
                draw_graph_window(graph_bitmap, x_min, x_max);}

/*jak naciskam backspace i akurat jestem w linii pisania wzoru funkcji*/
else if(!text.empty() && ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE
        && click_function==true && click_min_p==false && click_max_p==false && click_min_m==false && click_max_m==false){
            text.pop_back();
            draw_input_window_f(input_bitmap, x_min, x_max);
        }
/*jesli backspace w okienku funkcji ale nie ma tam nic do usunięcia*/
else if(text.empty() && ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && click_function==true && click_min_p==false && click_max_p==false
                        && click_min_m==false && click_max_m==false){}

/*jesli cokolwiek wcisnelam innego co mozna wpisac do okienka funkcji*/
else if(ev.type == ALLEGRO_EVENT_KEY_CHAR && ev.keyboard.keycode != ALLEGRO_KEY_BACKSPACE && ev.keyboard.keycode != ALLEGRO_KEY_ENTER
        && click_function==true && click_min_p==false && click_max_p==false && click_min_m==false && click_max_m==false ){
            text.push_back(ev.keyboard.unichar);
            draw_input_window_f(input_bitmap, x_min, x_max);}

 }

al_destroy_event_queue(event_queue);

//string tmp;
//getline(cin, tmp);
//al_destroy_display(display);

    return 0;
}
