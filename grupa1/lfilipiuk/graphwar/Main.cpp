#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
#include <sstream>
#include "parser.h"

#include<io.h>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace std;

const int w = 800;
const int h = 500;
const int h_menu = 150;
const float pr_gracza = 10;

int czas;

int liczba_gracz1 = 1; // liczba "pionkow" gracza 1
int liczba_gracz2 = 1; // liczba "pionkow" gracza 2
string napis1, napis2; // NAZWY graczy
string funkcja_menu;


bool wczytaj; //wcisniecie przycisku WCZYTAJ
bool start; //wcisniecie przycisku START
bool aktywny_rysuj = true;

int liczba, przesuniecie; // liczba "pionkow" aktywnego gracza; przesuniecie - zmienna pomocnicza
bool gracz1, gracz2; // zmienne 0-1 - ktory gracz jest wybrany
char litera;

// Funkcja zwraca wartosc prawda, jesli uzytkownik kliknal w wyznaczony obszar
bool Click(int x, int y, int x1, int y1, int x2, int y2){
if(x>=x1 && x<=x2 && y>=y1 && y<=y2)
    return true;
return false;
}

//Funkcja zwieksza/zmniejsza liczbe "pionkow" danego gracza
void Znak(bool lewy, bool up){
    if(lewy){
        if(up)
            liczba_gracz1++;
        else
            liczba_gracz1--;

        if(liczba_gracz1 == 0)
            liczba_gracz1 = 1;
        if(liczba_gracz1 == 5)
            liczba_gracz1 = 4;

        liczba = liczba_gracz1;
        przesuniecie = 0;
    }
    else{
        if(up)
            liczba_gracz2++;
        else
            liczba_gracz2--;

        if(liczba_gracz2 == 0)
            liczba_gracz2 = 1;
        if(liczba_gracz2 == 5)
            liczba_gracz2 = 4;

        liczba = liczba_gracz2;
        przesuniecie = 225;
    }

}

// Funkcja zamienia typ double na string
string double2string(const double x){
    ostringstream stream;
    stream << x;
    return stream.str();
}

// Funkcja oblicza wartosc funkcji
double wartosc(double x, char* expression){
    Parser prs;
    const char *s = "x=";

    string string_x = double2string(x);
    char const *char_x = string_x.c_str();

    char *t = new char[strlen(char_x)+strlen(s)+1];
    strcpy(t, s);
    strcat(t, char_x);

    prs.parse(t);
    return atof(prs.parse(expression));
}

double pixel_na_wsp_x(float x) {return (x-(w/2))/20;}

float wsp_na_pixel_x(double x) {return (x+20)*20;}

double pixel_na_wsp_y(float y) {return (y-(h/2))/(-20);}

float wsp_na_pixel_y(double y) {return (y-12.5)*(-20);}

class gracz
{
    float x, y, r;
    bool zywy, lewy;
public:
    gracz(float _x, float _y, bool _lewy, bool _true){
        x = _x;
        y = _y;
        r = pr_gracza;
        zywy = _true;
        lewy = _lewy;
    }

    void rysuj_gracza(){
        ALLEGRO_COLOR blue = al_map_rgb(0,0,255);
        ALLEGRO_COLOR green = al_map_rgb(0,255,0);
        ALLEGRO_BITMAP *ball_1 = al_load_bitmap("Images/ball_1.png");
        ALLEGRO_BITMAP *ball_2 = al_load_bitmap("Images/ball_2.png");
        if(lewy)
            al_draw_bitmap(ball_1,x-10,y-10,0);
        else
            al_draw_bitmap(ball_2,x-10,y-10,0);
            //al_draw_filled_circle(x, y, r, green);

        al_destroy_bitmap(ball_1);
        al_destroy_bitmap(ball_2);
    }

    void rysuj_gracza_aktywnego(){
        ALLEGRO_BITMAP *ball_1_glow = al_load_bitmap("Images/ball_1_glow.png");
        ALLEGRO_BITMAP *ball_2_glow = al_load_bitmap("Images/ball_2_glow.png");

        if(lewy)
            al_draw_bitmap(ball_1_glow,x-16,y-16,0);
        else
            al_draw_bitmap(ball_2_glow,x-16,y-16,0);
    }

    float   get_x()     {return x;}
    float   get_y()     {return y;}
    float   get_r()     {return r;}
    bool    get_lewy()  {return lewy;}
    bool    get_zywy()  {return zywy;}
    void    set_x(float _x)     {x = _x;}

    bool czy_gracz_trafiony(float xx, float yy){
        if ( (xx-x)*(xx-x) + (yy-y)*(yy-y) < r*r)
            return TRUE;
        else
            return FALSE;
    }

    void smierc_gracza (){
        zywy = FALSE;
    }
};

class przeszkoda
{
    float x, y, r;
public:
    przeszkoda(float _x, float _y, float _r){
        x = _x;
        y = _y;
        r = _r;
    }

    void rysuj_przeszkode(){
        ALLEGRO_COLOR grey = al_map_rgb(100,100,100);
        al_draw_filled_circle(x, y, r, grey);
    }


    bool czy_zderzenie(float xx, float yy){
        if((xx-x)*(xx-x) + (yy-y)*(yy-y) < r*r)
            return TRUE;
        else
            return FALSE;
    }

    float get_x() {return x;}
    float get_y() {return y;}
    float get_r() {return r;}
    void set_x(float _x) {x = _x;}
};

class wyrwa
{
    float x, y, r;
public:
    wyrwa(float _x, float _y){
        x = _x; y = _y; r = 20; //wielkosc wyrwy
    }

    void rysuj_wyrwe(){
        ALLEGRO_COLOR grey = al_map_rgb(245,246,247);
        al_draw_filled_circle(x, y, r, grey);
    }

    float get_wyrwa_x() {return x;}
    float get_wyrwa_y() {return y;}
    float get_wyrwa_r() {return r;}
    void set_x(float _x) {x = _x;}
};

class mapa
{
    int liczba_graczy, liczba_przeszkod;
    int runda, kolejka1, kolejka2;
    int czas_zapis;
    string mapa_napis1, mapa_napis2;
    vector<przeszkoda> przeszkody;
    vector<wyrwa> wyrwy;
public:
    vector<gracz> gracze;

    void kill()
    {
        delete this;
    }

    void wczytaj(){
        ifstream infile;
        infile.open("zapis.txt");
        int liczba_obiektow;
        float x, y, r;
        bool lewy, zywy;
        infile >> liczba_obiektow;
        liczba_graczy = liczba_obiektow/2;
        for (int i=0; i<liczba_obiektow; i++){
            infile >> x;
            infile >> y;
            infile >> r;
            infile >> lewy;
            infile >> zywy;
            gracz gr(x, y, lewy, zywy);
            gracze.push_back(gr);
        }
        infile >> liczba_obiektow;
        liczba_przeszkod = liczba_obiektow;
        for (int i=0; i< liczba_obiektow; i++){
            infile >> x;
            infile >> y;
            infile >> r;
            przeszkoda prz(x, y, r);
            przeszkody.push_back(prz);
        }
        infile >> liczba_obiektow;
        for (int i=0; i<liczba_obiektow; i++){
            infile >> x;
            infile >> y;
            infile >> r;
            wyrwa wyr(x, y);
            wyrwy.push_back(wyr);
        }
        infile >> runda;
        infile >> kolejka1;
        infile >> kolejka2;
        infile >> mapa_napis1;
        infile >> mapa_napis2;
        infile >> czas_zapis;
        infile.close();
    }

    void odwrocenie_danych(){
        float schowek;
        for (int i=0; i<liczba_przeszkod; i++){
            schowek = przeszkody[i].get_x();
            przeszkody[i].set_x(w-schowek);
        }
        for (int i=0; i<liczba_graczy_na_planszy(); i++){
            schowek = gracze[i].get_x();
            gracze[i].set_x(w - schowek);
        }
        for (int i=0; i<wyrwy.size(); i++)
        {
            schowek = wyrwy[i].get_wyrwa_x();
            wyrwy[i].set_x(w - schowek);
        }
    }

    mapa(){
        liczba_graczy=8;
        liczba_przeszkod=10;
    }

    void losuj(int _liczba_graczy){
        kolejka1=0;
        kolejka2=1;
        runda=0;
        liczba_graczy = _liczba_graczy;
        srand(time(NULL));
        liczba_przeszkod = /3 + rand()%17;
        for (int i=1; i<=liczba_przeszkod; i++){ // losowanie przeszkod
            float x = rand() % (w);
            float y = rand() % (h);
            float r = 20 + rand() % (55);
            przeszkoda p(x, y, r);
            przeszkody.push_back(p);
        }
        for (int j=1; j<=2*liczba_graczy; j++){ // losowanie graczy
            float x, y;
            bool lewy = FALSE;
            if (j%2 == 1)
                lewy = TRUE;
            bool dobra_pozycja = FALSE;
            while (!dobra_pozycja){
                if(lewy == TRUE){
                    x = 15 + rand() % ((w/2)-30);
                    y = 15 + rand() % (h-30);
                }
                else{
                    x = w/2 + 15 + rand() % ((w/2)-30);
                    y = 15 + rand() % (h-30);
                }
                bool pozycja = TRUE;
                for (int i=0; i<liczba_przeszkod; i++){
                    float xx = przeszkody[i].get_x();
                    float yy = przeszkody[i].get_y();
                    float rr = przeszkody[i].get_r();
                    if((xx-x)*(xx-x) + (yy-y)*(yy-y) < (rr+15)*(rr+15) )
                        pozycja = FALSE;
                }
                for (int i=0; i<j-2 ;i++){
                    float xxx = gracze[i].get_x();
                    float yyy = gracze[i].get_y();
                    float rrr = gracze[i].get_r();
                    if((xxx-x)*(xxx-x) + (yyy-y)*(yyy-y) < (rrr+15)*(rrr+15) )
                        pozycja = FALSE;
                }
                if (pozycja == TRUE){
                gracz gr(x, y, lewy, true);
                gracze.push_back(gr);
                dobra_pozycja = TRUE;
                }
            }
        }
    }

    // RYSOWANIE MAPY
    void rysuj_mape(int aktywny_gracz){

        // KOLORY
        ALLEGRO_COLOR l_grey = al_map_rgb(245,246,247);
        ALLEGRO_COLOR d_grey = al_map_rgb(205,205,205);
        ALLEGRO_COLOR black = al_map_rgb(0,0,0);
        ALLEGRO_COLOR white = al_map_rgb(255,255,255);

        // FONTY
        ALLEGRO_FONT *font_gracz = al_load_font("Fonts/8-Bit Madness.ttf", 30, ALLEGRO_KEYMOD_CAPSLOCK);
        ALLEGRO_FONT* font = al_load_font("Fonts/PIXEARG_.ttf", 18, ALLEGRO_KEYMOD_CAPSLOCK);

        const char *napis1_char = napis1.c_str();
        const char *napis2_char = napis2.c_str();

        ALLEGRO_BITMAP *Menu = al_load_bitmap("Images/menu.png");

        al_clear_to_color(l_grey);
        al_draw_line(0, h/2, w, h/2, d_grey, 2);
        al_draw_line(w/2,0, w/2, h, d_grey, 2);
        for (int i=0; i<liczba_przeszkod; i++){
            przeszkody[i].rysuj_przeszkode();
        }
        for (int i=0; i<wyrwy.size(); i++){
            wyrwy[i].rysuj_wyrwe();
              if(abs(wyrwy[i].get_wyrwa_y()-h/2) < wyrwy[i].get_wyrwa_r()){
                  al_draw_line(wyrwy[i].get_wyrwa_x()-sqrt(pow(wyrwy[i].get_wyrwa_r(),2)-pow(abs(wyrwy[i].get_wyrwa_y()-h/2),2)),
                               h/2, wyrwy[i].get_wyrwa_x()+sqrt(pow(wyrwy[i].get_wyrwa_r(),2)-pow(abs(wyrwy[i].get_wyrwa_y()-h/2),2)),
                               h/2, d_grey,2);
              }
              if(abs(wyrwy[i].get_wyrwa_x()-w/2)< wyrwy[i].get_wyrwa_r()){
                  al_draw_line(w/2,wyrwy[i].get_wyrwa_y()-sqrt(pow(wyrwy[i].get_wyrwa_r(),2)-pow(abs(wyrwy[i].get_wyrwa_x()-w/2),2)),
                               w/2,wyrwy[i].get_wyrwa_y()+sqrt(pow(wyrwy[i].get_wyrwa_r(),2)-pow(abs(wyrwy[i].get_wyrwa_x()-w/2),2)),
                               d_grey, 2 );
              }
        }

        for (int i=0; i<2*liczba_graczy; i++){
            if(gracze[i].get_zywy()){
                if(i == aktywny_gracz){ //AKTYWNY GRACZ
                    if(aktywny_rysuj) gracze[i].rysuj_gracza();
                    if(aktywny_rysuj) gracze[i].rysuj_gracza_aktywnego();
                }
                else
                    gracze[i].rysuj_gracza();
            }
        }

        // RYSOWANIE MENU
        al_draw_bitmap(Menu,0,500,0);

        // RYSOWANIE WSKAZOWKI
        al_draw_line(697,570, 697 + 40*sin(6.28*czas/60),570 - 40*cos(6.28*czas/60),black,2);

        // RYSOWANIE NICKOW GRACZY
        if(gracz1)
            al_draw_text(font_gracz,black,97,522,0,napis1_char);
        else
            al_draw_text(font_gracz,black,97,522,0,napis2_char);

        // RYSOWANIE FUNKCJI
        //const char *funkcja_menuChar = funkcja_menu.c_str(); // XXX
        //al_draw_text(font, black, 105, 560, ALLEGRO_ALIGN_LEFT, funkcja_menuChar);

        al_destroy_bitmap(Menu);
        al_destroy_font(font_gracz);
        al_destroy_font(font);
    }

    bool czy_zderzenie(float x, float y){

        int w_obszarze = 0;
        for (int i=0; i<liczba_przeszkod; i++){
            float p_x = przeszkody[i].get_x();
            float p_y = przeszkody[i].get_y();
            float p_r = przeszkody[i].get_r();
            if( (x-p_x)*(x-p_x) + (y-p_y)*(y-p_y) <= p_r*p_r )
                w_obszarze++;
        }

            if(w_obszarze > 0){
                bool czy_wewnatrz = FALSE;
                for (int j=0; j<wyrwy.size(); j++){
                    float w_x = wyrwy[j].get_wyrwa_x();
                    float w_y = wyrwy[j].get_wyrwa_y();
                    float w_r = wyrwy[j].get_wyrwa_r();
                    if( (x-w_x)*(x-w_x) + (y-w_y)*(y-w_y) < w_r*w_r )
                        czy_wewnatrz = TRUE;
                }
                if (!czy_wewnatrz)
                    return TRUE;
                else
                    return FALSE;
            }
            else
                return FALSE;
    }

    bool czy_koniec_planszy(float x, float y){
        if (x < w && y > 0 && y < h)
            return FALSE;
        else
            return TRUE;
    }

    bool czy_trafienie_gracza(float x, float y){
        bool trafienie = FALSE;
        for (int i=0; i<2*liczba_graczy; i++){
            if (gracze[i].get_zywy()){
            if (gracze[i].czy_gracz_trafiony(x, y))
                trafienie = TRUE;
            }
        }
        return trafienie;
    }

    void dodaj_wyrwe(float x, float y){
        wyrwa w(x, y);
        wyrwy.push_back(w);
    }

    int ktory_gracz_trafiony(float x, float y){
        int ktory;
        for (int i=0; i<2*liczba_graczy; i++){
            if(gracze[i].czy_gracz_trafiony(x, y))
                ktory = i;
        }
        return ktory;
    }

    void smierc_gracza(int i){
        gracze[i].smierc_gracza();
    }

    bool czy_gracz_zywy(int i){
        if(gracze[i].get_zywy())
            return TRUE;
        else
            return FALSE;
    }

    float gracz_get_x(int i) {return gracze[i].get_x();}
    float gracz_get_y(int i) {return gracze[i].get_y();}
    float gracz_get_r(int i) {return gracze[i].get_r();}
    float przeszkoda_get_x(int i) {return przeszkody[i].get_x();}
    float przeszkoda_get_y(int i) {return przeszkody[i].get_y();}
    float przeszkoda_get_r(int i) {return przeszkody[i].get_r();}
    float wyrwa_get_x(int i) {return wyrwy[i].get_wyrwa_x();}
    float wyrwa_get_y(int i) {return wyrwy[i].get_wyrwa_y();}
    float wyrwa_get_r(int i) {return wyrwy[i].get_wyrwa_r();}
    int liczba_przeszkod_na_planszy() {return przeszkody.size();}
    int liczba_wyrw_na_panszy() {return wyrwy.size();}
    int liczba_graczy_na_planszy()      {return 2*liczba_graczy;}
    bool gracz_get_lewy(int i) {return gracze[i].get_lewy();}
    bool gracz_get_zywy(int i) {return gracze[i].get_zywy();}
    int get_runda() {return runda;}
    int get_kolejka1() {return kolejka1;}
    int get_kolejka2() {return kolejka2;}
    string get_imie1() {return mapa_napis1;}
    string get_imie2() {return mapa_napis2;}
    int get_czas() {return czas_zapis;}
    bool zawodnik_zywy(bool lewy){
        bool zywy=FALSE;
        for (int i=0; i<2*liczba_graczy;i++){
            if (gracze[i].get_lewy()==lewy){
                if (gracze[i].get_zywy())
                    zywy = TRUE;
                }
        }
        return zywy;
    }
};

class funkcja
{
    float start_x, start_y;
    char expression[255];
public:
    funkcja(float _start_x, float _start_y, char expr[] )
    {
        start_x = _start_x, start_y = _start_y;
        strcpy(expression, expr);
    }

    void rysuj_funkcje(mapa &plansza, int aktywny_gracz){
        ALLEGRO_BITMAP *Wybuch = NULL;
        ALLEGRO_BITMAP *Wybuch_gracz = NULL;

        ALLEGRO_SAMPLE *eksplozja_kamien = al_load_sample("Sounds/eksplozja_kamien.WAV");
        ALLEGRO_SAMPLE *eksplozja_gracz = al_load_sample("Sounds/eksplozja_gracz.wav");

        ALLEGRO_COLOR kolor_strzalu;
        ALLEGRO_COLOR blue = al_map_rgb(25, 157, 181);
        ALLEGRO_COLOR red = al_map_rgb(181,65,25);
        if(gracz1)
            kolor_strzalu = blue;
        else
            kolor_strzalu = red;

        //

        Wybuch = al_load_bitmap("Images/wybuch.png");
        Wybuch_gracz = al_load_bitmap("Images/wybuch_gracz.png");

        vector<double> T;  //wektor wartosci we wspolrzednych
        float x = start_x;
        double yy = wartosc(pixel_na_wsp_x(x), expression);
        double stala = pixel_na_wsp_y(start_y) - wartosc(pixel_na_wsp_x(x), expression);  // wartosc we wspolrzednych
        while (!plansza.czy_koniec_planszy(x, wsp_na_pixel_y(yy+stala)) && !plansza.czy_zderzenie(x, wsp_na_pixel_y(yy+stala))
                    && !plansza.czy_trafienie_gracza(x, wsp_na_pixel_y(yy+stala)))
            {
                for (int i=0; i<40; i++){
                    T.push_back(wartosc(pixel_na_wsp_x(x), expression));
                    x=x+0.1;
                }
                plansza.rysuj_mape(aktywny_gracz);

                for (int i=0; i<T.size(); i++){
                    al_draw_pixel(start_x+(0.1*i),wsp_na_pixel_y(T[i]+stala),kolor_strzalu);
                }
                al_flip_display();
                al_rest(0.01);
                yy = T[T.size()-1];
            }
        if(plansza.czy_zderzenie(x, wsp_na_pixel_y(yy+stala))){
            plansza.dodaj_wyrwe(x, wsp_na_pixel_y(yy+stala));

            al_play_sample(eksplozja_kamien,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                for(int i=0;i<9;i++){
                    plansza.rysuj_mape(aktywny_gracz);
                    al_draw_bitmap_region(Wybuch,71*i,0,71,64,x-35,wsp_na_pixel_y(yy+stala)-32,0);
                    al_flip_display();
                al_rest(0.06);
            }

            plansza.rysuj_mape(aktywny_gracz);
            al_flip_display();
        }
        if(plansza.czy_trafienie_gracza(x, wsp_na_pixel_y(yy+stala))){
            int ktory_gracz_trafiony = plansza.ktory_gracz_trafiony(x, wsp_na_pixel_y(yy+stala));

            int t_x = plansza.gracze[ktory_gracz_trafiony].get_x() - 16;
            int t_y = plansza.gracze[ktory_gracz_trafiony].get_y()- 16;

            al_play_sample(eksplozja_gracz,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);

            for(int i=0;i<4;i++){
                    plansza.rysuj_mape(aktywny_gracz);
                    al_draw_bitmap_region(Wybuch_gracz,32*i,0,32,32,t_x,t_y,0);
                    al_flip_display();
            al_rest(0.05);
            }

            plansza.smierc_gracza(ktory_gracz_trafiony);

            for(int i=4;i<10;i++){
                    plansza.rysuj_mape(aktywny_gracz);
                    al_draw_bitmap_region(Wybuch_gracz,32*i,0,32,32,t_x,t_y,0);
                    al_flip_display();
            al_rest(0.05);
            }

            plansza.rysuj_mape(aktywny_gracz);
            al_flip_display();
        }

        al_rest(2);
        al_destroy_bitmap(Wybuch);
        al_destroy_bitmap(Wybuch_gracz);
        al_destroy_sample(eksplozja_gracz);
        al_destroy_sample(eksplozja_kamien);
    }

};

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY *display = NULL;

    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_init_acodec_addon();
    al_init_image_addon();

    // KOLEJKA ZDARZEN
    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();

    // FONTY
    ALLEGRO_FONT* menu_font = al_load_font("Fonts/8-Bit Madness.ttf", 30, ALLEGRO_KEYMOD_CAPSLOCK);
    ALLEGRO_FONT* font = al_load_font("Fonts/PIXEARG_.ttf", 18, ALLEGRO_KEYMOD_CAPSLOCK);
    ALLEGRO_FONT* font_winner = al_load_font("Fonts/8-Bit Madness.ttf", 40, ALLEGRO_KEYMOD_CAPSLOCK);
    ALLEGRO_FONT* font_winner_big = al_load_font("Fonts/8-Bit Madness.ttf", 80, ALLEGRO_KEYMOD_CAPSLOCK);
    ALLEGRO_TIMER* timer = al_create_timer(1.0/1);
    ALLEGRO_MOUSE_STATE state;

    // KOLORY
    ALLEGRO_COLOR black = al_map_rgb(0,0,0);
    ALLEGRO_COLOR white = al_map_rgb(255,255,255);

    // DZWIEKI
    al_reserve_samples(2); // dwa dzwieki w tle
    ALLEGRO_SAMPLE *strzal = al_load_sample("Sounds/strzal.wav");
    ALLEGRO_SAMPLE *klik = al_load_sample("Sounds/click.wav");
    ALLEGRO_SAMPLE *klik_select = al_load_sample("Sounds/click_select.wav");
    ALLEGRO_SAMPLE *tick = al_load_sample("Sounds/TIMERTICK.WAV");
    ALLEGRO_SAMPLE *klawiatura_klik = al_load_sample("Sounds/KEYCLICK.WAV");
    ALLEGRO_SAMPLE *klawiatura_erase = al_load_sample("Sounds/KEYERASE.WAV");
    ALLEGRO_SAMPLE *fanfary = al_load_sample("Sounds/fanfary.wav");

    // DZWIEKI - podklad
    ALLEGRO_SAMPLE *song_menu = al_load_sample("Sounds/fanfary.wav");
    ALLEGRO_SAMPLE_INSTANCE *song_menuInstance = al_create_sample_instance(song_menu);

    al_set_sample_instance_playmode(song_menuInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(song_menuInstance, al_get_default_mixer());

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    if (!al_init() || !al_install_mouse() || !al_install_keyboard()) {
        cout << "Inicjalizacja nie powiodÂła siĂŞ." << endl; return -1;
    }

    int x,y;
    bool koniec = false;

    timer = al_create_timer(1.0);
    display = al_create_display(800, 650);
    al_set_window_title(display, "GraphWar");

    // OBRAZY
    // OBRAZY - menu
    ALLEGRO_BITMAP *Tlo = al_load_bitmap("Images/tlo.png");
    ALLEGRO_BITMAP *Triangle = al_load_bitmap("Images/triangle.png");
    ALLEGRO_BITMAP *Triangle_cover = al_load_bitmap("Images/triangle_cover.png");
    ALLEGRO_BITMAP *Wczytaj_0 = al_load_bitmap("Images/wczytaj_0.png");
    ALLEGRO_BITMAP *Wczytaj_1 = al_load_bitmap("Images/wczytaj_1.png");
    ALLEGRO_BITMAP *Start_0 = al_load_bitmap("Images/start_0.png");
    ALLEGRO_BITMAP *Start_1 = al_load_bitmap("Images/start_1.png");
    ALLEGRO_BITMAP *Zamknij_0 = al_load_bitmap("Images/zamknij_0.png");
    ALLEGRO_BITMAP *Zamknij_1 = al_load_bitmap("Images/zamknij_1.png");
    ALLEGRO_BITMAP *Dol_cover = al_load_bitmap("Images/dol_cover.png");
    ALLEGRO_BITMAP *Plus_0 = al_load_bitmap("Images/plus_0.png");
    ALLEGRO_BITMAP *Plus_1 = al_load_bitmap("Images/plus_1.png");
    ALLEGRO_BITMAP *Minus_0 = al_load_bitmap("Images/minus_0.png");
    ALLEGRO_BITMAP *Minus_1 = al_load_bitmap("Images/minus_1.png");
    ALLEGRO_BITMAP *Znak_cover = al_load_bitmap("Images/znak_cover.png");
    ALLEGRO_BITMAP *Liczba_1 = al_load_bitmap("Images/liczba_1.png");
    ALLEGRO_BITMAP *Liczba_2 = al_load_bitmap("Images/liczba_2.png");
    ALLEGRO_BITMAP *Liczba_3 = al_load_bitmap("Images/liczba_3.png");
    ALLEGRO_BITMAP *Liczba_4 = al_load_bitmap("Images/liczba_4.png");
    ALLEGRO_BITMAP *Liczba_cover = al_load_bitmap("Images/liczba_cover.png");
    ALLEGRO_BITMAP *Napis_cover = al_load_bitmap("Images/napis_cover.png");

    // OBRAZY - gra
    ALLEGRO_BITMAP *Winner = al_load_bitmap("Images/winner.png");
    ALLEGRO_BITMAP *Zapis = al_load_bitmap("Images/zapis.png");
    ALLEGRO_BITMAP *Tablica_pusta = al_load_bitmap("Images/tablica_pusta.png");
    ALLEGRO_BITMAP *Tablica_pusta_s = al_load_bitmap("Images/tablica_pusta_s.png");
    ALLEGRO_BITMAP *ball_1_active = al_load_bitmap("Images/ball_1_active.png");
    ALLEGRO_BITMAP *ball_2_active = al_load_bitmap("Images/ball_2_active.png");
    ALLEGRO_BITMAP *ball_1_odbicie = al_load_bitmap("Images/ball_1_odbicie.png");
    ALLEGRO_BITMAP *ball_2_odbicie = al_load_bitmap("Images/ball_2_odbicie.png");


    if (!timer || !display || !event_queue) {
        cout << "Inicjalizacja nie powiodła sie." << endl; return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // PIOSENKA
    //al_play_sample_instance(song_menuInstance);
Poczatek:
    liczba_gracz1 = 1;
    liczba_gracz2 = 1;
    wczytaj = false;
    napis1="";
    napis2="";

    // WCZYTANIE OBRAZOW
    al_draw_bitmap(Tlo,0,0,0);
    al_draw_bitmap(Wczytaj_0,176,502,0);
    al_draw_bitmap(Zamknij_0,437,502,0);
    al_draw_bitmap(Start_0,176,445,0);
    al_draw_bitmap(Plus_0,191,324,0);
    al_draw_bitmap(Minus_0,191,373,0);
    al_draw_bitmap(Liczba_1,253,324,0);

    // PETLA MENU
    while (true) {
        al_flip_display();
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

      // KLIKNIECIE MYSZA
      if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            al_get_mouse_state(&state); // pobierane sa wspĂłlrzedne klikniecia
            x = al_get_mouse_state_axis(&state,0);
            y = al_get_mouse_state_axis(&state,1);
            //cout<<x <<":"<<y<<endl;

            if(Click(x,y,191,239,395,276)){ // GRACZ 1 - zakrycie znacznikĂłw, wstawienie nowego
                al_draw_bitmap(Triangle_cover, 279+5,291,0);
                al_draw_bitmap(Triangle_cover, 502+5,291,0);
                al_draw_bitmap(Triangle, 279+5,291,0);
                al_play_sample(klik_select, 0.4,0,1.1, ALLEGRO_PLAYMODE_ONCE,0);
                al_rest(0.1);
                gracz1 = true; // Ustalenie aktywnego gracza
                gracz2 = false;
            }
            else{ // KlikniĂŞcie w inne miejsce powoduje zakrycie obu znacznikĂłw i dezaktywacje obu graczy
               al_draw_bitmap(Triangle_cover, 279+5,291,0);
               al_draw_bitmap(Triangle_cover, 502+5,291,0);
               gracz1 = false;
               gracz2 = false;
            }

            if(Click(x,y,414,239,621,276)){ //GRACZ 2 - zakrycie znacznikĂłw, wstawienie nowego
                al_draw_bitmap(Triangle_cover, 279+5,291,0);
                al_draw_bitmap(Triangle_cover, 502+5,291,0);
                al_draw_bitmap(Triangle, 502+5,291,0);
                al_play_sample(klik_select, 0.4,0,1.1, ALLEGRO_PLAYMODE_ONCE,0);
                al_rest(0.1);
                gracz1 = false;
                gracz2 = true; // Ustalenie aktywnego gracza
            }

            if(Click(x,y,176,502,375,551)){ // WCZYTAJ - symulacja wcisniecia przycisku
                al_draw_bitmap(Dol_cover, 176,502,0);
                al_draw_bitmap(Wczytaj_1, 176,502+6,0);
                al_play_sample(klik, 1,0,1.1, ALLEGRO_PLAYMODE_ONCE,0);
                al_rest(0.1);
                al_flip_display();

                al_rest(0.1);
                al_draw_bitmap(Dol_cover, 176,502,0);
                al_draw_bitmap(Wczytaj_0,176,502,0);
                al_flip_display();
                al_rest(0.1);

                if(_access("zapis.txt",0) != -1){
                    wczytaj = true;
                    goto Gra;
                }
            }

            if(Click(x,y,437,502,638,551)){ //ZAMKNIJ - symulacja wcisniecia przycisku
                al_draw_bitmap(Dol_cover, 437,502,0);
                al_draw_bitmap(Zamknij_1, 437,502+6,0);
                al_play_sample(klik, 1,0,1.1, ALLEGRO_PLAYMODE_ONCE,0);
                al_rest(0.1);
                al_flip_display();

                al_rest(0.1);
                al_draw_bitmap(Dol_cover, 437,502,0);
                al_draw_bitmap(Zamknij_0,437,502,0);
                al_flip_display();
                al_rest(0.1);
                koniec = true; // Zamkniecie aplikacji
                goto Gra;
            }

            if(Click(x,y,176,445,375,489)){ //START - symulacja wcisniecia przycisku
                al_draw_bitmap(Dol_cover, 176,445,0);
                al_draw_bitmap(Start_1, 176,445+6,0);
                al_play_sample(klik, 1,0,1.1, ALLEGRO_PLAYMODE_ONCE,0);
                al_rest(0.1);
                al_flip_display();

                al_rest(0.1);
                al_draw_bitmap(Dol_cover, 176,445,0);
                al_draw_bitmap(Start_0,176,445,0);
                al_flip_display();
                al_rest(0.1);

                start = true;
                goto Gra;
            }

            // Jesli kliknieto w dowolny '+' albo '-'
            if(Click(x,y,191,324,225,358) || Click(x,y,191,373,225,405) /*|| Click(x,y,418,324,451,358) || Click(x,y,418,373,451,405)*/){

                if(Click(x,y,191,324,225,358)){ // LEWY PLUS
                    al_draw_bitmap(Znak_cover, 191,324,0);
                    al_draw_bitmap(Plus_1, 191,324+6,0);
                    al_play_sample(klik, 1,0,1.1, ALLEGRO_PLAYMODE_ONCE,0);
                    al_rest(0.1);
                    al_flip_display();

                    al_rest(0.1);
                    al_draw_bitmap(Znak_cover, 191,324,0);
                    al_draw_bitmap(Plus_0,191,324,0);

                    Znak(1,1);
                }

                if(Click(x,y,191,373,225,405)){ // LEWY PLUS
                    al_draw_bitmap(Znak_cover, 191,373,0);
                    al_draw_bitmap(Minus_1, 191,373+6,0);
                    al_play_sample(klik, 1,0,1.1, ALLEGRO_PLAYMODE_ONCE,0);
                    al_rest(0.1);
                    al_flip_display();

                    al_rest(0.1);
                    al_draw_bitmap(Znak_cover, 191,373,0);
                    al_draw_bitmap(Minus_0,191,373,0);

                    Znak(1,0);
                }

                al_draw_bitmap(Liczba_cover,253 + przesuniecie,324,0); // ZMIANA NUMERU
                switch(liczba){
                    case(1): al_draw_bitmap(Liczba_1,253 + przesuniecie,324,0); break;
                    case(2): al_draw_bitmap(Liczba_2,253 + przesuniecie,324,0); break;
                    case(3): al_draw_bitmap(Liczba_3,253 + przesuniecie,324,0); break;
                    case(4): al_draw_bitmap(Liczba_4,253 + przesuniecie,324,0); break;
                }
            }
        }

        // KLAWIATURA
        if(ev.type == ALLEGRO_EVENT_KEY_CHAR){
                if(ev.keyboard.keycode==75 || ev.keyboard.keycode==64 || ev.keyboard.keycode==59 || ev.keyboard.keycode==67){;}
                else
                {
                    if(gracz1 == true){ // Jesli GRACZ 1
                        if(ev.keyboard.keycode==63){ // BACKSPACE skraca napis
                            napis1 = napis1.substr(0, napis1.size()-1);
                            al_play_sample(klawiatura_erase,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    else{
                        if(napis1.size()>=10) goto Dalej; // nick nie moze byc dluzszy niz 10
                        al_play_sample(klawiatura_klik,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                        litera = ev.keyboard.unichar;
                        napis1.push_back(litera);
                    }
                    const char *tekst = napis1.c_str();
                    al_draw_bitmap(Napis_cover, 195,248,0); // zakrycie aktualnego napisu
                    al_draw_text(menu_font, black, 195,248,ALLEGRO_KEYMOD_CAPSLOCK, tekst); //wstawienie nowego
                    }
                    if(gracz2 == true){ // Jesli GRACZ 2 - analogicznie
                        if(ev.keyboard.keycode==63){ //
                            napis2 = napis2.substr(0, napis2.size()-1);
                            al_play_sample(klawiatura_erase,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    else{
                        if(napis2.size()>10) goto Dalej;
                        al_play_sample(klawiatura_klik,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                        litera = ev.keyboard.unichar;
                        napis2.push_back(litera);
                    }
                    const char *tekst = napis2.c_str();
                    al_draw_bitmap(Napis_cover, 420,248,0);
                    al_draw_text(menu_font, black, 420, 248,ALLEGRO_KEYMOD_CAPSLOCK, tekst);
                }
                }
            }
        Dalej:;
    }

    //WYJSCIE Z PETLI MENU
Gra:
    if(napis1.size()==0) napis1 = "GRACZ_1"; // Jesli gracz nie ustalil nicku,
    if(napis2.size()==0) napis2 = "GRACZ_2"; // dostaje nick domyslny.

    if(koniec) return 0;
    bool czy_gra_z_zapisu = wczytaj;
    bool czy_czas_od_zera = true;
    bool czy_przed_chwila_zapis = false;

    int runda, kolejka1, kolejka2;
    int i, dlugosc_tekstu;
    bool koniec_ruchu=false, koniec_gry=false, koniec_wpisywania=false, koniec_czasu=false, zapisywanie=false;
    string podnapis, napis;
    char litera, tekst, podtekst;

Wczytaj:
    mapa plansza;
    if(czy_gra_z_zapisu==false){
        plansza.losuj(liczba_gracz1);
        plansza.rysuj_mape(0);
        al_rest(1);
        runda=0; kolejka1=0; kolejka2=1;
    }
    else{
        //cout << "WCZYTYWANIE..." << endl;
        plansza.wczytaj();
        plansza.rysuj_mape(0);
        al_rest(1);
        runda=plansza.get_runda();
        kolejka1=plansza.get_kolejka1();
        kolejka2=plansza.get_kolejka2();
        napis1=plansza.get_imie1();
        napis2=plansza.get_imie2();
        czas = plansza.get_czas();
        czy_czas_od_zera=false;
        czy_gra_z_zapisu=false;
    }

    const char *napis1_char = napis1.c_str();
    const char *napis2_char = napis2.c_str();

    // #########################################################################################
    // PETLA GRY
    while(!koniec_gry){

        // wybor gracza ktory bedzie oddawal strzal
        if(runda%2 == 0){
            while(!plansza.czy_gracz_zywy(kolejka1)){
                if(kolejka1 == plansza.liczba_graczy_na_planszy()-2)
                    kolejka1 = 0;
                else
                    kolejka1 = kolejka1 + 2;
            }
            i = kolejka1;
        }
        else{
            while(!plansza.czy_gracz_zywy(kolejka2)){
                if(kolejka2 == plansza.liczba_graczy_na_planszy()-1)
                    kolejka2 = 1;
                else
                    kolejka2 = kolejka2 + 2;
            }
            i = kolejka2;
        }

        if(!plansza.gracz_get_lewy(i)){
            plansza.odwrocenie_danych();
            gracz2 = true;
            gracz1 = false;
        }
        else{
            gracz1 = true;
            gracz2 = false;
        }

        //
        if(czy_czas_od_zera==true)
            czas = 0;
        else
            czy_czas_od_zera=true;

        koniec_wpisywania = false; koniec_czasu = false; napis = napis.substr(0,0);


        plansza.rysuj_mape(i);
        //al_start_timer(timer);

        if(czy_przed_chwila_zapis==false){
            //al_stop_timer(timer);
            al_draw_bitmap(Tablica_pusta_s,0,0,0); // rysowanie pustej tablicy, na ktorej wyswtetlany jest nick gracza
            if(gracz1) al_draw_text(font_winner_big,white,400,240,ALLEGRO_ALIGN_CENTRE,napis1_char); // wyswietlanie nicku gracza
            if(gracz2) al_draw_text(font_winner_big,white,400,240,ALLEGRO_ALIGN_CENTRE,napis2_char);
            al_flip_display();
            al_rest(1.2);
            plansza.rysuj_mape(i);
            al_rest(0.1);

            int t_x = plansza.gracze[i].get_x();
            int t_y = plansza.gracze[i].get_y();

            // animacja ruchu pionka
            aktywny_rysuj = false;
            for(int j=1; j<4; j++){
                plansza.rysuj_mape(i);
                if(gracz1) al_draw_bitmap_region(ball_1_odbicie,j*32,0,32,32,t_x-16,t_y-16,0);
                if(gracz2) al_draw_bitmap_region(ball_2_odbicie,j*32,0,32,32,t_x-16,t_y-16,0);
                al_flip_display();
                al_rest(0.1);
                }
            aktywny_rysuj = true;
        }
        else
            czy_przed_chwila_zapis==false;

        al_start_timer(timer);

        while(!koniec_wpisywania && !koniec_czasu){
            plansza.rysuj_mape(i);

            const char *tekst = napis.c_str();

            // sprawdzenie czy napis miesci sie w polu tekstowym
            dlugosc_tekstu = al_get_text_width(font, tekst);
            if(dlugosc_tekstu>420){
                podnapis = napis;
                const char *podtekst = napis.c_str();
                dlugosc_tekstu = al_get_text_width(font, podtekst);
                while(dlugosc_tekstu>420)
                {
                    podnapis = podnapis.substr(1, podnapis.length()-1);
                    const char *podtekst = podnapis.c_str();
                    dlugosc_tekstu = al_get_text_width(font, podtekst);
                }
                const char *ostateczny_napis = podnapis.c_str();
                al_draw_text(font, black, 105, 560,ALLEGRO_ALIGN_LEFT, ostateczny_napis);
                funkcja_menu = ostateczny_napis;
            }
            else{
                al_draw_text(font, black, 105, 560,ALLEGRO_ALIGN_LEFT, tekst);
                funkcja_menu = tekst;
            }

            al_flip_display();

            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN && events.keyboard.keycode==ALLEGRO_KEY_ESCAPE){
                koniec_gry = true;
                koniec_wpisywania = true;

                napis1.clear();
                napis2.clear();
            }

            if(events.type == ALLEGRO_EVENT_KEY_CHAR){
                if(events.keyboard.keycode==50){ //ZAPISZ
                    koniec_wpisywania=true;
                    koniec_gry=true;
                    zapisywanie=true;
                }
                else if(events.keyboard.keycode==63){ //BACKSPACE
                    napis = napis.substr(0, napis.size()-1);
                    al_play_sample(klawiatura_erase,0.7,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
                else if(events.keyboard.keycode==67) //ENTER
                    koniec_wpisywania=true;
                else if(events.keyboard.keycode==ALLEGRO_KEY_TAB){
                    int t_x = plansza.gracze[i].get_x();
                    int t_y = plansza.gracze[i].get_y();

                    // animacja ruchu pionka
                    aktywny_rysuj = false;
                    for(int j=1; j<4; j++){
                        plansza.rysuj_mape(i);
                        if(gracz1) al_draw_bitmap_region(ball_1_odbicie,j*32,0,32,32,t_x-16,t_y-16,0);
                        if(gracz2) al_draw_bitmap_region(ball_2_odbicie,j*32,0,32,32,t_x-16,t_y-16,0);
                        al_flip_display();
                        al_rest(0.1);

                    }
                    aktywny_rysuj = true;

                }

                else{
                    litera = events.keyboard.unichar;
                    napis.push_back(litera);
                    al_play_sample(klawiatura_klik,0.7,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                }
            }



            if(events.type == ALLEGRO_EVENT_TIMER){
                czas++;
                if (czas==60)
                    koniec_czasu=true;
                if (czas>=55 && czas < 60)
                    al_play_sample(tick, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
            }

        }
        al_stop_timer(timer);

        // oddanie strzalu
        if(koniec_wpisywania==true && koniec_gry==false){
            const char *cstr = napis.c_str();
            char proba[255];
            strcpy(proba, cstr);
            funkcja f(plansza.gracz_get_x(i)+plansza.gracz_get_r(i)+1, plansza.gracz_get_y(i), proba);
            al_play_sample(strzal, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            f.rysuj_funkcje(plansza, i);
        }

        if(!plansza.gracz_get_lewy(i))
            plansza.odwrocenie_danych();
        if(zapisywanie==false){
                if(runda%2==0){
                    if(kolejka1 == plansza.liczba_graczy_na_planszy()-2)
                        kolejka1 = 0;
                    else
                        kolejka1 = kolejka1 + 2;
                }
                else{
                    if(kolejka2 == plansza.liczba_graczy_na_planszy()-1)
                        kolejka2 = 1;
                    else
                        kolejka2 = kolejka2 + 2;
                }
                runda++;

            }
    //WARUNEK KONCZACY GRE
    if((plansza.zawodnik_zywy(true) + plansza.zawodnik_zywy(false))==1) koniec_gry = true;
    }

    if(((plansza.zawodnik_zywy(true) + plansza.zawodnik_zywy(false))== 1) && koniec_gry){


        al_draw_bitmap(Winner,0,0,0);
        al_draw_text(font_winner,white,400,200,ALLEGRO_ALIGN_CENTRE,"GRATULACJE!");

        al_play_sample(fanfary,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);

        if(gracz1) al_draw_text(font_winner_big,white,400,240,ALLEGRO_ALIGN_CENTRE,napis1_char);
        if(gracz2) al_draw_text(font_winner_big,white,400,240,ALLEGRO_ALIGN_CENTRE,napis2_char);
        al_flip_display();
        al_rest(8.2);
        plansza.kill();
        goto Poczatek;
    }

    // ZAPISANIE GRY
    if(zapisywanie==true){
    ofstream myfile;
    myfile.open("zapis.txt");
    myfile << plansza.liczba_graczy_na_planszy() << "\n";
    for (int i=0; i<plansza.liczba_graczy_na_planszy(); i++){
        myfile << plansza.gracz_get_x(i) << "\n";
        myfile << plansza.gracz_get_y(i) << "\n";
        myfile << plansza.gracz_get_r(i) << "\n";
        myfile << plansza.gracz_get_lewy(i) << "\n";
        myfile << plansza.gracz_get_zywy(i) << "\n";
    }
    myfile << plansza.liczba_przeszkod_na_planszy() << "\n";
    for (int i=0; i<plansza.liczba_przeszkod_na_planszy(); i++){
        myfile << plansza.przeszkoda_get_x(i) << "\n";
        myfile << plansza.przeszkoda_get_y(i) << "\n";
        myfile << plansza.przeszkoda_get_r(i) << "\n";
    }
    myfile << plansza.liczba_wyrw_na_panszy() << "\n";
    for (int i=0; i<plansza.liczba_wyrw_na_panszy(); i++){
        myfile << plansza.wyrwa_get_x(i) << "\n";
        myfile << plansza.wyrwa_get_y(i) << "\n";
        myfile << plansza.wyrwa_get_r(i) << "\n";
    }
    myfile << runda << "\n" << kolejka1 << "\n" << kolejka2 <<"\n";
    myfile << napis1 << "\n" << napis2 << "\n";
    myfile << czas << "\n";
    myfile.close();

    al_rest(0.3);

    al_draw_bitmap(Tablica_pusta,0,0,0);
    al_draw_bitmap(Zapis,277,117,0);

    al_stop_timer(timer);
    al_flip_display();
    al_rest(2);
    al_start_timer(timer);

    zapisywanie = false;
    czy_gra_z_zapisu = true;
    koniec_gry = false;
    czy_przed_chwila_zapis = true;
    goto Wczytaj;
    }

    if(plansza.zawodnik_zywy(true) && plansza.zawodnik_zywy(false) && koniec_gry){
        plansza.kill();
        goto Poczatek;
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    al_destroy_bitmap(Tlo);
    al_destroy_bitmap(Triangle);
    al_destroy_bitmap(Triangle_cover);
    al_destroy_bitmap(Wczytaj_0);
    al_destroy_bitmap(Wczytaj_1);
    al_destroy_bitmap(Start_0);
    al_destroy_bitmap(Start_1);
    al_destroy_bitmap(Zamknij_0);
    al_destroy_bitmap(Zamknij_1);
    al_destroy_bitmap(Dol_cover);
    al_destroy_bitmap(Plus_0);
    al_destroy_bitmap(Plus_1);
    al_destroy_bitmap(Minus_0);
    al_destroy_bitmap(Minus_1);
    al_destroy_bitmap(Znak_cover);
    al_destroy_bitmap(Liczba_1);
    al_destroy_bitmap(Liczba_2);
    al_destroy_bitmap(Liczba_3);
    al_destroy_bitmap(Liczba_4);
    al_destroy_bitmap(Winner);
    al_destroy_bitmap(Zapis);
    al_destroy_bitmap(Tablica_pusta);

    al_destroy_sample(strzal);
    al_destroy_sample(klik);
    al_destroy_sample(klik_select);
    al_destroy_sample(tick);
    al_destroy_sample(klawiatura_erase);
    al_destroy_sample(klawiatura_klik);
    al_destroy_sample(fanfary);
    al_destroy_bitmap(ball_1_active);
    al_destroy_bitmap(ball_2_active);

    al_destroy_bitmap(ball_1_odbicie);
    al_destroy_bitmap(ball_2_odbicie);

    al_destroy_sample(song_menu);
    al_destroy_sample_instance(song_menuInstance);

    return 0;
}
