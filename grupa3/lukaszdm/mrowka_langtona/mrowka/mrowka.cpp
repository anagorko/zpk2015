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
            obrazek = load_bitmap_at_size("/Users/lukasz/Desktop/test_allegro/test2/mrowka.jpg",80,80);
}

void mrowa::setX(unsigned int x)
{
            pozX = x;
}

void mrowa::setY(unsigned int y)
{
            pozY = y;
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


ALLEGRO_BITMAP* mrowa:: getBMP()
{
    return obrazek;
}

unsigned int mrowa::getRozmiar()
{
            return rozmiar;
}

void mrowa::setRozmiar(unsigned int x)
{
            rozmiar = x;
}
void mrowa::lewo() //obrot w lewo
{
    switch(zwrot)
    {
    case N:
        zwrot = W;

        break;
    case W:
        zwrot = S;

        break;
    case S:
        zwrot = E;

        break;
    case E:
        zwrot = N;

        break;

    }
}

void mrowa::prawo() //obrot w prawo
{
    switch(zwrot)
    {
    case N:
            zwrot = E;

        break;
    case E:
            zwrot = S;

        break;
    case S:
            zwrot = W;

        break;
    case W:
            zwrot = N;

        break;

    }
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


void mrowa::pomaluj(vector <pole> &NieBiale, int kolory)
{

     for(int i = 0; i < NieBiale.size(); i++)
    {
        if(pozX == NieBiale[i].getX() && pozY == NieBiale[i].getY())
            {
                if(NieBiale[i].getKolor() +1 <= kolory - 1) NieBiale[i].setKolor(NieBiale[i].getKolor()+1);
                else NieBiale.erase(NieBiale.begin() + i);
                return; //jezeli zmieni kolor ktoregos z pomalowanych pol wychodzimy z funkcji
            }
    }


         pole v(pozX, pozY, rozmiar); //jeýeli przelecia¸a ca¸a p«tla, a funkcja nie zosta¸a zakonczona, znaczy ze mrowka stala na bialym polu, trzeba je dodac jako czarne (domyslny kolor)do wektora NieBiale
         NieBiale.push_back(v);
         return;

}

void mrowa::skret(vector <pole> &NieBiale) //w zaleýnosci od pozycji mrowki (czy jest na ktoryms z kolorowych pol) obraca jˆ "w gotowosci" do nastepnego ruchu
{


            for(int i = 0 ; i < NieBiale.size(); ++i) //dla kazdej mrowki porownywane sa pozycje z polami w wektorze NieBiale i w zaleznosci na jakim kolorze znajduje sie mrowka tak jest ustawiony jej obrot
            {

                if(pozX == NieBiale[i].getX() && pozY== NieBiale[i].getY())
                    {
                        if(NieBiale[i].getKolor() == 1)
                        {
                          lewo();
                          return;
                        }

                        if(NieBiale[i].getKolor() == 2)
                        {
                           prawo();
                           return;
                        }

                        if(NieBiale[i].getKolor() == 3)
                          lewo();
                          return;
                    }

            }

          prawo();
}


int mrowa::czySieZmiesci(vector <pole> &NieBiale)
{
 int szer = 800;
 int wys = 600;


 //skret(NieBiale); //skreca mr—wk« "w gotowosci" do nastepnego ruchu


 switch(zwrot)
    {
    case N:
        if(pozY - rozmiar < 0) return 1; //sprawdza czy nie wyjdzie gorˆ ekranu
        break;
    case E:
        if(pozX + rozmiar > szer ) return 2;  //sprawdza czy nie wyjdzie prawˆ stronˆ ekranu
        break;
    case S:
        if(pozY + rozmiar > wys) return 3; //sprawdza czy nie wyjdzie do¸em ekranu
        break;
    case W:
        if(pozX - rozmiar < 0) return 4; //sprawdza czy nie wyjdzie lewˆ stronˆ ekranu
        break;

    }
return 5;

}
vector <int> skrajne(vector <pole> &NieBiale) // argumentem funkcji jest wektor zawierajˆcy niebia¸e pola. funkcja zwraca wektor z 4roma wartosciami- skrajnymi wspolrzednymi pol nalezacych do argumentu
{
    vector <int> skrajne;
    skrajne[0] = 1000; //Najmniejszy x
    skrajne[1] = 1000; //Najmniejszy y
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


bool czySieZmieszcza(vector <mrowa> Mrowy, vector <pole> NieBiale) //sprawdza to co funkcja powyzej ale dla kazdej mrowki z wektora mrowek
{

   for(int i = 0; i < Mrowy.size(); ++i)
   {
       if(Mrowy[i].czySieZmiesci(NieBiale) != 5) return false; //wystarczy ze jedna z mrowek wyswietlanych na ekranie sie nie zmiesci, wtedy funkcja ma zwrocic false

   }
    return true;

}
void skrecWszystkie(vector <mrowa> &Mrowy ,vector<pole> &NieBiale) //to samo co skret tylko dla wszystkich mrowek w wektorze
{

    for(int i = 0; i < Mrowy.size(); ++i)
        Mrowy[i].skret(NieBiale);

}

void pomalujWszystkie(vector <mrowa> &Mrowy, vector <pole> &NieBiale, int kolory ) // to samo co pomaluj tylko dla wszytskich mrowek
{

        for(int i = 0; i < Mrowy.size(); ++i)
            Mrowy[i].pomaluj(NieBiale , kolory);


}


int mysz(int x, int rozmiar)//okreæla gdzie namalowa mr—wk« na podstawie klikni«cia myszkˆ
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

    if(x < 880 )
    {
        mrowa Ant(x, y, 80); //utworzenie instancji Ant klasy mrowka o wspolrzednych popranych z myszki i rozmiarze 80
        Mrowy.push_back(Ant);
    }
}
void rysuj(int x, int y, int rozmiar, int kolor)
{
    if(kolor ==1 ) al_draw_filled_rectangle(x, y, x + rozmiar, y + rozmiar, al_map_rgb(0,0,0)); //czarny
    else if(kolor == 2) al_draw_filled_rectangle(x, y, x + rozmiar, y + rozmiar, al_map_rgb(0,0,255) );//niebieski
    else if(kolor == 3) al_draw_filled_rectangle(x, y, x + rozmiar, y + rozmiar, al_map_rgb(255,0,0) ); //czerwony

}
void rysujPola(vector <pole> NieBiale) // w zaleýnoæci od argumentu kolor funkcja rysuje wszystkie pola naleýˆce do danego wektora w kolorze czarnym, niebieskim lub czerwonym
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


void rysujMrowy(vector <mrowa> Mrowy)
{
    float k;
    for(int i = 0; i < Mrowy.size() ; ++i) //rysuje wszystkie mrowki z wektora mrowek
    {
        float obrot=Mrowy[i].getZwrot() * 3.1415 / 2;
        k=float(Mrowy[0].getRozmiar())/80;
        al_draw_scaled_rotated_bitmap(Mrowy[i].getBMP(), 40, 40, float(Mrowy[i].getX()+Mrowy[i].getRozmiar()/2),float(Mrowy[i].getY()+Mrowy[i].getRozmiar()/2), k, k, obrot,0);

    }
}



void zmniejszMrowki(vector<mrowa> &Mrowy, vector <pole> &NieBiale, int rozmiar)
{
	int szer = 800;
	int wys = 600;
	//vector <int> Pozycje;
	//Pozycje = skrajne(NieBiale);
	int maxY = 800;//Pozycje[3];
	int maxX = 600;//Pozycje[2];
	int roznicaX = 0;
	int roznicaY = 0;
	int roznica = 10;
	if (rozmiar <= 10)
	{
		roznica = 1;
	}
	rozmiar -= roznica;

	for(int i = 0; i < Mrowy.size(); ++i)
    {
        Mrowy[i].setRozmiar(rozmiar);
		roznicaY = (maxY - Mrowy[i].getY());
		roznicaX = (maxX - Mrowy[i].getX());
		if (roznicaY != 0) roznicaY = (roznicaY / (rozmiar + roznica)) + 1;
		else roznicaY = 1;
		if (roznicaX != 0) roznicaX = (roznicaX/(rozmiar + roznica)) + 1;
		else roznicaX = 1;
		Mrowy[i].setX(Mrowy[i].getX() + roznicaX * roznica);
		Mrowy[i].setY(Mrowy[i].getY() + roznicaY * roznica);



    }

}

void zmniejszPola(vector<mrowa> &Mrowy, vector <pole> &NieBiale, int rozmiar)
{
	int szer = 800;
	int wys = 600;
	//vector <int> Pozycje;
	//Pozycje = skrajne(NieBiale);
	int maxY = 800; //Pozycje[3];
	int maxX = 600;//Pozycje[2];
	int roznicaX = 0;
	int roznicaY = 0;
	int roznica = 10;
	if (rozmiar <= 10)
	{
		roznica = 1;
	}
	rozmiar -= roznica;



	for(int i = 0; i < NieBiale.size(); ++i)
    {
        NieBiale[i].setRozmiar(rozmiar);
		roznicaY = (maxY - NieBiale[i].getY());
		roznicaX = (maxX - NieBiale[i].getX());
		if (roznicaY != 0) roznicaY = (roznicaY / (rozmiar + roznica)) + 1;
		else roznicaY = 1;
		if (roznicaX != 0) roznicaX = (roznicaX/(rozmiar + roznica)) + 1;
		else roznicaX = 1;
		NieBiale[i].setX(NieBiale[i].getX() + roznicaX * roznica);
		NieBiale[i].setY(NieBiale[i].getY() + roznicaY * roznica);



    }

}


/*void zmniejszPola(vector<pole> &NieBiale)
{
	int szer = 800;
	int wys = 600;
	if(NieBiale.size() == 0) return;
	int rozmiar = NieBiale[0].getRozmiar();
	int newRozmiar = 0.9 * rozmiar;

	for(int i = 0; i < Mrowy.size(); ++i)
    {

        if(NieBiale[i].getX()>= (0.5 * szer) && NieBiale[i].getY() >= (0.5 * wys)) //prawa dolna wiartka ekranu
            {
                NieBiale[i].setRozmiar(newRozmiar);
                NieBiale[i].setX(NieBiale[i].getX() * 0.5);
                NieBiale[i].setY(NieBiale[i].getY() * 0.5);
            }
        else if(NieBiale[i].getX() >= 0.5 * szer && NieBiale[i].getY() < 0.5 * wys) //prawa gorna cwiartka ekranu
            {
                NieBiale[i].setRozmiar(newRozmiar);
                NieBiale[i].setX(NieBiale[i].getX() * 0.5);
                NieBiale[i].setY(NieBiale[i].getY() *1.5);
            }
        else if(NieBiale[i].getX() < 0.5 * szer && NieBiale[i].getY() < 0.5 * wys) //lewa gorna cwiartka ekranu
            {
                NieBiale[i].setRozmiar(newRozmiar);
                NieBiale[i].setX(NieBiale[i].getX() * 1.5);
                NieBiale[i].setY(NieBiale[i].getY() * 1.5);
            }
        else if(NieBiale[i].getX() < 0.5 * szer && NieBiale[i].getY() >= 0.5 * wys) //lewa dolna cwiartka ekranu
            {
                NieBiale[i].setRozmiar(newRozmiar);
                NieBiale[i].setX(NieBiale[i].getX() * 1.5 );
                NieBiale[i].setY(NieBiale[i].getY() * 0.5 );
            }
         else
                NieBiale[i].setRozmiar(newRozmiar);


    }

}

*/


void menu(ALLEGRO_FONT *czcionka,int iter,int predkosc, int kol)
{

	int pola = NieBiale.size();
	int mrowki = Mrowy.size();



	al_draw_filled_rectangle(880, 0, 1080, 800, al_map_rgb(55, 100, 0));
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 50, ALLEGRO_ALIGN_LEFT, "Iteracje:");
	al_draw_textf(czcionka, al_map_rgb(255, 255, 255), 885, 70, ALLEGRO_ALIGN_LEFT, "%i", iter);
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 130, ALLEGRO_ALIGN_LEFT, "Ilosc niebialych pol:");
	al_draw_textf(czcionka, al_map_rgb(255, 255, 255), 885, 150, ALLEGRO_ALIGN_LEFT, "%i", pola);
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 190, ALLEGRO_ALIGN_LEFT, "Ilosc mrowek:");
	al_draw_textf(czcionka, al_map_rgb(255, 255, 255), 885, 210, ALLEGRO_ALIGN_LEFT, "%i", mrowki);
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 240, ALLEGRO_ALIGN_LEFT, "Predkosc :");
	al_draw_textf(czcionka, al_map_rgb(255, 255, 255), 885, 260, ALLEGRO_ALIGN_LEFT, "%i", predkosc);
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 290, ALLEGRO_ALIGN_LEFT, "Kolory:");
	al_draw_textf(czcionka, al_map_rgb(255, 255, 255), 885, 310, ALLEGRO_ALIGN_LEFT, "%i", kol);
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 450, ALLEGRO_ALIGN_LEFT, "Info :");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 470, ALLEGRO_ALIGN_LEFT, "Predkosc w gore :");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 490, ALLEGRO_ALIGN_LEFT, "Prawa strzalka =>");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 510, ALLEGRO_ALIGN_LEFT, "Predkosc w dol :");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 530, ALLEGRO_ALIGN_LEFT, "Lewa strzalka <=");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 570, ALLEGRO_ALIGN_LEFT, "Wiecej kolorow :");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 590, ALLEGRO_ALIGN_LEFT, "Strzalka w gore ^");
    al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 610, ALLEGRO_ALIGN_LEFT, "Mniej kolorow :");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 630, ALLEGRO_ALIGN_LEFT, "Strzalka w dol v");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 650, ALLEGRO_ALIGN_LEFT, "Start/Pauza :");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 670, ALLEGRO_ALIGN_LEFT, "Spacja");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 690, ALLEGRO_ALIGN_LEFT, "Reset :");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 710, ALLEGRO_ALIGN_LEFT, "Enter");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 730, ALLEGRO_ALIGN_LEFT, "Exit :");
	al_draw_text(czcionka, al_map_rgb(255, 255, 255), 885, 750, ALLEGRO_ALIGN_LEFT, "Esc");
}




int main(int argc, char **argv){

    int rozmiar = 80;
    int kolory = 4;
    int szer = 1080;
    int wys = 800;
    int FPS = 1;
    int iter = 0;
    int tmpRoz = 80;


    //zmienne do petli
    bool done = false;
    bool redraw = true;
    bool done1 = false;



    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;


    al_init();
    if(!al_init())
        return -1;

    display = al_create_display(szer, wys); //utworzenie wyswietlacza

    if(!display)
        return -1;

           //instalacja addon—w
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
    START:
    al_start_timer(timer);

    /*mrowa ANT(800, 100, 80);
    Mrowy.push_back(ANT);
    rysujMrowy(Mrowy);
    al_flip_display();
    al_rest(10);*/



    while(!done)
    {
        al_clear_to_color(al_map_rgb(255,255,255));
        menu(czcionka, FPS, iter, kolory);

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
            done1 = true;

        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {

            ALLEGRO_MOUSE_STATE klawisz;
            al_get_mouse_state(&klawisz);

            if(klawisz.buttons & 1) dodajMrowke(Mrowy, NieBiale, ev.mouse.x, ev.mouse.y);
            else if(klawisz.buttons & 2) dodajPole(NieBiale, Mrowy, ev.mouse.x, ev.mouse.y,rozmiar,kolory);


        }
        else if(ev.type == ALLEGRO_EVENT_TIMER)
                {
                    redraw = true;
                }

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                done = true;
                done1 =true;
            }
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
            if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE) break; // po wciænieciu spacji opuszczamy p«tl«, w kt—rej moýna dodawa mr—wki

        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            rysujMrowy(Mrowy);
            rysujPola(NieBiale);
            al_flip_display();
        }

    }

    while(!done1)
    {
        al_clear_to_color(al_map_rgb(255,255,255));
        menu(czcionka, iter, FPS, kolory);

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) done1 = true;
        else if(ev.type == ALLEGRO_EVENT_TIMER)
                {
                    redraw = true;
                }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) done1 = true;

                if(ev.keyboard.keycode ==ALLEGRO_KEY_LEFT)
                    {
                        if(FPS > 1)FPS--;
                        else FPS = 1;
                        al_set_timer_speed(timer, 1.0/FPS);
                    }
                if(ev.keyboard.keycode ==ALLEGRO_KEY_RIGHT)
                    {
                        if(FPS<250)FPS++;
                        else FPS = 250;
                        al_set_timer_speed(timer, 1.0/FPS);

                    }
                if(ev.keyboard.keycode ==ALLEGRO_KEY_SPACE) //pausa
                    {
                       if(al_get_timer_started(timer))
                                al_stop_timer(timer);
                        else
                                al_start_timer(timer);
                    }
                 if(ev.keyboard.keycode ==ALLEGRO_KEY_ENTER && !al_get_timer_started(timer)) //powrot do menu
                    {
                                        Mrowy.clear();
                                        NieBiale.clear();
                                        redraw = true;
                                        done = false;
                                        goto START;
                    }


            }

        if(redraw && al_is_event_queue_empty(event_queue))
            {
                redraw = false;
                skrecWszystkie(Mrowy, NieBiale);
                while(!czySieZmieszcza(Mrowy, NieBiale))
                {

                for(int i = 0; i < Mrowy.size(); ++i)
                    {
                        tmpRoz = Mrowy[i].getRozmiar();
                        zmniejszPola(Mrowy, NieBiale,tmpRoz);
                        zmniejszMrowki(Mrowy, NieBiale,tmpRoz);
                    }

                }


                  pomalujWszystkie(Mrowy, NieBiale, kolory);

                  for(int i = 0; i < Mrowy.size(); ++i)
                                Mrowy[i].ruch();

            iter++;
            rysujPola(NieBiale);
            rysujMrowy(Mrowy);
            al_flip_display();
            }

    }





return 0;

}



