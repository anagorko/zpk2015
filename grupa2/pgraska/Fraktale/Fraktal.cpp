#pragma once

#include <allegro5/allegro.h>

#include "Menu.h"
#include "Mandelbrot.h"
#include "Julia.h"

enum WindowState_t
{
	WINDOWSTATE_MENU,
	WINDOWSTATE_MANDELBROT,
	WINDOWSTATE_JULIA
};

enum Actions_t
{
	ACTION_MENU_TO_MANDELBROT,
	ACTION_MENU_TO_JULIA,
	ACTION_RETURN_TO_MENU,
	ACTION_EXIT
};

enum Responds_t
{
	RESPOND_CLICKED,
	RESPOND_NOT_CLICKED,
	RESPOND_CLOSE_WINDOW
};

class Window
{
private:
	Menu* menu;
	Mandelbrot* mandelbrot;
	Julia* julia;

	std::vector<Okno*>okna;
public:

	WindowState_t stanOkna;

	Window(Menu* menu, Mandelbrot* mandelbrot, Julia* julia);
	~Window();

	void SetIteracje(int iteracje);
	int Click(int x, int y);
	void Draw(ALLEGRO_USTR* str);
	bool CzyFraktal() { if (stanOkna == WINDOWSTATE_MANDELBROT) return true;else if (stanOkna == WINDOWSTATE_JULIA)return true;return false; }
	void ZaladujFraktal();
	Fraktal* AktualnyFraktal();
};
