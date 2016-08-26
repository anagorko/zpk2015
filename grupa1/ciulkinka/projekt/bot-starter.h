// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __BOT_STARTER_H
#define __BOT_STARTER_H

#include <cstdlib>
#include <vector>

#include "bot-state.h"
#include "move.h"

using namespace std;


class BotStarter {

    double ocen(const vector<Cell*> komorki, const Field& pole,
                 int wielkoscKlocka, int _x, int _y) const
    {
        /*x_ oraz y_ to wspolrzedne shapea*/
        double dwys = 0;
        double dpuste = 0;
        double dmin = 0;
        double ddiff = 0;
        double wyn; //wartosc funkcji celu

        int mini = pole.height();
        int wys = 0;

        //tabele pomocnicze
        int tt[pole.width()];
        int puste[pole.width()];

        //zapelnianie tabeli zerami
        for (int i = 0; i < pole.width(); i++)
        {
            tt[i] = 0;
            puste[i] = 0;
        }

        //zapelnianie wlasciwymi liczbami
        for (int x = 0; x < pole.width(); x++)
        {
            for (int y = 1; y < pole.height(); y++) // y = 1, bo w polu na 0. i tak widac nowy klocek, co psuje obliczenia
            {
                if(pole.GetCell(x, y).IsEmpty() == false)
                {
                    tt[x] = y;
                }
                // jesli jest na obszarze shapea to sprawdz z niego
                if(x >= _x && x <= _x + wielkoscKlocka && y >= _y && y <= _y + wielkoscKlocka)
                {
                    for(const Cell* komorka : komorki)
                    {
                        if((komorka->x() == x) && (komorka->y() == y) && (komorka->IsEmpty() == false))
                        {
                            tt[x] = y;
                        }
                    }
                }
            }
        }

        for (int x = 0; x < pole.width(); x++)
        {
            for (int y = tt[x]; y < pole.height(); y++)
            {
                if(pole.GetCell(x, y).IsEmpty() == true)
                {
                    puste[x] = puste[x] + 1;
                }
                // jesli jest na obszarze shapea to sprawdz z niego
                if(x >= _x && x <= _x + wielkoscKlocka && y >= _y && y <= _y + wielkoscKlocka)
                {
                    for(const Cell* komorka : komorki)
                    {
                        if((komorka->x() == x) && (komorka->y() == y) && (komorka->IsEmpty() == true))
                        {
                            puste[x] = puste[x] + 1;
                        }
                    }
                }
            }
        }

        //obliczanie sumy wysokosci
        for (int i = 0; i <= pole.width(); i++)
        {
            dwys = dwys + (double) tt[i];
            dpuste = dpuste + (double) puste[i];
        }

        //obliczanie maksa
        for (int i = 0; i <= pole.width(); i++)
        {
            if(tt[i] > mini) mini = tt[i];
        }
        dmin = (double) mini;

        //obliczenie roznic
        for (int i = 0; i < pole.width() - 1; i++)
        {
            ddiff = ddiff + absolut((double) tt[i + 1] - (double) tt[i]);
        }

        // im wyzszy wynik tym lepiej. (bo lewy gorny rog to (0,0) )

        wyn = (1 * dwys) + (0 * dmin) + (0 * dpuste) + (0 * ddiff);
        return(wyn);
    }


    //funkcja pomocnicza
    double absolut(const double &a) const
    {
        double b;
        if (a < 0)
        {
            b = -a;
        } else
        {
            b = a;
        }

        return b;
    }



 public:
  /**
   * Returns a random amount of random moves
   * @param state : current state of the bot
   * @param timeout : time to respond
   * @return : a list of moves to execute
   */
  vector<Move::MoveType> GetMoves(const BotState& state,
                                  long long timeout) const {

    vector<Move::MoveType> moves;
    const Field& my_field = state.MyField();
    const Point& my_location = state.ShapeLocation();
    //Shape(ShapeType type, const Field& field, int x, int y)
    Shape s = Shape(state.CurrentShape(),
                my_field,
                my_location.first, my_location.second);

    int i;

    //zmienne opisujace liczbe ruchow.
    int l;
    int r;
    int tl;
    int tr;

    //ostatnia wartosc funckcji celu
    double wynik;
    double a;

    int doly; //zmienna pomocnicza.


    //if (state.Round() > 1)
    //{
    wynik = 0; // wysokosc liczy sie od gory, wiec 0 oznacza, ze cala plansza jest zapelniona

    l = 0;
    r = 10;
    tl = 0;
    tr = 0;

    for(int obrL = 3; obrL >= 0; obrL--)
    {
        for (int iks = 0; iks < my_field.width() - s.size(); iks++)
        {
            /**czesc 'drop'**/
            //restartuje wartosc zmiennej doly
            doly = my_location.second;

            //tworze te 2 shape'y tutaj, poniewaz dzieki temu znikaja po kazdej iteracji
            //Shape(ShapeType type, const Field& field, int x, int y)
            Shape szejp = Shape(state.CurrentShape(),
                                my_field,
                                iks, my_location.second);


            Shape testuj = Shape(state.CurrentShape(),
                                 my_field,
                                 iks, my_location.second);
            if (obrL > 0)
            {
                for (int iter = 0; iter < obrL; iter++)
                {
                    szejp.TurnLeft();
                    testuj.TurnLeft();
                }
            }

            while(testuj.IsValid() == true && doly <= my_field.height())
            {
                testuj.OneDown();
                doly++;
            }

            //wlasciwy shape, ktory jest przesuwany o 1 wiersz wyzej niz testuj.
            for (int iter = 0; iter < doly; iter++)
            {
                szejp.OneDown();
            }

            /**czesc 'ocena'**/
            a = ocen(szejp.GetBlocks(),
                     my_field,
                     szejp.size(),
                     szejp.Location().first,
                     szejp.Location().second);


            if(a > wynik)
            {
                l = 0; r = 0;
                tl = 0; tr = 0;

                wynik = a;

                if (iks < my_location.first) l = my_location.first - iks;
                if (iks > my_location.first) r = iks - my_location.first + 1;
                tl = obrL;
            }
        }
    }

    // koniec
    for(i = 0; i < tl; i++)
    {
      moves.push_back(Move::MoveType::TURNLEFT);
    }

    for(i = 0; i < tr; i++)
    {
      moves.push_back(Move::MoveType::TURNRIGHT);
    }

    for(i = 0; i < l; i++)
    {
      moves.push_back(Move::MoveType::LEFT);
    }

    for(i = 0; i < r; i++)
    {
      moves.push_back(Move::MoveType::RIGHT);
    }

    moves.push_back(Move::MoveType::DROP);

    return moves;
  }
};

#endif  //__BOT_STARTER_H
