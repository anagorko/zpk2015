#pragma once

#include <stdio.h>
#include <allegro5/allegro.h>

class Window;
enum Actions_t;

class Przycisk
{
private:
	int x, y, sizeX, sizeY, lx, px, gy, dy, id;
	Actions_t action;
	ALLEGRO_BITMAP* bitmap;
public:
	Przycisk(int id, int x, int y, Actions_t action, char* file);
	~Przycisk();

	bool IsClicked(int x, int y);
	void Draw();
	int GetId() { return this->id; }
	Actions_t GetAction() { return this->action; }
	void SetY(int y) { this->y = y; this->gy = y - sizeY / 2; this->dy = y + sizeY / 2; }
};
