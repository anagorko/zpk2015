#include <vector>
#include <iostream>
#include <cstdlib>

enum state {Brak_Zycia = 0, Zywy = 1};

#define ScreenWidth   600
#define ScreenHeight  600

class gra
{
   private:
   int m_row;
   int m_col;
 std::vector<std::vector<state> > m_matrix;
   std::vector<std::vector<state> > nxt_matrix;

   int poprzednie_cykle;

   void sprawdz_zabierz_zycie(int m, int n);
   void sprawdz_daj_zycie(int m, int n);
   int sprawdz_ile_jest_zywych(int m, int n);
   bool is_valid_coordinate(int r, int c) {
      x++;
      return (((r>=0)&&(r<m_matrix.size()))&&((c>=0)&&(c<m_matrix[0].size())));
   }

   public:
   gra(int row, int col, std::vector<std::vector<state> > init_state);
   static int x;

   static void func(void);
   void foo(gra y) {
      m_row = y.m_row;
   }

   ~gra();

   void print(int cykle);
};

int gra::x = 0;

