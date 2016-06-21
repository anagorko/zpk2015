#include "Window.h"
#include "Okno.h"

Window::Window(Menu* menu, Mandelbrot* mandelbrot, Julia* julia)
{
	this->menu = menu;
	this->mandelbrot = mandelbrot;
	this->julia = julia;

	okna.push_back(this->menu);
	okna.push_back(this->mandelbrot);
	okna.push_back(this->julia);
	this->stanOkna = WINDOWSTATE_MENU;
}

Window::~Window()
{
}

void Window::SetIteracje(int iteracje)
{
	Fraktal* fraktal = AktualnyFraktal();
	if (fraktal)
		fraktal->SetLiczbaIteracji(iteracje);
}

int Window::Click(int x, int y)
{
	Okno* aktualne = okna[stanOkna];
	return aktualne->Click(x, y);
}

void Window::Draw(ALLEGRO_USTR* str)
{
	Okno* aktualne = okna[stanOkna];
	aktualne->Draw(str);
}

void Window::ZaladujFraktal()
{
	Fraktal* fraktal = AktualnyFraktal();
	if (fraktal && fraktal->czyBylZaladowany == false)
	{
		fraktal->Generate();
		fraktal->czyBylZaladowany = true;
	}
}

Fraktal * Window::AktualnyFraktal()
{
	if (stanOkna == WINDOWSTATE_MANDELBROT) 
		return mandelbrot;
	else if (stanOkna == WINDOWSTATE_JULIA)
		return julia;
	return nullptr;
}
