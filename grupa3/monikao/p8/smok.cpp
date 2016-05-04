#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <iomanip>

const int w = 800;
const int h = 600;


const int sup = 10000;

double x[sup], y[sup];




void calculate()
{
    /*uzupe³nienie wartoœci pocz¹tkowych x i y w tablicach*/
    x[0] = w/2;
    y[0] = h/2;

    for (int i = 1; i < sup; i++) {
        /*losujemy wed³ug którego uk³adu równañ przekszta³cenie*/
        /*losujemy 100 liczb ca³kowitych z przedzia³u 0-99, sprawdzamy czy liczba jest parzysta
        jest tyle samo parzystych co nieparzystych wiêc takie samo prawdopodobieñstwo*/
        int v1 = rand() % 100;

        /*w zale¿noœci od wyników losowania dokonujemy przekszta³cenia liczby x oraz y*/
        if(v1 % 2 == 0){
            x[i] = -0.4 *x[i-1] - 1;
            y[i] = -0.4 *y[i-1] + 0.1;
        }else{
            x[i] =  0.76*x[i-1] - 0.4 *y[i-1];
            y[i] =  0.4 *x[i-1] + 0.76*y[i-1];
        }
    }


}

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    /*podpunkt a- obliczam pierwsze 10000 wartoœci x i y z kolejnych iteracji*/
    calculate();

    al_clear_to_color(al_map_rgb(0,0,0));

    /*zmienne pomocnicze do wykonania podpunktów c i d zadania*/
    double x_sum;
    double y_sum;
    double x_max = 0.0;
    double y_max = 0.0;
    double x_min = 0.0;
    double y_min = 0.0;
    /*jako œrodek uk³¹du wspó³rzêdnych wybieram punkt x[0] = 400, y[0] = 300
     wykonujê równie¿ przeskalowanie otrzymanych wartoœci x i y przez 100, by by³y widoczne na rysunku */
     /*zgodnie z treœci¹ zadania pomijam na rysunku pierwszych 100 wartoœci x i y*/
    double scale = 300;

    for (int i = 100; i < sup; i++) {
        /*rysowanie*/
        al_draw_pixel( x[0]+ scale*x[i], y[0] + scale*y[i], al_map_rgb(255,255,255));
        /*obliczenia pomocnic*/
        x_sum += x[i];
        y_sum += y[i];
        if(x[i] < x_min)
            x_min = x[i];
        if(y[i] < y_min)
            y_min = y[i];
        if(x[i] > x_max)
            x_max = x[i];
        if(y[i] > y_max)
            y_max = y[i];
    }

    double x_mean = x_sum / (sup-100);
    double y_mean = y_sum / (sup-100); ;

    cout << "Srodek masy smoka: x = " << setprecision(1) << fixed << x[0] + scale * x_mean << ", y = " << y[0] + scale * y_mean <<endl;
    cout << "Rozmiar smoka: x = ( " << setprecision(1) << fixed << x[0] + scale * x_min << ", "
                                                       << x[0] + scale * x_max << "), "
                                                       << "y = ( " << y[0] + scale * y_min <<  ", "
                                                       << y[0] + scale * y_max << "), " <<endl;


    al_flip_display();

    al_rest(7);
    al_destroy_display(display);

    return 0;
}
