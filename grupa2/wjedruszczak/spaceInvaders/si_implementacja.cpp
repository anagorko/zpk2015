#include "si_naglowek.h"

ObiektBazowy::ObiektBazowy(float x_, float y_, float predkoscObiektu_, int promien_, int punktyZycia_) {
	x = x_;
	y = y_;
	predkoscObiektu = predkoscObiektu_;
	promien = promien_;
	punktyZycia = punktyZycia_;
}

ObiektBazowy::~ObiektBazowy() { }

float ObiektBazowy::podajPredkoscObiektu() const {
	return predkoscObiektu;
}

int ObiektBazowy::podajPromien() const {
	return promien;
}

int ObiektBazowy::podajPunktyZycia() const {
	return punktyZycia;
}

float ObiektBazowy::podajX() const {
	return x;
}

float ObiektBazowy::podajY() const {
	return y;
}

void ObiektBazowy::ustawPredkoscObiektu(int predkoscObiektu_) {
	predkoscObiektu = predkoscObiektu_;
}

void ObiektBazowy::ustawPromien(int promien_) {
	promien = promien_;
}

void ObiektBazowy::ustawPunktyZycia(int punktyZycia_) {
	punktyZycia = punktyZycia_;
}

void ObiektBazowy::ustawX(float x_) {
	x = x_;
}

void ObiektBazowy::ustawY(float y_) {
	y = y_;
}

Dzialko::Dzialko(ALLEGRO_BITMAP * gfx_dzialko_, float x_, float y_, float predkoscObiektu_, int promien_, int punktyZycia_) : ObiektBazowy(x_, y_, predkoscObiektu_, promien_, punktyZycia_) {
	gfx_dzialko = gfx_dzialko_;
};

Dzialko::~Dzialko() { }

void Dzialko::przesunX(float x_) {
	// przy przesuwaniu gra uwzglednia wymiary grafiki dzialka (aby nie wyjsc poza ekran)
	if (szerokosc <= podajX() + x_ + al_get_bitmap_width(gfx_dzialko))
		ustawX(szerokosc - al_get_bitmap_width(gfx_dzialko));
	else if (0 >= podajX() + x_)
		ustawX(0);
	else
		ustawX(podajX() + x_);
}

void Dzialko::przesunY(float y_) {
	// dzialko nie porusza sie w gore / dol, wiec ta funkcja nic nie robi,
	// ale niestety musi zostac zaimplementowana, zeby klasa pochodna nie
	// byla abstrakcyjna
	return;
}

void Dzialko::rysujObiekt() {
	al_draw_bitmap(gfx_dzialko, podajX(), podajY(), 0);
}

Najezdzca::Najezdzca(ALLEGRO_BITMAP * gfx_najezdzca_s01_, ALLEGRO_BITMAP * gfx_najezdzca_s02_, short id_, short stan_, float x_, float y_, float predkoscObiektu_, int promien_, int punktyZycia_) : ObiektBazowy(x_, y_, predkoscObiektu_, promien_, punktyZycia_) {
	gfx_najezdzca_s01 = gfx_najezdzca_s01_;
	gfx_najezdzca_s02 = gfx_najezdzca_s02_;
	id = id_;
	stan = stan_;
};

Najezdzca::~Najezdzca() { }

void Najezdzca::przesunX(float x_) {
	ustawX(podajX() + x_);
}

void Najezdzca::przesunY(float y_) {
	ustawY(podajY() + y_);
}

void Najezdzca::rysujObiekt() {
	// wiekszy czerwony statek to stan == 0; stany 1 i 2 to standardowe stworki
	if (stan == 0 || stan == 1)
		al_draw_bitmap(gfx_najezdzca_s01, podajX(), podajY(), 0);
	else if (stan == 2)
		al_draw_bitmap(gfx_najezdzca_s02, podajX(), podajY(), 0);
}

short Najezdzca::podajID() const {
	return id;
}

short Najezdzca::podajStan() const {
	return stan;
}

void Najezdzca::ustawStan() {
	// stany zmieniaja sie tylko dla standardowych stworkow (1 i 2),
	// dzieki nim powstaje animacja ruchu
	if (stan == 1)
		stan = 2;
	else if (stan == 2)
		stan = 1;
}

Strzal::Strzal(std::string id_, float x_, float y_, float predkoscObiektu_, int promien_, int punktyZycia_) : ObiektBazowy(x_, y_, predkoscObiektu_, promien_, punktyZycia_) {
	id = id_;
}

Strzal::~Strzal() { }

void Strzal::przesunX(float x_) {
	return;
}

void Strzal::przesunY(float y_) {
	if (id == "dzialko") {
		// gdy zostanie przekroczony ekran, zeruja sie pkt. zycia
		if (podajY() <= 0)
			ustawPunktyZycia(0);

		// kierunek strzalu
		y_ *= -1;
	}
	else if (id == "najezdzca") {
		// gdy zostanie przekroczona pozycja dzialka (bez trafienia), zeruja sie pkt. zycia
		if (podajY() >= wysokosc - 50)
			ustawPunktyZycia(0);
	}

	if (podajPunktyZycia())
		ustawY(podajY() + y_);
}

void Strzal::rysujObiekt() {
	al_draw_filled_circle(podajX(), podajY(), podajPromien(), al_map_rgb(0, 0, 0));
}

Oslona::Oslona(ALLEGRO_BITMAP * gfx_oslona_, int promienWewnetrzny_, int szerokosc_, int wysokosc_, float x_, float y_, float predkoscObiektu_, int promien_, int punktyZycia_) : ObiektBazowy(x_, y_, predkoscObiektu_, promien_, punktyZycia_) {
	gfx_oslona = gfx_oslona_;
	promienWewnetrzny = promienWewnetrzny_;
	szerokosc = szerokosc_;
	wysokosc = wysokosc_;
}

Oslona::~Oslona() { }

void Oslona::przesunX(float x_) {
	// obiekt nie porusza sie, ale implementacja musi byc ze wzgledu na uzycie klasy abstrakcyjnej
	return;
}

void Oslona::przesunY(float y_) {
	// obiekt nie porusza sie, ale implementacja musi byc ze wzgledu na uzycie klasy abstrakcyjnej
	return;
}

void Oslona::rysujObiekt() {
	al_draw_bitmap(gfx_oslona, podajX(), podajY(), 0);
}

int Oslona::podajPromienWewnetrzny() const {
	return promienWewnetrzny;
}

int Oslona::podajSzerokosc() const {
	return szerokosc;
}

int Oslona::podajWysokosc() const {
	return wysokosc;
}

void Oslona::ustawOslone(ALLEGRO_BITMAP * gfx_oslona_) {
	// ta metoda pozwala zmienic grafike oslony (potrzebna do imitacji zniszczen)
	gfx_oslona = gfx_oslona_;
}

Gracz::Gracz() {
	fala = 1;
	punkty = 0;
}

Gracz::~Gracz() { }

int Gracz::podajFaleNajezdzcow() const {
	return fala;
}

int Gracz::podajPunkty() const {
	return punkty;
}

void Gracz::ustawFaleNajezdzcow(int fala_) {
	fala = fala_;
}

void Gracz::ustawPunkty(int punkty_) {
	punkty = punkty_;
}

bool Gracz::sprawdzCzyBrakWynikow() const {
	return wyniki.empty();
}

float Gracz::podajWynik(int i) const {
	return wyniki.at(i);
}

int Gracz::podajLiczbeWynikow() const {
	return wyniki.size();
}

void Gracz::zapiszWynik() {
	wyniki.push_back(punkty);
}

void Gracz::wczytajWyniki(const char * plik) {
	// stworzenie obiektu klasy ifstream
	std::ifstream fin;

	// otwarcie pliku
	fin.open(plik);

	// udalo sie otworzyc plik z wynikami
	if (fin.is_open()) {
		int wynik;

		// wczytywanie wynikow
		while (fin >> wynik)
			wyniki.push_back(wynik);
	}
	
	if (!wyniki.empty())
		std::sort(wyniki.begin(), wyniki.end(), std::greater <int> ());

	// konczymy korzystac z pliku
	fin.close();
}

void Gracz::zapiszWyniki(const char * plik) {
	// stworzenie obiektu klasy ofstream
	std::ofstream fout;

	// otwarcie pliku
	fout.open(plik, std::ios::trunc);

	// zapis wynikow
	for (int wynik : wyniki)
		fout << wynik << std::endl;

	// konczymy korzystac z pliku
	fout.close();
}
