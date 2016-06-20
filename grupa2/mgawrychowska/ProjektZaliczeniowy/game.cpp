// Projekt zaliczeniowy: Milena Gawrychowska, Martyna Zmuda Trzebiatowska
#include "game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


gra::gra(int row, int col, std::vector<std::vector<state> > init_state)
   : m_row(row), m_col(col), poprzednie_cykle(0)
{
   m_matrix = init_state;
   nxt_matrix = init_state;
}

gra::~gra()
{
}


int gra::sprawdz_ile_jest_zywych(int m, int n)
{
   int count = 0;
   for(int i=m-1; i<=m+1; i++) {
      for(int j=n-1; j<=n+1; j++) {
         if (is_valid_coordinate(i, j) && (m_matrix[i][j] == Zywy)) {
            count++;
         }
      }
   }

   return count;
}

void gra::func(void)
{
   //std::cout << "Hello! - " << x << std::endl;
  // std::cout << "Koniec cykli" << std::endl;
}


/*
 * 1. Komorki zywe bez conajmniej dwoch sasiadow gina.
 * 2. Komorki zywe z wiecej niz trzema sasiadami gina.
 */

void gra::sprawdz_zabierz_zycie(int m, int n)
{
   if(m_matrix[m][n] == Zywy) {
      if(sprawdz_ile_jest_zywych(m, n) < 2) {
         //m_matrix[m][n] = Brak_Zycia;
         nxt_matrix[m][n] = Brak_Zycia;
      }
      if(sprawdz_ile_jest_zywych(m, n) > 3) {
         //m_matrix[m][n] = Brak_Zycia;
         nxt_matrix[m][n] = Brak_Zycia;
      }
   }
}

/* 1.Kazda zywa komorka z dwoma lub trzema sasiadami przechodzi do nastpnego cyklu.
 * 2.Kazda niezywa komorka z trzema zywymi sasiadami otrzymuje zycie.
*/
void gra::sprawdz_daj_zycie(int m, int n)
{
   if(m_matrix[m][n] == Zywy) {
      if( (sprawdz_ile_jest_zywych(m, n) == 3)||(sprawdz_ile_jest_zywych(m, n) == 2)) {
         //m_matrix[m][n] = Zywy;
         nxt_matrix[m][n] = Zywy;
      }
   }
   if(m_matrix[m][n] == Brak_Zycia) {
      if(sprawdz_ile_jest_zywych(m, n) == 3) {
         //m_matrix[m][n] = Zywy;
         nxt_matrix[m][n] = Zywy;
      }
   }
}

void gra::print(int cykle)
{
   poprzednie_cykle = cykle;
   for(int k=0; k<poprzednie_cykle; k++) {
      for(int i=0; i<m_matrix.size(); i++) {
         for(int j=0; j<m_matrix[0].size(); j++) {
            sprawdz_daj_zycie(i, j);
            sprawdz_zabierz_zycie(i, j);
         }
      }

     /* Cykl poczatkowy */
     std::cout << "Stan poczatkowy: " << k << std::endl;
     for(int i=0; i<m_matrix.size(); i++) {
       for(int j=0; j<m_matrix[0].size(); j++) {
         std::cout << " " << m_matrix[i][j] << " ";
       }
       std::cout << std::endl;
     }

      int val = 0;
     /* Nastepny cykl */
     std::cout << "Stan po sprawdzeniu : " << k << std::endl;
     for(int i=0; i<nxt_matrix.size(); i++) {
       for(int j=0; j<nxt_matrix[0].size(); j++) {
         std::cout << " " << nxt_matrix[i][j] << " ";
         val = nxt_matrix[i][j];
         if (val == 1) {
           al_draw_filled_rectangle((i*20),(j*20), (i*20)+20, (j*20)+20, al_map_rgb(255, 255, 0));
         } else {
           al_draw_filled_rectangle((i*20),(j*20), (i*20)+20, (j*20)+20, al_map_rgb(0, 0, 0));
         }
       }
       al_flip_display();
       std::cout << std::endl;
     }
     m_matrix = nxt_matrix;
    al_rest(1.0);
   }
}

int main(int argc, char *argv[])
{
   std::vector<std::vector<state> > init_state;
   int wiekosc_pola = 0;
   int liczba_cykli = 0;

   std::cout << "Gra w Zycie - zalecane wielkosc pola do 30, zalecana wielkosc cykli do 15 "<< std::endl;
   std::cout << "" << std::endl;
     std::cout << "Podaj wielkosc pola : ";

				std::cin>>wiekosc_pola ;
				std::cout << "Podaj liczbe cykli : ";
				std::cin>>liczba_cykli;

   ALLEGRO_DISPLAY *display;

   if(!al_init())
   {
     std::cout << "Nie moze uruchomic allegro" << std::endl;
       return -1;
   }
   al_init_primitives_addon();

   display = al_create_display(ScreenWidth, ScreenHeight);
   if(!display)
   {
     std::cout << "Nie moze utworzyc ekranu" << std::endl;
     return -1;
   }

   al_set_new_display_flags(ALLEGRO_NOFRAME);
   al_set_window_title(display, "  Gra w Zycie  ");

   if (argc == 3) {
     wiekosc_pola = std::atoi(argv[1]);
     liczba_cykli = std::atoi(argv[2]);
   } else {
     std::cout << "Sciezka programu: " << argv[0] << " <Wielkosc pola> <Liczba cykli> " << std::endl;
     std::cout << "Uzyto domyslne ustawienia" << std::endl;
   }

   std::cout << "Wielkosc pola: " << wiekosc_pola << " Liczba cykli: " << liczba_cykli << std::endl;

   init_state.resize(wiekosc_pola);
   for(int i=0; i<wiekosc_pola; i++) {
      init_state[i].resize(wiekosc_pola);
      for(int j=0; j<wiekosc_pola; j++) {
         init_state[i][j] =  ((i + j) % 2 == 0)? Zywy:Brak_Zycia;
      }
   }

   gra::func();

   gra g(wiekosc_pola, wiekosc_pola, init_state);
   g.print(liczba_cykli);

   gra::func();


std::cout << "Koniec cykli" << std::endl;

    al_rest(5.0);
    al_destroy_display(display);

   return 0;
}
