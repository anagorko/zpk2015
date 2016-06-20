#include <cmath>
#include <string>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"

#include <vector>
#include <utility>

enum Kierunek {UP, DOWN, RIGHT, LEFT};

class Mrowa
{
public:
	Mrowa(int MrowaSzer, int MrowaWys, int posX, int posY);
	~Mrowa();

	void wLewo();
	void wPrawo();

	pair<int, int> getPosition()const; //jednoczesnie umozliwia wziecie dwoch wspolrzednych, getX i getY
	void idz(int mapX, int mapY);
	void rysuj(ALLEGRO_BITMAP *tilesBitmap, int bitmapX, int bitmapY);

private:
	enum Kierunek { UP, DOWN, RIGHT, LEFT };
	int mMrowaSzer; //wielkosc trojkata 
	int mMrowaWys; 

	int mX;		// x-owa wspolrzedna plytki 
	int mY;		// y-ta wspolrzedna plytki
	Kierunek mObecnyKierunek;
};

//Definicje metod klasy Mrowa
Mrowa::Mrowa(int MrowaSzer, int MrowaWys, int posX, int posY)  //za pomoca listy inicjujacej
	:mMrowaSzer(MrowaSzer),
	mMrowaWys(MrowaWys),
	mX(posX),
	mY(posY),
	mObecnyKierunek(Kierunek::LEFT)
{
}


Mrowa::~Mrowa()
{}

//Ktore kierunki beda po kolei gdy skreca w Lewo
void Mrowa::wLewo()
{
	switch(mObecnyKierunek)
	{
		case Mrowa::UP:
			mObecnyKierunek = Kierunek::LEFT;
			break;
		case Mrowa::DOWN:
			mObecnyKierunek = Kierunek::RIGHT;
			break;
		case Mrowa::RIGHT:
			mObecnyKierunek = Kierunek::UP;
			break;
		case Mrowa::LEFT:
			mObecnyKierunek = Kierunek::DOWN;
			break;
		default:
			break;
	}
}

//Ktore kierunki beda po kolei gdy skreca w Prawo
void Mrowa::wPrawo()
{
	switch(mObecnyKierunek)
	{
		case Mrowa::UP:
			mObecnyKierunek = Kierunek::RIGHT;
			break;
		case Mrowa::DOWN:
			mObecnyKierunek = Kierunek::LEFT;
			break;
		case Mrowa::RIGHT:
			mObecnyKierunek = Kierunek::DOWN;
			break;
		case Mrowa::LEFT:
			mObecnyKierunek = Kierunek::UP;
			break;
		default:
			break;
	}
}

//Podaje wspolrzedne pola, na ktorym znajduje sie mrowka
pair<int, int> Mrowa::getPosition()const
{
	pair<int, int> ret(mX, mY);
	return ret;
}

//Przesuwa mrowke o 1 pole w zaleznosci od kierunku
void Mrowa::idz(int mapX, int mapY)
{
	switch(mObecnyKierunek)
	{
		case Mrowa::UP:
			--mY;
			break;
		case Mrowa::DOWN:
			++mY;
			break;
		case Mrowa::RIGHT:
			++mX;
			break;
		case Mrowa::LEFT:
			--mX;
			break;
		default:
			break;
	}
// Charakterystyka krawedzi mapy. Jesli dojdzie do konca prawej krawedzi, to pojawi sie z lewej strony i odwrotnie
	if(mX == -1) { mX = mapX - 1; }
	else if(mX == mapX) { mX = 0; }

	if(mY == -1) { mY = mapY - 1; }
	else if(mY == mapY) { mY = 0; }
}

//rysuje znaczek mrowki - trojkat - w zaleznosci od kierunku w ktorym mrowka zmierza
void Mrowa::rysuj(ALLEGRO_BITMAP *tilesBitmap, int bitmapX, int bitmapY)
{
	int flags = 0; //flagi do biblioteki allegro, zeby sie mogly obracac trojkaty
	switch(mObecnyKierunek)
	{
		case Mrowa::UP:
			break;
		case Mrowa::DOWN:
			flags = ALLEGRO_FLIP_VERTICAL; //odwroc trojkat, ktory jest w gore skierowany, 3. pozycja na liscie w bitmapie
			break;
		case Mrowa::RIGHT:
			bitmapX += mMrowaSzer;	//wybierz czwarty obrazek z listy na bitmapie - trojkat w prawo
			break;
		case Mrowa::LEFT:
			bitmapX += mMrowaSzer;
			flags = ALLEGRO_FLIP_HORIZONTAL; //wybierz trojkat w prawo i obroc
			break;
		default:
			break;
	}
//rysuj odpowiednia bitmape
	al_draw_scaled_bitmap(tilesBitmap, bitmapX, bitmapY, 64, 64, mX * 32, mY * 32, 32, 32, flags);
}

//Definicja klasy planszy
class Plansza
{
public:
	Plansza(ALLEGRO_DISPLAY *display);
	~Plansza();

	const float getCameraZoom()const;
	const float getCameraRotate()const;

	void subtractCameraScroll(float x, float y);
	void addCameraZoom(float val);

	int getTileSzer()const;
	int getTileWys()const;

	void idz();
	void rysuj(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *tilesBitmap);

private:

	enum Color { COLOR_BLACK, COLOR_WHITE };

	static const int TILE_Szer;
	static const int TILE_Wys;

	static const int MAP_Szer; //number of tiles in row
	static const int MAP_Wys; //number of tiles in column

	std::vector<Color> mTilesMap;
	float mCameraZoom;
	float mCameraRotate;
	float mCameraScrollX;
	float mCameraScrollY;

	Mrowa mMrowa;
};



const int Plansza::TILE_Szer = 66;
const int Plansza::TILE_Wys = 66;
const int Plansza::MAP_Szer = 100;
const int Plansza::MAP_Wys = 100;

Plansza::Plansza(ALLEGRO_DISPLAY *display)
	:mCameraZoom(0.25f),
	mCameraRotate(0.f),
	mMrowa(TILE_Szer, TILE_Wys, MAP_Szer / 2, MAP_Wys / 2)
{
//rezerwuje sobie stale miejsce w pamieci
	mPlansza.reserve(MAP_Szer*MAP_Wys);
//plansza jest dluga jednowymiarowa tablica (dlugi wiersz)
//poszczegolne czesci wiersza tworza odpowiednie wiersze w planszy
//na kazde pole w tablicy nakladana jest informacja o tym, ze ma byc biale
	for(size_t i = 0; i < MAP_Szer; i++)
	{
		for(size_t j = 0; j < MAP_Wys; j++)
		{
			mPlansza.push_back(COLOR_WHITE);
		}
	}
//dane do polecen allegro, ktore pozwalaja na uzycie efektu zblizania kamery
	mCameraScrollX = MAP_Szer * TILE_Szer / 4;
	mCameraScrollY = MAP_Wys * TILE_Wys / 4;
}

Plansza::~Plansza()
{}
//wszystkie polecenia zwiazane z efektem kamery pochodza z dokumentacji allegro
const float Plansza::getCameraZoom()const
{
	return mCameraZoom;
}

const float Plansza::getCameraRotate()const
{
	return mCameraRotate;
}

void Plansza::subtractCameraScroll(float x, float y)
{
	mCameraScrollX -= x;
	mCameraScrollY -= y;
}

void Plansza::addCameraZoom(float val)
{
	mCameraZoom += val;

	if(mCameraZoom < 0.1) { mCameraZoom = 0.1; }
	if(mCameraZoom > 10) { mCameraZoom = 10; }
}
//szerokosc i wysokosc plytki na planszy
int Plansza::getTileSzer()const
{
	return TILE_Szer;
}

int Plansza::getTileWys()const
{
	return TILE_Wys;
}

//zamiana kolorow plytek, gdy mrowka sobie po niej idzie 
void Plansza::idz()
{
	pair<int, int> MrowaPosition = mMrowa.getPosition();
//element tablicy to element w dlugim wierszu
	switch(mPlansza[MrowaPosition.first + MrowaPosition.second * MAP_Wys])
	{
		case COLOR_BLACK:
			mMrowa.wPrawo();
			mPlansza[MrowaPosition.first + MrowaPosition.second * MAP_Wys] = COLOR_WHITE;
			break;
		case COLOR_WHITE:
			mMrowa.wLewo();
			mPlansza[MrowaPosition.first + MrowaPosition.second * MAP_Wys] = COLOR_BLACK;
			break;
	}

	mMrowa.idz(MAP_Szer, MAP_Wys);
}

void Plansza::rysuj(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *tilesBitmap)
{
	ALLEGRO_TRANSFORM transform;
	float Szer, Wys;

	Szer = al_get_display_Szer(display);
	Wys = al_get_display_Wys(display);

//Poniższe polecenia pochodzą z dokumentacji biblioteki allegro co do transformacji z "oka kamery"
	al_identity_transform(&transform);
	al_translate_transform(&transform, -mCameraScrollX, -mCameraScrollY);
	al_rotate_transform(&transform, mCameraRotate);
	al_scale_transform(&transform, mCameraZoom, mCameraZoom);
	al_translate_transform(&transform, Szer * 0.5, Wys * 0.5);
	al_use_transform(&transform);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_hold_bitmap_drawing(1);

	float tileBitmapSzer = TILE_Szer - 2;	// 2 - szerokość obramowania okna
	float tileBitmapWys = TILE_Wys - 2;	// 2 - szerokość obramowania okna
	float destTileSzer = tileBitmapSzer / 2;
	float destTileWys = tileBitmapWys / 2;

	for(int y = 0; y < MAP_Wys; y++)
	{
		for(int x = 0; x < MAP_Szer; x++)
		{
			int tilesBitmapX = -1; //krańce planszy
			int tilesBitmapY = 1;

			switch(mPlansza[x + y * MAP_Wys])
			{
				case COLOR_BLACK:
					tilesBitmapX = 1; //wybierz pierwszy element z bitmapy - czarny kwadrat
					break;
				case COLOR_WHITE:
					tilesBitmapX = 1 + TILE_Szer; //wybierz drugi element z bitmapy - bialy kwadrat
					break;
			}
			//nalozenie elementow bitmapy na okno i na ekran
			al_draw_scaled_bitmap(tilesBitmap, tilesBitmapX, tilesBitmapY, tileBitmapSzer, tileBitmapWys, x * destTileSzer, y * destTileWys, destTileSzer, destTileWys, 0);
		}
	}
	//narysowanie trojkata mrowki (z bitmapy, trzeci obrazek, bez obracania)
	mMrowa.rysuj(tilesBitmap, 1 + 2 * TILE_Szer, 1);
	
	//Polecenia z dokumentacji allegro
	al_hold_bitmap_drawing(0);
	al_identity_transform(&transform);
	al_use_transform(&transform);
}

//GŁÓWNY program
ALLEGRO_BITMAP * initMainBitmap(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *mainBitmap, int tileSzer, int tileWys);

int main(void)
{
//wskaźniki obiektów na null
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_BITMAP *mainBitmap = nullptr;
	ALLEGRO_TIMER *timer = nullptr;
	ALLEGRO_EVENT_QUEUE *queue = nullptr;
	ALLEGRO_FONT *font = nullptr;
	bool redraw = true;
	int mouse = 0;
	long licznik = 0;

	//Inicjalizacja biblioteki allegro i dodatków, np. obsługi myszy i klawiatury
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_install_mouse();
	al_install_keyboard();

	//Tworzenie okna
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	display = al_create_display(1280, 720);
	al_set_window_title(display, "Projekt zaliczeniowy ZPK: Mrowka Langtona, Edyta Lasek");
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

	Plansza map(display);
	mainBitmap = initMainBitmap(display, mainBitmap, map.getTileSzer(), map.getTileWys());

	font = al_create_builtin_font();

//Ustawienie licznika czasu i kolejki zdarzeń
	timer = al_create_timer(1.0 / 60);
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	bool pause = false;

	while(true)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		//Klawisze sterujące: ESC zamyka program, SPACJA pauzuje
		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	{break;	}
		if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){break;}
			if(event.keyboard.keycode == ALLEGRO_KEY_SPACE)	{pause = !pause;}
		}
		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){mouse = event.mouse.button;}
		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)	{mouse = 0;}
		if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{//Efekty kamery w zaleznosci od wcisniecia klawisza myszy, 1-LPP, 2-PPP
			if(mouse == 1)
			{
				float x = event.mouse.dx / map.getCameraZoom();
				float y = event.mouse.dy / map.getCameraZoom();
				map.subtractCameraScroll(x * cos(map.getCameraRotate()) + y * sin(map.getCameraRotate()), y * cos(map.getCameraRotate()) - x * sin(map.getCameraRotate()));
			}
			if(mouse == 2)
			{map.addCameraZoom(event.mouse.dy * 0.01 * map.getCameraZoom());}
			map.addCameraZoom(event.mouse.dz * 0.1 * map.getCameraZoom());
		}
		if(event.type == ALLEGRO_EVENT_TIMER){redraw = true;}
		if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
		{
			al_acknowledge_resize(display);
			redraw = true;
		}

		if(redraw && al_is_event_queue_empty(queue))
		{
			redraw = false;
			if(!pause)
			{ //Tu sie kreci nasza symulacja
				map.idz();
				++licznik;
			}

			map.rysuj(display, mainBitmap);
			if(font)
			{
				string text = "Liczba iteracji: " + to_string(licznik);
				al_draw_text(font, al_map_rgb(127, 127, 255), 10, 10, 0, text.c_str());
			}

			al_flip_display();
		}
	}
	return 0;
}

{ //Stworzenie bitmapy
// Bitmapa jest zlozeniem czterech figur: czarnego kwadratu, bialego kwadratu, trojkata czerwonego skierowanego w gore, czerwonego trojkata skierowanego w prawo
	ALLEGRO_COLOR COLOR_WHITE = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR COLOR_BLACK = al_map_rgb(68, 68, 68);
	ALLEGRO_COLOR COLOR_RED = al_map_rgb(255, 0, 0);

	mainBitmap = al_create_bitmap(4 * tileSzer, tileWys);
	al_set_target_bitmap(mainBitmap);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));

	al_draw_filled_rectangle(0, 0, tileSzer, tileWys, COLOR_BLACK);
	al_draw_filled_rectangle(tileSzer, 0, 2 * tileSzer, tileWys, COLOR_WHITE);
	al_draw_filled_triangle(2 * tileSzer + tileSzer*0.5f, tileWys* 0.125f,
							2 * tileSzer + tileSzer*0.125f, tileWys* 0.875f,
							2 * tileSzer + tileSzer*0.875f, tileWys* 0.875f, COLOR_RED);	// UP and DOWN
	al_rysuj_filled_triangle(3 * tileSzer + tileSzer*0.125f, tileWys* 0.125f,
							3 * tileSzer + tileSzer*0.125f, tileWys* 0.875f,
							3 * tileSzer + tileSzer*0.875f, tileWys* 0.5f, COLOR_RED);	// RIGHT and LEFT

//Ustawienie bufera żeby nie migał ekran
	al_set_target_backbuffer(display);

	return mainBitmap;
}
