#include "Menu.h"
#include "Window.h"


Menu::Menu(int sx, int sy) : Okno(sx, sy)
{
	LoadButtons();
}


Menu::~Menu()
{
}

void Menu::LoadButtons()
{
	przyciski.push_back(new Przycisk(przyciskId++, screenX / 2, 0, Actions_t::ACTION_MENU_TO_MANDELBROT, "gfx/opcja1.bmp"));
	przyciski.push_back(new Przycisk(przyciskId++, screenX / 2, 0, Actions_t::ACTION_MENU_TO_JULIA, "gfx/opcja2.bmp"));
	przyciski.push_back(new Przycisk(przyciskId++, screenX / 2, 0, Actions_t::ACTION_EXIT, "gfx/opcja3.bmp"));

	RozmiescPrzyciski();
}

void Menu::Draw(ALLEGRO_USTR* str)
{
	for (int i = 0;i < przyciski.size();i++)
	{
		przyciski[i]->Draw();
	}
}

int Menu::Click(int x, int y)
{
	for (int i = 0;i < przyciski.size();i++)
	{
		bool click = przyciski[i]->IsClicked(x, y);
		if (click)
		{
			
			int action = przyciski[i]->GetAction();
			if (action == ACTION_MENU_TO_MANDELBROT)
				window->stanOkna = WINDOWSTATE_MANDELBROT;
			else if (action == ACTION_MENU_TO_JULIA)
				window->stanOkna = WINDOWSTATE_JULIA;
			else if (action == ACTION_EXIT)
				return RESPOND_CLOSE_WINDOW;
				
			return RESPOND_CLICKED;
		}
	}
	return RESPOND_NOT_CLICKED;
}

void Menu::RozmiescPrzyciski()
{
	int ilosc = przyciski.size() + 1;
	for (int i = 0;i < przyciski.size();i++)
	{
		przyciski[i]->SetY((screenY / ilosc) * (i + 1));
	}
}
