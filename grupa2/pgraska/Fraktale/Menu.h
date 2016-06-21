#pragma once

#include <vector>

#include "Przycisk.h"
#include "Okno.h"

class Window;
enum Actions_t;

class Menu : public Okno
{
public:
	Menu(int sx, int sy);
	~Menu();

	void LoadButtons();
	void Draw(ALLEGRO_USTR* str);
	int Click(int x, int y);
	void RozmiescPrzyciski();
};
