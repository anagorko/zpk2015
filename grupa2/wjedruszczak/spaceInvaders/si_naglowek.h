#pragma once
#include<algorithm>
#include<functional>
#include<fstream>
#include<string>
#include<vector>

#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_primitives.h>

const float FPS = { 60.0 };
const int szerokosc = { 1280 };
const int wysokosc = { 720 };

// ponizsza klasa jest abstrakcyjna: bez problemu mozna wyodrebnic pewne wspolne cechy
// klas obiektow, ktore pojawiaja sie w grze; jest ona stworzona tylko do dziedziczenia:
// jest to pewna wygoda, gdy¿ ideowo nie potrzebujemy tworzyc takich obiektow bezposredno
// (co wynika oczywiscie z samego funkcjonowania klas abstrakcyjnych jako takich)
class ObiektBazowy {
private:
	float predkoscObiektu, x, y;
	int promien, punktyZycia;

public:
	ObiektBazowy(float x_ = 0.0, float y_ = 0.0, float predkoscObiektu_ = 0.0, int promien_ = 0.0, int punktyZycia_ = 0);
	virtual ~ObiektBazowy();

	float podajPredkoscObiektu() const;
	int podajPromien() const;
	int podajPunktyZycia() const;
	float podajX() const;
	float podajY() const;

	void ustawPredkoscObiektu(int predkoscObiektu_);
	void ustawPromien(int promien_);
	void ustawPunktyZycia(int punktyZycia_);
	void ustawX(float x_);
	void ustawY(float y_);

	virtual void przesunX(float x_) = 0;
	virtual void przesunY(float y_) = 0;
	virtual void rysujObiekt() = 0;
};

// klasa Dzialko, dziedziczy po klasie ObiektBazowy; posiada dodatkowo dane do obslugi grafiki
class Dzialko : public ObiektBazowy {
private:
	ALLEGRO_BITMAP * gfx_dzialko;

public:
	Dzialko(ALLEGRO_BITMAP * gfx_dzialko_ = nullptr, float x_ = 0.0, float y_ = 0.0, float predkoscObiektu_ = 10.0, int promien_ = 47, int punktyZycia_ = 3);
	~Dzialko();

	virtual void przesunX(float x_);
	virtual void przesunY(float y_);
	virtual void rysujObiekt();
};

// klasa Najezdzca, dziedziczy po klasie ObiektBazowy; posiada dodatkowo 2x dane
// do obslugi grafiki (bo rysunek kazdego stworka ma dwie postacie - ich przelaczanie
// jest obslugiwane za pomoca zmiennej "stan"); id to indentyfikator: sluzy do wyliczania
// odpowiedniej liczby punktow w zaleznosci od trafionego stworka; stan = 0 to wiekszy
// statek, ktory ma tylko jedna grafike
class Najezdzca : public ObiektBazowy {
private:
	ALLEGRO_BITMAP * gfx_najezdzca_s01;
	ALLEGRO_BITMAP * gfx_najezdzca_s02;
	short id;
	short stan;

public:
	Najezdzca(ALLEGRO_BITMAP * gfx_najezdzca_s01_ = nullptr, ALLEGRO_BITMAP * gfx_najezdzca_s02_ = nullptr, short id_ = 1, short stan_ = 1, float x_ = 0.0, float y_ = 0.0, float predkoscObiektu_ = 0.0, int promien_ = 25, int punktyZycia_ = 1);
	~Najezdzca();

	virtual void przesunX(float x_);
	virtual void przesunY(float y_);
	virtual void rysujObiekt();

	short podajID() const;
	short podajStan() const;
	
	void ustawStan();
};

// klasa Strzal, dziedziczy po klasie ObiektBazowy; posiada dodatkowe pole id,
// w zaleznosci od tego czy strzela dzialko czy najezdzca (zeby ustalic kierunek strzalu)
class Strzal : public ObiektBazowy {
private:
	std::string id;

public:
	Strzal(std::string id_ = "puste", float x_ = 0.0, float y_ = 0.0, float predkoscObiektu_ = 3.0, int promien_ = 2, int punktyZycia_ = 1);
	~Strzal();

	virtual void przesunX(float x_);
	virtual void przesunY(float y_);
	virtual void rysujObiekt();
};

// klasa Oslona, dziedziczy po klasie ObiektBazowy; posiada dane do obslugi grafiki,
// oraz dane dot. wymiarow i promienia kola, ktore mozna wpisac w bialym obszarze,
// ktory jest wyznaczany przez ksztalt oslony: chodzi o to, zeby uwzglednic prawidlowo
// kolizjie miedzy strzalem ze statku a oslona
class Oslona : public ObiektBazowy {
private:
	ALLEGRO_BITMAP * gfx_oslona;
	int promienWewnetrzny, szerokosc, wysokosc;

public:
	Oslona(ALLEGRO_BITMAP * gfx_oslona_ = nullptr, int promienWewnetrzny_ = 23, int szerokosc_ = 80, int wysokosc_ = 65, float x_ = 0.0, float y_ = 0.0, float predkoscObiektu_ = 0.0, int promien_ = 40, int punktyZycia_ = 15);
	~Oslona();

	virtual void przesunX(float x_);
	virtual void przesunY(float y_);
	virtual void rysujObiekt();

	int podajPromienWewnetrzny() const;
	int podajSzerokosc() const;
	int podajWysokosc() const;

	void ustawOslone(ALLEGRO_BITMAP * gfx_oslona_ = nullptr);
};

// ta klasa jest odpowiedzialna za obsluge gracza:
// zawiera dane dot. fali przeciwnikow, zdobyte
// punkty, czy wektor wynikow; poza metodami,
// ktore pozwalaja modyfikowac te dane, pozwala
// rowniez wczytac i zapisac wyniki do pliku tekstowego
class Gracz {
private:
	int fala;
	int punkty;
	std::vector <int> wyniki;

public:
	Gracz();
	~Gracz();

	int podajFaleNajezdzcow() const;
	int podajPunkty() const;

	void ustawFaleNajezdzcow(int fala_);
	void ustawPunkty(int punkty_);

	bool sprawdzCzyBrakWynikow() const;
	float podajWynik(int i) const;
	int podajLiczbeWynikow() const;
	void zapiszWynik();

	void wczytajWyniki(const char * plik = "si_wyniki.txt");
	void zapiszWyniki(const char * plik = "si_wyniki.txt");
};