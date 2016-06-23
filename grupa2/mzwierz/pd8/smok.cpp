#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <iostream>
using namespace std;

int main(int, char**)
{

    al_init();
    al_init_image_addon();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *display = NULL;

    display = al_create_display(800, 600);

    al_clear_to_color(al_map_rgb(0,0,0));

    double x = 1.0, y = 1.0;			// wartoœci pocz¹tkowe x-a i y-a
    double suma_x = 0.0, suma_y = 0.0;
    double min_x = 100.0, max_x = -100.0, min_y = 100.0, max_y = -100.0; //min i max

    for (int i = 0; i < 5000; i++) {

       int r = rand();

        if(r % 2 ==0){
            suma_x = -0.4 * x - 1;
            suma_y = -0.4 * y + 0.1;
            x = suma_x;
            y = suma_y;
        }
        else {
            suma_x = 0.76 * x - 0.4 * y;
            suma_y = 0.4 * x + 0.76 * y;
            x = suma_x;
            y = suma_y;
        }

        if (i >= 100) {					// obraz po 100 punktach
            if (x > max_x)
                max_x = x;
            else if (x < min_x)
                min_x = x;
            if (y > max_y)
                max_y = y;
            else if (y < min_y)
                min_y = y;

            suma_x += x;
            suma_y += y;

            al_draw_pixel(400 * (x + 1.5), 400 * (y + 0.75), al_map_rgb(255,255,255));
        }
    }

    al_flip_display();
    al_save_bitmap(".bmp", al_get_backbuffer(display));

    al_rest(10.0);

    al_destroy_display(display);

    cout << "Srodek masy smoka: " << endl;
    cout << fixed << setprecision(1) << "x = " << suma_x / double(4900) << endl;
    cout << fixed << setprecision(1) << "y = " << suma_y / double(4900) << endl;
    cout << endl;

    cout << "Rozmiary smoka: " << endl;
    cout << fixed << setprecision(1) << "x_min = " << min_x << " x_max = " << max_x << endl;
    cout << fixed << setprecision(1) << "y_min = " << min_y << " y_max = " << max_y << endl;

}
