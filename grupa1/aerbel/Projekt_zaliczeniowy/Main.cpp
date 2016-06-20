#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <cmath>
#include <time.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <stdio.h>
#include <vector>
using namespace std;

int skal = 10;
int szer = 800;
int wys  = 600;
double szyb = 0.5/10;
enum Direction { DOWN, LEFT, RIGHT, UP };

class przeszkoda;
class segment{
    public:
    int a,b;
        segment(int _a, int _b){
            a=_a, b=_b;
        }

        void setxy(int _a, int _b){
            a=_a, b=_b;
        }

        void losuj (){
            a=40*(rand()%(szer/40)), b= 40*(rand()%(wys/40));
         }

};

class waz {
    public:
    vector<segment> s;
    int z; // licznik punktow

    waz(segment _p);
    void przechodz(int & _dir);
    bool zjadlsie();
    bool uwkrawedz();
    bool uwprze(przeszkoda * _pp);
    bool zjadl(segment & _dol, przeszkoda * _pp);
    void ustaw(int & _dir,  segment & _dol, segment _p);
    void rysuj(segment _dol, ALLEGRO_COLOR _str);

};

class przeszkoda {
    public:
    vector<segment> p;
    przeszkoda();
   ~przeszkoda();

    void losuj(waz _s, waz _p, segment _dol);
    void rysuj();
};

przeszkoda::przeszkoda(){
    segment k(-10,-10);
    p.push_back(k);
}
przeszkoda::~przeszkoda(){
    while (p.size()>1) p.pop_back();
}


void przeszkoda::losuj(waz _r, waz _p, segment _dol){
    segment k(-10,-10);
    k.losuj();
    // przeszkoda nie moze byc tam gdzie dolar ale tam gdzie glowa weza
    while( (k.a==_p.s[0].a && k.b==_p.s[0].b ) || (k.a==_r.s[0].a && k.b==_r.s[0].b) || (k.a==_dol.a && k.b==_dol.b)) k.losuj();
    p.push_back(k);
}


void przeszkoda::rysuj(){
  for(int i=0;i<=p.size();i++){al_draw_rectangle(p[i].a, p[i].b, p[i].a +skal, p[i].b +skal, al_map_rgb(0,0,0), skal/2);
                               al_draw_filled_rectangle(p[i].a, p[i].b, p[i].a +skal, p[i].b +skal, al_map_rgb(0,0,0));}
}

waz::waz(segment _p) // inicjalizacaj weza z dowolnego sementu
     { s.push_back(_p);
       z=0;}

bool waz::zjadlsie(){
            for(int i=1;i<s.size();i++){ // czy glowa == reszta
                if(s[0].a==s[i].a && s[0].b==s[i].b) {return true;}
                }
return false;
}

bool waz::uwkrawedz(){ // czy waz uderzyl w sciane
            if(s[0].a<0 || s[0].a>=szer || s[0].b<0 || s[0].b>=wys ) {return true;}
return false;
}

bool waz::uwprze(przeszkoda * _pp){  //czy waz trafil na przeszkode
            for (int i=0; i<_pp ->p.size(); i++) {if(s[0].a==_pp ->p[i].a && s[0].b==_pp -> p[i].b) {return true;} }
return false;
}

bool waz::zjadl(segment & _dol, przeszkoda * _pp){
   if(s[0].a== _dol.a && s[0].b== _dol.b){  // jezeli glowa weza zrówna sie z moneta
                       z++;                 // zwiekszenie liczby punktow
                       segment p(-10,-10);  // dodanie nowego elementu do weza
                       s.push_back(p);
                       p.losuj();           // wylosowanie kandydata do bycia moneta
                                            // sprawdzenie czy nie koliduje z przeszkoda
                       for (int i=0; i<=_pp -> p.size(); i++) {if (_pp->p[i].a==p.a && _pp ->p[i].b==p.b) { p.losuj(); i=0;} }
                      _dol=p;               // przypisanie nowej wartosci do monety
                      return true;
                       }
return false;
}
// zeruje ustawienia
void waz::ustaw(int & _dir,  segment & _dol, segment _p){

        while(s.size()>0) s.pop_back(); // wyrzucenie wszystkich elementów z weza
        _dir=DOWN;                      // ustawienie kierunku weza
        _dol.losuj();                   // wylosowanie nowej monety na koljna gre
        s.push_back(_p);                // ustawienie glowy na poczatkowym miejscu
        z=0;                            // zerowanie punktow
}

void waz::rysuj(segment _dol, ALLEGRO_COLOR _str){
   // rysowanie monety
   al_draw_rectangle(_dol.a, _dol.b, _dol.a +skal, _dol.b+skal, al_map_rgb(0,0,0), skal/2);
   // rysowanie weza
   for(int i=0;i<=s.size();i++){al_draw_rectangle(s[i].a, s[i].b, s[i].a +skal, s[i].b +skal, _str, skal/2);}
}

void waz::przechodz(int & _dir) {
    // przechodzenie calego weza
    for(int i=s.size();i>0;i--) s[i]=s[i-1];
    // przechodznie glowy
    switch(_dir){
                case RIGHT: s[0].a = s[0].a+skal; break;
                case LEFT:  s[0].a = s[0].a-skal; break;
                case UP:    s[0].b = s[0].b-skal; break;
                case DOWN:  s[0].b = s[0].b+skal; break;
              }

}
/*--------------------------------------------------------*/

int main(){

    ALLEGRO_DISPLAY *display=NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_KEYBOARD_STATE keyState;

    if(!al_init()|| !al_install_mouse() || !al_install_keyboard()) return -1;

    al_init_primitives_addon(); // rysunki
    al_install_keyboard();      // klawiatura
    al_init_font_addon();       // inicjalizacja czcionki
    al_init_ttf_addon();        // inicjalizacja True Type Font

    display = al_create_display(szer,wys);
    timer = al_create_timer(szyb);
    event_queue = al_create_event_queue();

    if (!timer || !display || !event_queue) {return -1;}

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    srand (time(NULL));

    ALLEGRO_FONT *font_duzy = al_load_font("nokiafc22.ttf", 45, 0);
    ALLEGRO_FONT *font      = al_load_font("nokiafc22.ttf", 25, 0);
    ALLEGRO_FONT *font_maly = al_load_font("nokiafc22.ttf", 15, 0);

    bool enter;
    bool koniec = false;
    bool menu   = true;
    int dir  = DOWN;  // poczatkowy kierunek weza1
    int dir2 = DOWN;  // poczatkowy kierunek weza2

// inicjalizacja weza:
    segment z(0,-10);      // punkt poczatkowy weza1
    segment p(790,-10);    // punkt poczatkowy weza2
    waz snake(p);          // inicjalizacja weza1
    waz snake2(z);         // inicjalizacja weza2
    segment dol(-10,-10);  // inicjalizacja monety
    dol.losuj();
    przeszkoda *pre = new przeszkoda; // inicjalizacja przeszkody


     while(!koniec){

         ALLEGRO_EVENT events;
         al_wait_for_event(event_queue, &events);

        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) koniec = true;   // wylaczenie programu X w kazdym momencie
        switch(events.keyboard.keycode){
                  case ALLEGRO_KEY_ESCAPE: koniec = true; break;        // wylaczenie prograsmu ESC
                  case ALLEGRO_KEY_ENTER: if(menu) {menu=false,
                                                    enter=true;} break; // nowa gra po ENTER ale tylko gdy wyswietla sie MENU
                  }


           if(events.type == ALLEGRO_EVENT_TIMER){
                    if(events.timer.source == timer){

                          al_get_keyboard_state(&keyState);

                          // klawisze pierwszego gracza
                          if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && dir != LEFT)      dir = RIGHT;
                          else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT) && dir != RIGHT) dir = LEFT;
                          else if(al_key_down(&keyState, ALLEGRO_KEY_UP) && dir != DOWN)    dir = UP;
                          else if(al_key_down(&keyState, ALLEGRO_KEY_DOWN) && dir != UP)    dir = DOWN;

                          // klawisze drugiego gracza
                          if(al_key_down(&keyState, ALLEGRO_KEY_D) && dir2 != LEFT)        dir2 = RIGHT;
                          else if(al_key_down(&keyState, ALLEGRO_KEY_A) && dir2 != RIGHT)  dir2 = LEFT;
                          else if(al_key_down(&keyState, ALLEGRO_KEY_W) && dir2 != DOWN)   dir2 = UP;
                          else if(al_key_down(&keyState, ALLEGRO_KEY_S) && dir2 != UP)     dir2 = DOWN;

                         // przechodzenie wezy
                          snake.przechodz(dir);
                          snake2.przechodz(dir2);

                         // czy zjadl dolara
                         if (snake.zjadl(dol, pre) || snake2.zjadl(dol, pre)) {pre ->losuj(snake, snake2, dol);}

                         // sprawdzenie czy ktorys waz sie zjadl sam lub wjechal na krawedz
                         if ((snake.zjadlsie() || snake.uwkrawedz() || snake.uwprze(pre)) || ( snake2.zjadlsie() || snake2.uwkrawedz() || snake2.uwprze(pre) ) ){menu=true;}

                                  }}

            // gdy przegra lub na poczatku gry wyswietla...
            if(menu){
                    al_draw_textf(font_duzy, al_map_rgb(0,0,0),    330, 120, 0,"SNAKE");
                    al_draw_textf(font,      al_map_rgb(0,0,0),    270, 180, 0,"Wybierz: Enter/ESC");
                    al_draw_textf(font,      al_map_rgb(136,0,21), 350, 250, 0,"Punkty: %i", snake.z);
                    al_draw_textf(font,      al_map_rgb(0,0,0),    350, 280, 0,"Punkty: %i", snake2.z);
                    al_draw_textf(font_maly, al_map_rgb(0,0,0),    225, 350, 0,"Kolizje z drugim wezem sa dopuszczane!");
                    al_draw_textf(font_maly, al_map_rgb(136,0,21), 325, 375, 0,"Uwaga na kamienie!!!");

                    al_draw_rectangle(350, 400, 350 +skal, 400 +skal, al_map_rgb(0,0,0), skal/2);
                    al_draw_filled_rectangle(350, 400, 350+skal, 400 +skal, al_map_rgb(0,0,0));

                    al_draw_rectangle(350+50, 400, 350+50 +skal, 400 +skal, al_map_rgb(0,0,0), skal/2);
                    al_draw_filled_rectangle(350+50, 400, 350+50+skal, 400 +skal, al_map_rgb(0,0,0));

                    al_draw_rectangle(350+100, 400, 350+100 +skal, 400 +skal, al_map_rgb(0,0,0), skal/2);
                    al_draw_filled_rectangle(350+100, 400, 350+100+skal, 400 +skal, al_map_rgb(0,0,0));


                    al_draw_textf(font_maly, al_map_rgb(0,0,0),    250, 425, 0,"Prawy waz: sterowanie strzalkami.");
                    al_draw_textf(font_maly, al_map_rgb(136,0,21), 220, 450, 0,"Lewy waz: A(Lewo) D(Prawo) W(gora) S (dol)");

                                                           }
            // jezeli gracz wybral enter - zeruje parametry gry
            else if (enter) {
                 delete pre;             // usuwanie starych przeszkód, destruktor sam sie wlacza
                 pre = new przeszkoda;   // inicjalizacja przeszkody
                 snake.ustaw(dir,dol,p); //zeruje liczniki i pozycje weza
                 snake2.ustaw(dir2,dol,z);
                 enter=false;


                            }
            // w przeciwnym razie gra dalej
                 else {snake.rysuj(dol, al_map_rgb(136,0,21)); //rysuje weza i monete
                       snake2.rysuj(dol, al_map_rgb(0,0,0));
                       pre -> rysuj();
                        }
            // wyswietlenie
            al_flip_display();
            al_clear_to_color(al_map_rgb(102,155, 2));

        }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
