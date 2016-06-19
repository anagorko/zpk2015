#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "mrowka.h"

using namespace Mrowka;
using namespace std;

int ileKolorow;
vector <pole> NieBiale;
vector <mrowa> Mrowy;

ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h)
{
  ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;


  resized_bmp = al_create_bitmap(w, h);
  if (!resized_bmp) return NULL;


  loaded_bmp = al_load_bitmap(filename);
  if (!loaded_bmp)
  {
     al_destroy_bitmap(resized_bmp);
     return NULL;
  }

  prev_target = al_get_target_bitmap();
  al_set_target_bitmap(resized_bmp);

  al_draw_scaled_bitmap(loaded_bmp,
     0, 0,
     al_get_bitmap_width(loaded_bmp),
     al_get_bitmap_height(loaded_bmp),
     0, 0,
     w, h,
     0
  );


  al_set_target_bitmap(prev_target);
  al_destroy_bitmap(loaded_bmp);

  return resized_bmp;
}


pole::pole(int x, int y, int z)
{
            pozX=x;
            pozY=y;
            rozmiar=z;
            kolor = 1;
}

void pole::setX(unsigned int x)
{
            pozX = x;
}

void pole::setY(unsigned int y)
{
            pozY = y;
}

void pole::setRozmiar(unsigned int z)
{
            rozmiar = z;
}

unsigned int pole::getX()
{
            return pozX;
}

unsigned int pole::getY()
{
            return pozY;
}

unsigned int pole::getRozmiar()
{
            return rozmiar;
}

int pole::getKolor()
{
            return kolor;
}

void pole::setKolor(int k)
{
        kolor = k;
}

 mrowa::mrowa(int x, int y, int z)
{
            pozX=x;
            pozY=y;
            rozmiar=z;
            zwrot = N;
            obrot = zwrot * 3.1415 / 90;
            obrazek = load_bitmap_at_size("/Users/lukasz/Desktop/test_allegro/test2/mrowka.jpg",80,80);
}

void mrowa::setX(unsigned int x)
{
            this -> pozX = x;
}

void mrowa::setY(unsigned int y)
{
            this -> pozY = y;
}

unsigned int mrowa::getX()
{
            return pozX;
}

unsigned int mrowa::getY()
{
            return pozY;
}

void mrowa::setZwrot(kierunek x)
{
            zwrot = x;
}

kierunek mrowa::getZwrot()
{
            return zwrot;
}

float mrowa::getObrot()
{
            return obrot;
}

ALLEGRO_BITMAP* mrowa:: getBMP()
{
    return obrazek;
}

unsigned int mrowa::getRozmiar()
{
            return rozmiar;
}
void mrowa::lewo()
{
    switch(this -> zwrot)
    {
    case N:
        this ->  zwrot = W;
        this ->  obrot = zwrot * 3.1415 / 90;
        break;
    case W:
        this ->  zwrot = S;
        this ->  obrot = zwrot * 3.1415 / 90;
        break;
    case S:
        this ->  zwrot = E;
        this ->  obrot = zwrot * 3.1415 / 90;
        break;
    case E:
        this ->  zwrot = N;
        this ->  obrot = zwrot * 3.1415 / 90;
        break;

    }
}

void mrowa::prawo()
{
    switch(this -> zwrot)
    {
    case N:
        this ->  zwrot = E;
        this ->  obrot = zwrot * 3.1415 / 90;
        break;
    case E:
        this ->  zwrot = S;
        this ->  obrot = zwrot * 3.1415 / 90;
        break;
    case S:
        this ->  zwrot = W;
        this ->  obrot = zwrot * 3.1415 / 90;
        break;
    case W:
        this ->  zwrot = N;
        this ->  obrot = zwrot * 3.1415 / 90;
        break;

    }
}

int mrowa:: kolor(vector <pole> &nieBiale) //funkcja zwraca jeden, jezeli wspolrzedne mrowki pokrywajà si´ ze wspó∏rz´dnymi któregos z pokolorowanych kwadracikow
{

  int kolor = 0;
  for(int i = 0 ; i<nieBiale.size(); ++i)
  {
        if(nieBiale[i].getX() == pozX && nieBiale[i].getY() == pozY)
        {
            kolor=1;
            break;
        }
  }

return kolor;

}

void mrowa::ruch() //ruch mrowki do przodu. zmiana wspolrzednych o rozmiar zalezy od jej wczesniejszego zwrotu
{
        switch(this -> zwrot)
    {
    case N:
        pozY -= rozmiar;
        break;
    case E:
        pozX += rozmiar;
        break;
    case S:
        pozY += rozmiar;
        break;
    case W:
        pozX -= rozmiar;
        break;

    }

}


void mrowa::usunKolor(vector <pole> &NieBiale)
{
    for(int i = 0 ; i<NieBiale.size(); ++i)
        if(NieBiale[i].getX() == pozX && NieBiale[i].getY() == pozY)
    {
        switch (ileKolorow)
        {
            case 4:
                if(NieBiale[i].getKolor() == 1)
                    {
                        NieBiale[i].setKolor(2);
                        break;
                    }

               if(NieBiale[i].getKolor() == 2)
                    {
                        NieBiale[i].setKolor(3);
                        break;
                    }
                if(NieBiale[i].getKolor() == 3)
                    {
                        NieBiale.erase(NieBiale.begin()+i);
                        break;
                    }
            break;

            case 3:
                if(NieBiale[i].getKolor() == 1)
                    {
                        NieBiale[i].setKolor(2);
                        break;
                    }

               if(NieBiale[i].getKolor() == 2)
                    {
                        NieBiale.erase(NieBiale.begin()+i);
                        break;
                    }
            break;

               case 2:
                if(NieBiale[i].getKolor() == 1)
                    {
                        NieBiale.erase(NieBiale.begin()+i);
                        break;
                    }
            break;
        }
    }
}


void mrowa::pomaluj(vector <pole> &V)
{
    pole v(pozX, pozY, rozmiar);
    V.push_back(v);

}

void mrowa::skret(vector <pole> &NieBiale) //w zale˝nosci od pozycji mrowki (czy jest na ktoryms z kolorowych pol) obraca jà "w gotowosci" do nastepnego ruchu
{

            this -> prawo(); //domyslnie mrowka jest na bia∏ym polu, wiec skreca w prawo
            for(int i = 0 ; i < NieBiale.size(); ++i) //dla kazdej mrowki porownywane sa pozycje z polami w wektorze NieBiale i w zaleznosci na jakim kolorze znajduje sie mrowka tak jest ustawiony jej obrot
            {

                if(pozX == NieBiale[i].getX() && pozY== NieBiale[i].getY())
                    {
                        if(NieBiale[i].getKolor() == 1)
                            this -> lewo();
                        if(NieBiale[i].getKolor() == 2)
                            this -> prawo();
                        if(NieBiale[i].getKolor() == 3)
                            this -> lewo();
                    }

            }
}


int mrowa::czySieZmiesci(vector <pole> &NieBiale)
{
 int szer = 800;
 int wys = 600;

 this -> skret(NieBiale); //skreca mrówk´ "w gotowosci" do nastepnego ruchu

 switch(zwrot)
    {
    case N:
        if(pozY - rozmiar < 0) return 1; //sprawdza czy nie wyjdzie gorà ekranu
        break;
    case E:
        if(pozX + rozmiar > szer) return 2;  //sprawdza czy nie wyjdzie prawà stronà ekranu
        break;
    case S:
        if(pozY + rozmiar > wys) return 3; //sprawdza czy nie wyjdzie do∏em ekranu
        break;
    case W:
        if(pozX - rozmiar < 0) return 4; //sprawdza czy nie wyjdzie lewà stronà ekranu
        break;

    }
return 5;
}

bool czySieZmiesci(vector <mrowa> &Mrowy, vector <pole> &NieBiale) //sprawdza to co funkcja powyzej ale dla kazdej mrowki z wektora mrowek
{

   for(int i = 1; i < Mrowy.size(); ++i)
   {
       if(Mrowy[i].czySieZmiesci(NieBiale) != 5) return false; //wystarczy ze jedna z mrowek wyswietlanych na ekranie sie nie zmiesci, wtedy funkcja ma zwrocic false

   }
    return true;

}



vector <int> skrajne(vector <pole> &NieBiale) // argumentem funkcji jest wektor zawierajàcy niebia∏e pola. funkcja zwraca wektor z 4roma wartosciami- skrajnymi wspolrzednymi pol nalezacych do argumentu
{
    vector <int> skrajne;
    skrajne[0] = 800; //Najmniejszy x
    skrajne[1] = 600; //Najmniejszy y
    skrajne[2] = 0; //Najwiekszy x
    skrajne[3] = 0; //Najwiekszy y
    for(int i = 0; i < NieBiale.size(); ++i)
    {
        if(NieBiale[i].getX() < skrajne[0] )
            skrajne[0] = NieBiale[i].getX(); //ustalenie najmniejszej wspolrzednej x wsrod wszystkich niebialych pol
        if(NieBiale[i].getY() < skrajne[1] )
            skrajne[1] = NieBiale[i].getY(); //ustalenie najmniejszej wspolrzednej y wsrod wszystkich niebialych pol
        if(NieBiale[i].getX() > skrajne[2] )
            skrajne[2] = NieBiale[i].getX();
        if(NieBiale[i].getY() > skrajne[3] )
            skrajne[3] = NieBiale[i].getY();
    }
return skrajne;
}


int mysz(int x, int rozmiar)//okreÊla gdzie namalowaç mrówk´ na podstawie klikni´cia myszkà
{
    int mysz = 0;
    mysz = (x / rozmiar )* rozmiar;
    return mysz;
}



void dodajPole(vector <pole> &NieBiale, vector <mrowa> &Mrowy, int x, int y, int rozmiar, int kolory)
{
    x = mysz(x, 80); // ustalenie wspolrzednej x-owej dla pola
    y = mysz(y , 80); // ustalenie wspolrzednej y-owej dla pola

    for(int i = 0; i < NieBiale.size(); i++)
    {
        if(NieBiale[i].getX() == x && NieBiale[i].getY() == y )
            {
                if(NieBiale[i].getKolor() +1 <= kolory - 1) NieBiale[i].setKolor(NieBiale[i].getKolor()+1);
                else NieBiale.erase(NieBiale.begin() + i);
                return;
            }
        if(Mrowy[i].getX() == x && Mrowy[i].getY() == y ) Mrowy.erase(Mrowy.begin() + i);
    }

    for(int i = 0; i < Mrowy.size(); ++i)
    {
        if(Mrowy[i].getX() == x && Mrowy[i].getY() == y ) Mrowy.erase(Mrowy.begin() + i);
    }



    NieBiale.push_back(pole(x, y, rozmiar));
}


void dodajMrowke(vector <mrowa> &Mrowy, vector <pole> NieBiale, int x, int y)
{
    x = mysz(x, 80); // ustalenie wspolrzednej x-owej dla mrowki
    y = mysz(y , 80); // ustalenie wspolrzednej y-owej dla mrowki

     for(int i = 0; i < Mrowy.size(); ++i)
    {
        if(Mrowy[i].getX() == x && Mrowy[i].getY() == y ) Mrowy.erase(Mrowy.begin() + i);
    }

     for(int i = 0; i < NieBiale.size(); ++i)
    {
        if(NieBiale[i].getX() == x && NieBiale[i].getY() == y )
            return;
    }
    mrowa Ant(x, y, 80); //utworzenie instancji Ant klasy mrowka o wspolrzednych popranych z myszki i rozmiarze 80
    Mrowy.push_back(Ant);

}
void rysuj(int x, int y, int rozmiar, int kolor)
{
    if(kolor ==1 ) al_draw_filled_rectangle(x, y, x + rozmiar, y + rozmiar, al_map_rgb(0,0,0)); //czarny
    else if(kolor == 2) al_draw_filled_rectangle(x, y, x + rozmiar, y + rozmiar, al_map_rgb(0,0,255) );//niebieski
    else if(kolor == 3) al_draw_filled_rectangle(x, y, x + rozmiar, y + rozmiar, al_map_rgb(255,0,0) ); //czerwony

}
void rysujPola(vector <pole> &NieBiale) // w zale˝noÊci od argumentu kolor funkcja rysuje wszystkie pola nale˝àce do danego wektora w kolorze czarnym, niebieskim lub czerwonym
{
    int rozmiar;
    for(int i = 0; i < NieBiale.size(); ++i )
    {
        rozmiar = NieBiale[i].getRozmiar();
        break;
    }

    int k;
    for(int i = 0; i < NieBiale.size(); ++i)
        {
            k = NieBiale[i].getKolor();
            rysuj(NieBiale[i].getX(),NieBiale[i].getY(),rozmiar, k);
        }
}


void rysujMrowy(vector <mrowa> &Mrowy)
{
    float k;
    for(int i = 0; i < Mrowy.size() ; ++i) //rysuje wszystkie mrowki z wektora mrowek
    {
        k=float(Mrowy[0].getRozmiar())/80;
        al_draw_scaled_rotated_bitmap(Mrowy[i].getBMP(), 40, 40, float(Mrowy[i].getX()+Mrowy[i].getRozmiar()/2),float(Mrowy[i].getY()+Mrowy[i].getRozmiar()/2), k, k, Mrowy[i].getObrot(),0);

    }
}

void doSrodka(int kierunek, vector<mrowa> &Mrowy, vector<pole> &NieBiale) /*W zale˝nosci od tego, ktorà stronà ekroanu,
 mrowka mog∏aby wyjsc za jego obrys, ustalane sa nowe wspolrzedne wszystkich obiektow na mapie- mrowek i nieBiaych pol, tak aby "sciagnac" je bardziej do Êrodka*/
{






}

void menu(ALLEGRO_FONT *F1,int iter,int predkosc, int kol)
{
	string p,i,m,pred, colors;
	int LiczbaPol = NieBiale.size();
	int LiczbaMrowek = Mrowy.size();
	sprintf((char*)p.c_str(), "%d", LiczbaPol);
	sprintf((char*)i.c_str(), "%d", iter);
	sprintf((char*)m.c_str(), "%d", LiczbaMrowek);
	sprintf((char*)pred.c_str(), "%d", predkosc);
	sprintf((char*)colors.c_str(), "%d", kol);


	al_draw_filled_rectangle(880, 0, 1080, 800, al_map_rgb(55, 100, 0));
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 50, ALLEGRO_ALIGN_LEFT, "Iteracje:");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 70, ALLEGRO_ALIGN_LEFT, (char*)i.c_str());
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 130, ALLEGRO_ALIGN_LEFT, "Ilosc niebialych pol:");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 150, ALLEGRO_ALIGN_LEFT, (char*)p.c_str());
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 190, ALLEGRO_ALIGN_LEFT, "Ilosc mrowek:");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 210, ALLEGRO_ALIGN_LEFT, (char*)m.c_str());
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 240, ALLEGRO_ALIGN_LEFT, "Predkosc :");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 260, ALLEGRO_ALIGN_LEFT, (char*)pred.c_str());
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 290, ALLEGRO_ALIGN_LEFT, "Kolory:");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 310, ALLEGRO_ALIGN_LEFT, (char*)colors.c_str());
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 450, ALLEGRO_ALIGN_LEFT, "Info :");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 470, ALLEGRO_ALIGN_LEFT, "Predkosc w gore :");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 490, ALLEGRO_ALIGN_LEFT, "Prawa strzalka =>");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 510, ALLEGRO_ALIGN_LEFT, "Predkosc w dol :");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 530, ALLEGRO_ALIGN_LEFT, "Lewa strzalka <=");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 570, ALLEGRO_ALIGN_LEFT, "Wiecej kolorow :");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 590, ALLEGRO_ALIGN_LEFT, "Strzalka w gore ^");
    al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 610, ALLEGRO_ALIGN_LEFT, "Mniej kolorow :");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 630, ALLEGRO_ALIGN_LEFT, "Strzalka w dol v");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 660, ALLEGRO_ALIGN_LEFT, "Exit :");
	al_draw_text(F1, al_map_rgb(255, 255, 255), 885, 680, ALLEGRO_ALIGN_LEFT, "Esc");
}




int main(int argc, char **argv){

    int rozmiar = 80;
    int kolory = 4;
    int szer = 1080;
    int wys = 800;
    int FPS = 60;


    //zmienne do petli
    bool done = false;
    bool redraw = true;



    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;


    al_init();
    if(!al_init())
        return -1;

    display = al_create_display(szer, wys); //utworzenie wyswietlacza

    if(!display)
        return -1;

           //instalacja addonów
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_mouse();

    ALLEGRO_FONT *czcionka = al_load_ttf_font("/Users/lukasz/Desktop/mrowka_langtona/mrowka/Arial.ttf", 15, 0);


    event_queue = al_create_event_queue();


    al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());


    ALLEGRO_EVENT ev;

    al_set_window_title(display , "MROWKA");

    Mrowy.clear();
    NieBiale.clear();
    al_clear_to_color(al_map_rgb(255,255,255));
    al_flip_display();
    timer = al_create_timer(1.0 / FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    while(!done)
    {
        al_clear_to_color(al_map_rgb(255,255,255));
        menu(czcionka, FPS, FPS, kolory);

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) done = true;
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {

            ALLEGRO_MOUSE_STATE klawisz;
            al_get_mouse_state(&klawisz);

            if(klawisz.buttons & 1) dodajMrowke(Mrowy, NieBiale, ev.mouse.x, ev.mouse.y);
            else if(klawisz.buttons & 2) dodajPole(NieBiale, Mrowy, ev.mouse.x, ev.mouse.y,rozmiar,kolory);


               // rysujMrowy(Mrowy);
                //rysujPola(NieBiale);
                //al_flip_display();

        }
        else if(ev.type == ALLEGRO_EVENT_TIMER)
                {
                    redraw = true;
                }

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) done = true;
            if(ev.keyboard.keycode ==ALLEGRO_KEY_UP)
                {
                    if(kolory < 4)kolory++;
                    else kolory = 4;
                }
             if(ev.keyboard.keycode ==ALLEGRO_KEY_DOWN)
                {
                    if(kolory > 2)kolory--;
                    else kolory = 2;
                }
            if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE) break; // po wciÊnieciu spacji opuszczamy p´tl´, w której mo˝na dodawaç mrówki

        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            rysujMrowy(Mrowy);
            rysujPola(NieBiale);
            al_flip_display();
        }

    }





return 0;

}




