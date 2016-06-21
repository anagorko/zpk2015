#include <stdio.h>
#include <string>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Window.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

void InitAllegro()
{
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_image_addon();
}

int SkalujY(int py, double screenRatio, int px, int mx)
{
	return py + screenRatio * static_cast<double>((mx - px));
}

int main(int argc, char **argv)
{
	InitAllegro();

	ALLEGRO_KEYBOARD_STATE klawiatura;
	ALLEGRO_MOUSE_STATE mysz;
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE* key_queue = al_create_event_queue();
	ALLEGRO_DISPLAY* okno = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	ALLEGRO_FONT* defaultFont = al_create_builtin_font();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

	al_register_event_source(key_queue, al_get_display_event_source(okno));
	al_register_event_source(event_queue, al_get_display_event_source(okno));
	al_register_event_source(key_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_set_window_title(okno, "Fraktale");
	al_set_target_bitmap(al_get_backbuffer(okno));
	
	Menu* menu = new Menu(WINDOW_WIDTH, WINDOW_HEIGHT);
	Mandelbrot* mandelbrot = new Mandelbrot(WINDOW_WIDTH, WINDOW_HEIGHT, defaultFont);
	Julia* julia = new Julia(WINDOW_WIDTH, WINDOW_HEIGHT, defaultFont);
	Window* window = new Window(menu, mandelbrot, julia);
	menu->SetWindow(window);
	mandelbrot->SetWindow(window);
	julia->SetWindow(window);

	const ALLEGRO_COLOR backgroundColor = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR frameColor = al_map_rgb(255, 255, 255);
	const int frameThickness = 2;

	ALLEGRO_USTR* str = al_ustr_new("");
	int pos = (int)al_ustr_size(str);

	ALLEGRO_EVENT ev;

	double blokadaKlikniecia = al_get_time();
	
	int poczX = -1, poczY = -1, poprzedniStan = window->stanOkna;
	bool petla = true, klikniecieMyszy = false, klawiszWcisniety = false, wpisywanieIteracji = false;

	double screenRatio = static_cast<double>(WINDOW_HEIGHT) / static_cast<double>(WINDOW_WIDTH);

	while (petla)
	{
		if (poprzedniStan != window->stanOkna)
		{
			blokadaKlikniecia = al_get_time();
		}

		poprzedniStan = window->stanOkna;

		al_get_next_event(event_queue, &ev);
		al_get_mouse_state(&mysz);

		int mx = mysz.x;
		int my = mysz.y;

		bool koniecKlikniecia = false;

		if (mysz.buttons & 1 && klikniecieMyszy == false && al_get_time() > blokadaKlikniecia + 0.3)
		{
			klikniecieMyszy = true;

			if (window->CzyFraktal())
			{
				poczX = mx;
				poczY = my;
			}
		}
		else if (!(mysz.buttons & 1) && klikniecieMyszy == true && al_get_time() > blokadaKlikniecia + 0.3)
		{
			klikniecieMyszy = false;

			int pp = window->stanOkna;

			int respond = window->Click(mx, my);
			if (respond == Responds_t::RESPOND_CLOSE_WINDOW)
				petla = false;

			if (window->CzyFraktal() && (pp == WINDOWSTATE_MANDELBROT || pp == WINDOWSTATE_JULIA))
			{
				koniecKlikniecia = true;
			}

			if (pp == WINDOWSTATE_MENU && window->CzyFraktal())
			{
				window->ZaladujFraktal();
			}
		}

		if (koniecKlikniecia)
		{
			if (window->CzyFraktal())
			{
				Fraktal* fraktal = window->AktualnyFraktal();
				fraktal->Powieksz(poczX, mx, poczY, SkalujY(poczY, screenRatio, poczX, mx));
			}
			poczX = -1, poczY = -1;
		}

		al_get_next_event(key_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && klawiszWcisniety == false && window->CzyFraktal())
		{
			int kod = ev.keyboard.keycode;
			klawiszWcisniety = true;

			if (kod == 9)
			{
				wpisywanieIteracji = true;
			}
			else if (kod == 10)
			{
				Fraktal* fraktal = window->AktualnyFraktal();
				fraktal->Resetuj();
			}
			else if (kod >= 27 && kod <= 36 && wpisywanieIteracji)
			{
				pos += al_ustr_append_chr(str, kod + 21);
			}
			else if (kod == ALLEGRO_KEY_ENTER)
			{
				if (wpisywanieIteracji == true)
					wpisywanieIteracji = false;
				unsigned char* tmp = str->data;
				int t = atoi((const char*)tmp);
				window->SetIteracje(t);
			}
			else if (kod == ALLEGRO_KEY_BACKSPACE)
			{
				if (al_ustr_prev(str, &pos))
					al_ustr_truncate(str, pos);
			}
			else if (kod == ALLEGRO_KEY_ESCAPE)
			{
				window->stanOkna = WINDOWSTATE_MENU;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			klawiszWcisniety = false;
		}

		al_clear_to_color(backgroundColor);

		if (wpisywanieIteracji)
			window->Draw(str);
		else
			window->Draw(NULL);

		if(poczX != -1)
			al_draw_rectangle(poczX, poczY, mx, SkalujY(poczY, screenRatio, poczX, mx), frameColor, frameThickness);
		al_flip_display();
	}
	al_destroy_display(okno);
	return 0;
}
