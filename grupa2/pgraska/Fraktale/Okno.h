#pragma once

#include <vector>
#include <allegro5/allegro.h>

class Przycisk;
class Window;

class Okno
{
protected:
	Window* window;
	int przyciskId = 0, screenX, screenY;
	std::vector<Przycisk*> przyciski;
	double screenRatio;
public:
	Okno() {};
	Okno(int sx, int sy);
	~Okno();

	virtual int Click(int x, int y) = 0;
	virtual void Draw(ALLEGRO_USTR* str) = 0;
	void SetWindow(Window* window) { this->window = window; }
};
