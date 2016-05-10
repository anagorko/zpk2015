#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

int main(int, char**)
{

    al_init();
    al_init_image_addon();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    ALLEGRO_DISPLAY *display = NULL;

    display = al_create_display(800, 600);
    
    al_clear_to_color(al_map_rgb(0,0,0));

    int liczba;
    double x = 1.0, y = 1.0;			// wartości początkowe x-a i y-a
    double suma_x = 0.0, suma_y = 0.0;
    double min_x = 1000000.0, max_x = -1000000.0, min_y = 1000000.0, max_y = -1000000.0;

    srand( time( NULL ) );

    for (int i = 0; i < 5000; i++) {

        liczba = rand() % 2 + 1;		// wybieramy losowo jeden z dwóch układów równań

        switch(liczba) {
        case 1:
            x = -0.4 * x - 1;
            y = -0.4 * y + 0.1;
            break;
        case 2:
            x = 0.76 * x - 0.4 * y;
            y = 0.4 * x + 0.76 * y;
            break;
        }

        if (i >= 100) {					// sporządzamy obraz z pominięciem 100 pierwszych punktów
            if (x > max_x)
                max_x = x;				// aktualizujemy wartość maksymalną x-a
            else if (x < min_x)
                min_x = x;				// aktualizujemy wartość minimalną x-a
            if (y > max_y)
                max_y = y;				// aktualizujemy wartość maksymalną y-a
            else if (y < min_y)
                min_y = y;				// aktualizujemy wartość minimalną y-a

            suma_x += x;				// aktualizujemy sumę x-ow
            suma_y += y;				// aktualizujemy sumę y-ow

            al_draw_pixel(400 * (x + 1.5), 400 * (y + 0.75), al_map_rgb(255,255,255));
        }
    }

    al_flip_display();

    al_save_bitmap(".bmp", al_get_backbuffer(display));

    al_rest(5.0);

    al_destroy_display(display);

    cout << "Srodek masy smoka:" << endl;
    cout << fixed << setprecision(1) << "x = " << suma_x / double(4900) << endl;
    cout << fixed << setprecision(1) << "y = " << suma_y / double(4900) << endl;
    cout << endl;

    cout << "Rozmiary smoka:" << endl;
    cout << fixed << setprecision(1) << "x_min = " << min_x << " x_max = " << max_x << endl;
    cout << fixed << setprecision(1) << "y_min = " << min_y << " y_max = " << max_y << endl;

}
