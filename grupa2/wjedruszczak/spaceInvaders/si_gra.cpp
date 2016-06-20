#include<cmath>
#include<iostream>

#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>

#include "si_naglowek.h"

enum KLAWISZ { LEWY, PRAWY, P, SPACJA };
enum STAN { GRA, MENU, PAUZA, POMOC, PORAZKA, WYGRANA, WYNIKI };

// prototyp funkcji, ktora sprawdza, czy wystapila kolizja dwoch obiektow
bool sprawdzKolizje(const ObiektBazowy * obiekt, const ObiektBazowy * strzal, int obiektSzerokosc, int obiektWysokosc);

// prototyp funkcji, ktora sprawdza, czy wystapila kolizja z oslona
bool sprawdzKolizje(const Oslona * oslona, const Strzal * strzal);

int main() {
	using std::cout;
	using std::endl;

	// inicjalizacja modulow biblioteki ALLEGRO
	al_init();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();

	// obsluga urzadzen zewnetrznych
	al_install_keyboard();
	al_install_mouse();

	// obsluga ekranu i kolejki zdarzen
	ALLEGRO_DISPLAY * okienko = al_create_display(szerokosc, wysokosc);
	ALLEGRO_EVENT_QUEUE * kolejkaZdarzen = al_create_event_queue();
	ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);

	// zrodla zdarzen
	al_register_event_source(kolejkaZdarzen, al_get_display_event_source(okienko));
	al_register_event_source(kolejkaZdarzen, al_get_keyboard_event_source());
	al_register_event_source(kolejkaZdarzen, al_get_mouse_event_source());
	al_register_event_source(kolejkaZdarzen, al_get_timer_event_source(timer));

	// wczytanie czcionek
	ALLEGRO_FONT * czcionkaTekst_36 = al_load_font("si_font_01.ttf", 36, 0);
	ALLEGRO_FONT * czcionkaTekst_48 = al_load_font("si_font_01.ttf", 48, 0);
	ALLEGRO_FONT * czcionkaTytul_192 = al_load_font("si_font_02.ttf", 192, 0); // ta czcionka moze powodowac problemy

	// wczytanie plikow *.png z grafikami
	ALLEGRO_BITMAP * gfx_dzialko_ = al_load_bitmap("gfx_dzialko.png");
	ALLEGRO_BITMAP * gfx_najezdzca_s00_00_ = al_load_bitmap("gfx_najezdzca_00.png");
	ALLEGRO_BITMAP * gfx_najezdzca_s01_01_ = al_load_bitmap("gfx_najezdzca_01_01.png");
	ALLEGRO_BITMAP * gfx_najezdzca_s01_02_ = al_load_bitmap("gfx_najezdzca_01_02.png");
	ALLEGRO_BITMAP * gfx_najezdzca_s02_01_ = al_load_bitmap("gfx_najezdzca_02_01.png");
	ALLEGRO_BITMAP * gfx_najezdzca_s02_02_ = al_load_bitmap("gfx_najezdzca_02_02.png");
	ALLEGRO_BITMAP * gfx_najezdzca_s03_01_ = al_load_bitmap("gfx_najezdzca_03_01.png");
	ALLEGRO_BITMAP * gfx_najezdzca_s03_02_ = al_load_bitmap("gfx_najezdzca_03_02.png");
	ALLEGRO_BITMAP * gfx_oslona_00 = al_load_bitmap("gfx_oslona_00.png");
	ALLEGRO_BITMAP * gfx_oslona_01 = al_load_bitmap("gfx_oslona_01.png");
	ALLEGRO_BITMAP * gfx_oslona_02 = al_load_bitmap("gfx_oslona_02.png");
	ALLEGRO_BITMAP * gfx_oslona_03 = al_load_bitmap("gfx_oslona_03.png");
	ALLEGRO_BITMAP * gfx_oslona_04 = al_load_bitmap("gfx_oslona_04.png");

	// wymiary grafik
	int dzialkoSzerokosc = { al_get_bitmap_width(gfx_dzialko_) };
	int dzialkoWysokosc = { al_get_bitmap_height(gfx_dzialko_) };
	int najezdzcaWiekszySzerokosc = { al_get_bitmap_width(gfx_najezdzca_s00_00_) };
	int najezdzcaWiekszyWysokosc = { al_get_bitmap_height(gfx_najezdzca_s00_00_) };
	int najezdzcaSzerokosc = { al_get_bitmap_width(gfx_najezdzca_s01_01_) };
	int najezdzcaWysokosc = { al_get_bitmap_height(gfx_najezdzca_s01_01_) };
	int oslonaSzerokosc = { al_get_bitmap_width(gfx_oslona_00) };
	int oslonaWysokosc = { al_get_bitmap_height(gfx_oslona_00) };

	// obiekty gry
	Dzialko dzialko = Dzialko(gfx_dzialko_, szerokosc / 2 - dzialkoSzerokosc / 2, wysokosc - 75 - dzialkoWysokosc / 2);
	Gracz gracz;
	std::vector <Najezdzca> najezdzcy;
	std::vector <Najezdzca> wiekszyNajezdzca;
	std::vector <Strzal> strzalDzialko;
	std::vector <Strzal> strzalNajezdzcy;
	std::vector <Oslona> oslony;

	// wczytanie wynikow gry
	gracz.wczytajWyniki();

	// dane z inf. diagnostycznymi
	std::vector <bool> trafioneDzialko;
	std::vector <bool> trafionyNajezdzca;
	std::vector <bool> trafionyWiekszyNajezdzca;
	std::vector <bool> trafionaOslonaDzialko;
	std::vector <bool> trafionaOslonaNajezdzca;

	// generowanie najezdzcow
	for (int y = 340; y >= 100; y -= 60) {
		for (int x = 100; x <= 700; x += 60) {
			if (y <= 100)
				najezdzcy.push_back(Najezdzca(gfx_najezdzca_s01_01_, gfx_najezdzca_s01_02_, 3, 1, x - najezdzcaSzerokosc / 2, y - najezdzcaWysokosc / 2));
			else if (y <= 220 && y > 100)
				najezdzcy.push_back(Najezdzca(gfx_najezdzca_s02_01_, gfx_najezdzca_s02_02_, 2, 1, x - najezdzcaSzerokosc / 2, y - najezdzcaWysokosc / 2));
			else if (y <= 340 && y > 220)
				najezdzcy.push_back(Najezdzca(gfx_najezdzca_s03_01_, gfx_najezdzca_s03_02_, 1, 1, x - najezdzcaSzerokosc / 2, y - najezdzcaWysokosc / 2));
		}
	}

	// generowanie oslon
	for (int i = 1; i <= 4; ++i)
		oslony.push_back(Oslona(gfx_oslona_00, 23, 80, 65, 192 * i + 80 * (i - 1), wysokosc - wysokosc / 3.5));

	// obsluga glownej petli
	bool diagnostyka = { false };
	bool grajPonownie = { false };
	bool klawisze[4] = { false, false, false, false };
	bool koniecPetliGlownej = { false };
	bool rysuj = { true };
	STAN stanGry = { MENU };

	// obsluga kolorow w menu
	bool kolorCzerwonyKoniec = { false };
	bool kolorCzerwonyNowaGra = { false };
	bool kolorCzerwonyPomoc = { false };
	bool kolorCzerwonyPowrot = { false };
	bool kolorCzerwonyWyniki = { false };

	// obsluga dodatkowego statku
	bool pokazWiekszegoNajezdzce = { true };
	bool ustalonoKierunekWiekszegoNajezdzcy = { false };
	int kierunekWiekszegoNajezdzcy = { 0 };

	// obsluga ruchu najezdzcow
	bool koniecOkienka = { false };
	int licznik = { 0 };
	int czas = { 50 };
	int czasDoWystrzalu = { 50 };
	int kierunek = { 1 };
	int ruchPoziomo = { 23 };
	int ruchPionowo = { 25 };
	int liczbaZestrzelonychNajezdzcow = { 0 };

	al_start_timer(timer);
	srand(time(NULL));

	while (!koniecPetliGlownej) {
		ALLEGRO_EVENT zdarzenie;
		al_wait_for_event(kolejkaZdarzen, &zdarzenie);

		if (zdarzenie.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			koniecPetliGlownej = true;
		else if (zdarzenie.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (zdarzenie.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT: klawisze[PRAWY] = true;
					break;
				case ALLEGRO_KEY_LEFT: klawisze[LEWY] = true;
					break;
				case ALLEGRO_KEY_SPACE: klawisze[SPACJA] = true;
					break;
				case ALLEGRO_KEY_0: diagnostyka = diagnostyka ? false : true;
					break;
				case ALLEGRO_KEY_T:
					{
						if (stanGry == PORAZKA || stanGry == WYGRANA)
							grajPonownie = true;
						break;
					}
				case ALLEGRO_KEY_N:
					{
						if (stanGry == PORAZKA || stanGry == WYGRANA)
							koniecPetliGlownej = true;
						break;
					}
				case ALLEGRO_KEY_P:
					{
						if (stanGry == GRA) {
							stanGry = PAUZA;
							klawisze[P] = true;
						}
						else if (stanGry == PAUZA) {
							stanGry = GRA;
							klawisze[P] = false;
						}
						break;
					}
				case ALLEGRO_KEY_ESCAPE: koniecPetliGlownej = true;
					break;
			}
		}
		else if (zdarzenie.type == ALLEGRO_EVENT_KEY_UP) {
			switch (zdarzenie.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT: klawisze[PRAWY] = false;
					break;
				case ALLEGRO_KEY_LEFT: klawisze[LEWY] = false;
					break;
			}
		}
		else if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_AXES || zdarzenie.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			if (diagnostyka && (stanGry == MENU || stanGry == POMOC || stanGry == WYNIKI)) {
				// wyswietla polozenie myszy, na podstawie tych wspolrzednych ustalono strefe napisow w menu
				cout << "X: " << zdarzenie.mouse.x << endl;
				cout << "Y: " << zdarzenie.mouse.y << endl;
			}

			if (stanGry == MENU) {
				// mysz najechala na napis "NOWA GRA"
				if (zdarzenie.mouse.x >= 545 && zdarzenie.mouse.x <= 740 && zdarzenie.mouse.y >= 395 && zdarzenie.mouse.y <= 425)
					kolorCzerwonyNowaGra = true;
				else
					kolorCzerwonyNowaGra = false;

				// mysz najechala na napis "POMOC"
				if (zdarzenie.mouse.x >= 575 && zdarzenie.mouse.x <= 705 && zdarzenie.mouse.y >= 445 && zdarzenie.mouse.y <= 475)
					kolorCzerwonyPomoc = true;
				else
					kolorCzerwonyPomoc = false;

				// mysz najechala na napis "WYNIKI"
				if (zdarzenie.mouse.x >= 570 && zdarzenie.mouse.x <= 710 && zdarzenie.mouse.y >= 495 && zdarzenie.mouse.y <= 525)
					kolorCzerwonyWyniki = true;
				else
					kolorCzerwonyWyniki = false;

				// mysz najechala na napis "KONIEC"
				if (zdarzenie.mouse.x >= 565 && zdarzenie.mouse.x <= 715 && zdarzenie.mouse.y >= 545 && zdarzenie.mouse.y <= 575)
					kolorCzerwonyKoniec = true;
				else
					kolorCzerwonyKoniec = false;
			}
			else if (stanGry == POMOC || stanGry == WYNIKI) {
				// mysz najechala na napis "POWROT DO MENU"
				if (zdarzenie.mouse.x >= 455 && zdarzenie.mouse.x <= 790 && zdarzenie.mouse.y >= 650 && zdarzenie.mouse.y <= 680)
					kolorCzerwonyPowrot = true;
				else
					kolorCzerwonyPowrot = false;
			}
		}
		else if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (stanGry == MENU) {
				// zmiana stanu jezeli mysz jest w obszarze napisu "NOWA GRA" i kliknieto
				if (zdarzenie.mouse.x >= 545 && zdarzenie.mouse.x <= 740 && zdarzenie.mouse.y >= 395 && zdarzenie.mouse.y <= 425) {
					stanGry = GRA;

					// estetyka
					if (kolorCzerwonyNowaGra)
						kolorCzerwonyNowaGra = false;
				}
				// zmiana stanu jezeli mysz jest w obszarze napisu "POMOC" i kliknieto
				if (zdarzenie.mouse.x >= 575 && zdarzenie.mouse.x <= 705 && zdarzenie.mouse.y >= 445 && zdarzenie.mouse.y <= 475) {
					stanGry = POMOC;

					// estetyka
					if (kolorCzerwonyPomoc)
						kolorCzerwonyPomoc = false;
					if (kolorCzerwonyPowrot)
						kolorCzerwonyPowrot = false;
				}
				// zmiana stanu jezeli mysz jest w obszarze napisu "WYNIKI" i kliknieto
				if (zdarzenie.mouse.x >= 570 && zdarzenie.mouse.x <= 710 && zdarzenie.mouse.y >= 495 && zdarzenie.mouse.y <= 525) {
					stanGry = WYNIKI;

					// estetyka
					if (kolorCzerwonyWyniki)
						kolorCzerwonyWyniki = false;
					if (kolorCzerwonyPowrot)
						kolorCzerwonyPowrot = false;
				}
				// zamkniecie aplikacji jezeli mysz jest w obszarze napisu "KONIEC" i kliknieto
				if (zdarzenie.mouse.x >= 565 && zdarzenie.mouse.x <= 715 && zdarzenie.mouse.y >= 545 && zdarzenie.mouse.y <= 575)
					koniecPetliGlownej = true;
			}
			else if (stanGry == POMOC || stanGry == WYNIKI) {
				// powrot do menu jezeli mysz jest w obszarze napisu "POWROT DO MENU" i kliknieto
				if (zdarzenie.mouse.x >= 455 && zdarzenie.mouse.x <= 790 && zdarzenie.mouse.y >= 650 && zdarzenie.mouse.y <= 680)
					stanGry = MENU;
			}
		}
		else if (zdarzenie.type == ALLEGRO_EVENT_TIMER) {
			rysuj = true;

			if (stanGry == GRA) {
				if (!klawisze[P]) {
					if (klawisze[LEWY])
						dzialko.przesunX(-dzialko.podajPredkoscObiektu());
					if (klawisze[PRAWY])
						dzialko.przesunX(dzialko.podajPredkoscObiektu());
					if (klawisze[SPACJA]) {
						klawisze[SPACJA] = false;
						strzalDzialko.push_back(Strzal("dzialko", dzialko.podajX() + dzialkoSzerokosc / 2, dzialko.podajY() - dzialkoWysokosc / 10, 4.0));
					}

					// sprawdzenie czy doszlo do kolizji (strzal z dzialka vs. najezdzca)
					for (int i = 0; i < strzalDzialko.size(); ++i) {
						for (int j = 0; j < najezdzcy.size(); ++j) {
							if (najezdzcy.at(j).podajPunktyZycia() > 0) {
								if (sprawdzKolizje(&najezdzcy.at(j), &strzalDzialko.at(i), najezdzcaSzerokosc / 2, najezdzcaWysokosc / 2)) {
									// dodawanie punktow za trafienie poszczegolnych stworkow
									if (najezdzcy.at(j).podajID() == 1)
										gracz.ustawPunkty(gracz.podajPunkty() + 10);
									else if (najezdzcy.at(j).podajID() == 2)
										gracz.ustawPunkty(gracz.podajPunkty() + 20);
									else if (najezdzcy.at(j).podajID() == 3)
										gracz.ustawPunkty(gracz.podajPunkty() + 40);

									// odjecie pkt. zycia
									najezdzcy.at(j).ustawPunktyZycia(0);
									strzalDzialko.at(i).ustawPunktyZycia(0);

									// liczba trafien
									++liczbaZestrzelonychNajezdzcow;

									// diagnostyka
									trafionyNajezdzca.push_back(true);
									break;
								}
							}
						}
					}

					// sprawdzenie czy doszlo do kolizji (strzal z dzialka vs. oslona)
					for (int i = 0; i < strzalDzialko.size(); ++i) {
						for (int j = 0; j < oslony.size(); ++j) {
							if (oslony.at(j).podajPunktyZycia() > 0) {
								if (sprawdzKolizje(&oslony.at(j), &strzalDzialko.at(i))) {
									// odjecie pkt. zycia
									oslony.at(j).ustawPunktyZycia(oslony.at(j).podajPunktyZycia() - 1);
									strzalDzialko.at(i).ustawPunktyZycia(0);

									// zmiana grafiki dzialka
									if (oslony.at(j).podajPunktyZycia() > 9 && oslony.at(j).podajPunktyZycia() <= 12)
										oslony.at(j).ustawOslone(gfx_oslona_01);
									else if (oslony.at(j).podajPunktyZycia() > 6 && oslony.at(j).podajPunktyZycia() <= 9)
										oslony.at(j).ustawOslone(gfx_oslona_02);
									else if (oslony.at(j).podajPunktyZycia() > 3 && oslony.at(j).podajPunktyZycia() <= 6)
										oslony.at(j).ustawOslone(gfx_oslona_03);
									else if (oslony.at(j).podajPunktyZycia() <= 3)
										oslony.at(j).ustawOslone(gfx_oslona_04);

									// diagnostyka
									trafionaOslonaDzialko.push_back(true);
									break;
								}
							}
						}
					}

					// losowanie wystapienia wiekszego najezdzcy
					if (rand() % 500 == 1 && liczbaZestrzelonychNajezdzcow < 55 && pokazWiekszegoNajezdzce) {
						// losowanie, czy wyleci z lewej strony czy prawej
						if (!ustalonoKierunekWiekszegoNajezdzcy) {
							if (rand() % 2 == 1)
								kierunekWiekszegoNajezdzcy = -1; // prawa strona
							else
								kierunekWiekszegoNajezdzcy = 1;  // lewa strona
						}

						// wyleci z prawej lub lewej strony (zza widocznego ekranu)
						float x_ = kierunekWiekszegoNajezdzcy == -1 ? (szerokosc + najezdzcaWiekszySzerokosc) : (0 - najezdzcaWiekszySzerokosc);

						// generowanie wiekszego najezdzcy
						wiekszyNajezdzca.push_back(Najezdzca(gfx_najezdzca_s00_00_, nullptr, 4, 0, x_, 10, 3, 48));

						// resetowanie zmiennych odpowiedzialnych za wyswietlenie poj. najezdzcy w trakcie jednej fali
						ustalonoKierunekWiekszegoNajezdzcy = true;
						pokazWiekszegoNajezdzce = false;
					}

					// ruch wiekszego najezdzcy (w lewo lub prawo)
					for (int i = 0; i < wiekszyNajezdzca.size(); ++i) {
						if (wiekszyNajezdzca.at(i).podajPunktyZycia() > 0)
							wiekszyNajezdzca.at(i).ustawX(wiekszyNajezdzca.at(i).podajX() + (kierunekWiekszegoNajezdzcy * wiekszyNajezdzca.at(i).podajPredkoscObiektu()));
					}

					// sprawdzanie stanu wiekszego najezdzcy (przekroczyl druga strone ekranu)
					for (int i = 0; i < wiekszyNajezdzca.size(); ++i) {
						if (wiekszyNajezdzca.at(i).podajPunktyZycia() > 0) {
							// czy lecial z lewej strony i przekroczyl prawa lub lecial z prawej strony i przekroczyl lewa, ale nie zostal trafiony
							if ((wiekszyNajezdzca.at(i).podajX() > szerokosc && kierunekWiekszegoNajezdzcy == 1) ||
								(wiekszyNajezdzca.at(i).podajX() < 0 - 2 * najezdzcaWiekszySzerokosc && kierunekWiekszegoNajezdzcy == -1)) {
								// kasowanie wiekszego najezdzcy
								wiekszyNajezdzca.erase(wiekszyNajezdzca.begin() + i);

								// poniewaz nie zostal trafiony, moze jeszcze raz zostac wylosowany
								pokazWiekszegoNajezdzce = true;
								ustalonoKierunekWiekszegoNajezdzcy = false;
							}
						}
					}

					// sprawdzenie czy doszlo do kolizji (strzal z dzialka vs. wiekszy najezdzca)
					for (int i = 0; i < strzalDzialko.size(); ++i) {
						for (int j = 0; j < wiekszyNajezdzca.size(); ++j) {
							if (wiekszyNajezdzca.at(j).podajPunktyZycia() > 0) {
								if (sprawdzKolizje(&wiekszyNajezdzca.at(j), &strzalDzialko.at(i), najezdzcaSzerokosc, najezdzcaWysokosc / 6)) {
									// dodawanie punktow za trafienie poszczegolnych stworkow
									gracz.ustawPunkty(gracz.podajPunkty() + 50 + rand() % 451);

									// odjecie pkt. zycia
									wiekszyNajezdzca.at(j).ustawPunktyZycia(0);
									strzalDzialko.at(i).ustawPunktyZycia(0);

									// kasowanie wiekszego najezdzcy
									wiekszyNajezdzca.erase(wiekszyNajezdzca.begin() + j);

									// w pojedynczej fali tylko raz mozna trafic w duzego najezdzce
									pokazWiekszegoNajezdzce = false;

									// diagnostyka
									trafionyWiekszyNajezdzca.push_back(true);
									break;
								}
							}
						}
					}

					// gracz wygral jezeli zestrzelil wszystkie statki
					if (liczbaZestrzelonychNajezdzcow == 55 && wiekszyNajezdzca.empty())
						stanGry = WYGRANA;

					// sprawdzanie polozenia najezdzcow i ewentualna zmiana kierunku
					for (int i = 0; i < najezdzcy.size(); ++i) {
						if (najezdzcy.at(i).podajPunktyZycia() > 0 && najezdzcy.at(i).podajX() + 70 >= szerokosc) {
							kierunek = -1;
							koniecOkienka = true;
							break;
						}
						else if (najezdzcy.at(i).podajPunktyZycia() > 0 && najezdzcy.at(i).podajX() <= 23) {
							kierunek = 1;
							koniecOkienka = true;
							break;
						}
					}

					// przesuwanie najezdzcow
					if (licznik == 0) {
						if (koniecOkienka) {
							for (int i = 0; i < najezdzcy.size(); ++i) {
								najezdzcy.at(i).przesunY(ruchPionowo);
								najezdzcy.at(i).ustawStan();
							}

							if (czas > 10)
								czas -= 10;
							koniecOkienka = false;
						}

						for (int i = 0; i < najezdzcy.size(); ++i) {
							najezdzcy.at(i).przesunX(kierunek * ruchPoziomo);
							najezdzcy.at(i).ustawStan();
						}
						licznik = czas;
					}

					if (licznik > 0)
						licznik--;

					// strzelanie najezdzcow
					if (czasDoWystrzalu == 0) {
						int wylosowanaKolumna = rand() % 11;
						int ktoryWiersz;
						int ktoraKolumna = wylosowanaKolumna;
						while (najezdzcy.at(44 + ktoraKolumna).podajPunktyZycia() == 0 && ktoraKolumna != wylosowanaKolumna) {
							if (ktoraKolumna <= 10)
								++wylosowanaKolumna;
							else
								ktoraKolumna = 0;
						}
						for (int j = 0; j <= 4; ++j) {
							if (najezdzcy.at(11 * j + ktoraKolumna).podajPunktyZycia() > 0) {
								ktoryWiersz = j;
								break;
							}
						}
						if (najezdzcy.at(11 * ktoryWiersz + ktoraKolumna).podajPunktyZycia() > 0 && rand() % 5 == 0) {
							strzalNajezdzcy.push_back(Strzal("najezdzca", najezdzcy.at(11 * ktoryWiersz + ktoraKolumna).podajX() + najezdzcaSzerokosc / 2, najezdzcy.at(11 * ktoryWiersz + ktoraKolumna).podajY() + najezdzcaWysokosc, 6.0));
							czasDoWystrzalu = 2 * czas;
						}
					}

					if (czasDoWystrzalu > 0)
						czasDoWystrzalu--;

					// sprawdzenie czy doszlo do kolizji (strzal najezdzcy vs. oslona)
					for (int i = 0; i < strzalNajezdzcy.size(); ++i) {
						for (int j = 0; j < oslony.size(); ++j) {
							if (oslony.at(j).podajPunktyZycia() > 0) {
								if (sprawdzKolizje(&oslony.at(j), &strzalNajezdzcy.at(i), oslonaSzerokosc / 2, oslonaWysokosc / 2 + 5)) {
									// odjecie pkt. zycia
									oslony.at(j).ustawPunktyZycia(oslony.at(j).podajPunktyZycia() - 1);
									strzalNajezdzcy.at(i).ustawPunktyZycia(0);

									// zmiana grafiki oslony w zaleznosci od liczby pkt. zycia
									if (oslony.at(j).podajPunktyZycia() > 9 && oslony.at(j).podajPunktyZycia() <= 12)
										oslony.at(j).ustawOslone(gfx_oslona_01);
									else if (oslony.at(j).podajPunktyZycia() > 6 && oslony.at(j).podajPunktyZycia() <= 9)
										oslony.at(j).ustawOslone(gfx_oslona_02);
									else if (oslony.at(j).podajPunktyZycia() > 3 && oslony.at(j).podajPunktyZycia() <= 6)
										oslony.at(j).ustawOslone(gfx_oslona_03);
									else if (oslony.at(j).podajPunktyZycia() <= 3)
										oslony.at(j).ustawOslone(gfx_oslona_04);

									// diagnostyka
									trafionaOslonaNajezdzca.push_back(true);
									break;
								}
							}
						}
					}

					// sprawdzenie czy doszlo do kolizji (strzal najezdzcy vs. dzialko)
					for (int i = 0; i < strzalNajezdzcy.size(); ++i) {
						if (dzialko.podajPunktyZycia() > 0) {
							if (sprawdzKolizje(&dzialko, &strzalNajezdzcy.at(i), dzialkoSzerokosc / 2, dzialkoWysokosc)) {
								// odjecie pkt. zycia
								dzialko.ustawPunktyZycia(dzialko.podajPunktyZycia() - 1);
								strzalNajezdzcy.at(i).ustawPunktyZycia(0);

								// resetowanie polozenia dzialka
								dzialko.ustawX(szerokosc / 2 - dzialkoSzerokosc / 2);
								dzialko.ustawY(wysokosc - 75 - dzialkoWysokosc / 2);

								// diagnostyka
								trafioneDzialko.push_back(true);
								break;
							}
						}
					}

					// porazka gracza (brak pkt. zycia)
					if (dzialko.podajPunktyZycia() == 0)
						stanGry = PORAZKA;

					// porazka gracza (stworki podlecialy za blisko)
					for (int i = 0; i < najezdzcy.size(); ++i) {
						if (najezdzcy.at(i).podajPunktyZycia() > 0)
							if (najezdzcy.at(i).podajY() + najezdzcaWysokosc / 2 >= oslony.at(1).podajY() - 10)
								stanGry = PORAZKA;
					}

					// uaktualnienie stanu strzalu (dzialko)
					for (int i = 0; i < strzalDzialko.size(); ++i) {
						if (strzalDzialko.at(i).podajPunktyZycia() > 0)
							// przesuniecie strzalu, ktory nie trafil i nie wypadl poza plansze
							strzalDzialko.at(i).przesunY(strzalDzialko.at(i).podajPredkoscObiektu());
						else
							// usuniecie zbednych strzalow
							strzalDzialko.erase(strzalDzialko.begin() + i);
					}

					// uaktualnienie stanu strzalu (najezdzcy)
					for (int i = 0; i < strzalNajezdzcy.size(); ++i) {
						if (strzalNajezdzcy.at(i).podajPunktyZycia() > 0)
							// przesuniecie strzalu, ktory nie trafil i nie wypadl poza plansze
							strzalNajezdzcy.at(i).przesunY(strzalNajezdzcy.at(i).podajPredkoscObiektu());
						else
							// usuniecie zbednych strzalow
							strzalNajezdzcy.erase(strzalNajezdzcy.begin() + i);
					}
				}
			}
		}

		if (rysuj && al_is_event_queue_empty(kolejkaZdarzen)) {
			rysuj = false;
			
			if (stanGry == MENU) {
				al_draw_text(czcionkaTytul_192, al_map_rgb(0, 0, 0), szerokosc / 2 - 192, wysokosc / 2 - 192, 0, ".");

				// napis "NOWA GRA" w kolorze czerwonym (jezeli najechano na niego), czarny w.p.p.
				if (kolorCzerwonyNowaGra)
					al_draw_text(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 - 95, wysokosc / 2 + 30, 0, "NOWA GRA");
				else
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 95, wysokosc / 2 + 30, 0, "NOWA GRA");

				// napis "POMOC" w kolorze czerwonym (jezeli najechano na niego), czarny w.p.p.
				if (kolorCzerwonyPomoc)
					al_draw_text(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 - 65, wysokosc / 2 + 80, 0, "POMOC");
				else
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 65, wysokosc / 2 + 80, 0, "POMOC");

				// napis "WYNIKI" w kolorze czerwonym (jezeli najechano na niego), czarny w.p.p.
				if (kolorCzerwonyWyniki)
					al_draw_text(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 - 70, wysokosc / 2 + 130, 0, "WYNIKI");
				else
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 70, wysokosc / 2 + 130, 0, "WYNIKI");

				// napis "KONIEC" w kolorze czerwonym (jezeli najechano na niego), czarny w.p.p.
				if (kolorCzerwonyKoniec)
					al_draw_text(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 - 75, wysokosc / 2 + 180, 0, "KONIEC");
				else
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 75, wysokosc / 2 + 180, 0, "KONIEC");
			}
			else if (stanGry == GRA || stanGry == PAUZA) {
				// rysowanie dzialka
				if (dzialko.podajPunktyZycia() > 0)
					dzialko.rysujObiekt();

				// rysowanie oslon
				for (int i = 0; i < oslony.size(); ++i)
					if (oslony.at(i).podajPunktyZycia() > 0)
						oslony.at(i).rysujObiekt();

				// rysowanie najezdzcow
				for (int i = 0; i < najezdzcy.size(); ++i)
					if (najezdzcy.at(i).podajPunktyZycia() > 0)
						najezdzcy.at(i).rysujObiekt();

				// rysowanie wiekszego najezdzcy
				for (int i = 0; i < wiekszyNajezdzca.size(); ++i)
					if (wiekszyNajezdzca.at(i).podajPunktyZycia() > 0)
						wiekszyNajezdzca.at(i).rysujObiekt();

				// rysowanie strzalu (dzialko)
				for (int i = 0; i < strzalDzialko.size(); ++i)
					strzalDzialko.at(i).rysujObiekt();

				// rysowanie strzalu (najezdzcy)
				for (int i = 0; i < strzalNajezdzcy.size(); ++i)
					if (strzalNajezdzcy.at(i).podajPunktyZycia() > 0)
						strzalNajezdzcy.at(i).rysujObiekt();

				if (stanGry == GRA) {
					if (diagnostyka) {
						// na podstawie ponizszych rysunkow dopasowano odpowiednie kola zeby wyznaczyc sensowne strefy kolizji

						// strefa kolizji dzialka 
						al_draw_circle(dzialko.podajX() + dzialkoSzerokosc / 2, dzialko.podajY() + dzialkoWysokosc, 47, al_map_rgb(255, 0, 0), 2);

						// strefa kolizji oslon
						for (int i = 0; i < oslony.size(); ++i)
							if (oslony.at(i).podajPunktyZycia() > 0)
								al_draw_circle(oslony.at(i).podajX() + oslonaSzerokosc / 2, oslony.at(i).podajY() + oslonaWysokosc / 2 + 5, 40, al_map_rgb(255, 0, 0), 2);

						// strefa kolizji oslon (fragment, ktory trzeba wylaczyc)
						for (int i = 0; i < oslony.size(); ++i)
							if (oslony.at(i).podajPunktyZycia() > 0)
								al_draw_circle(oslony.at(i).podajX() + oslonaSzerokosc / 2, oslony.at(i).podajY() + oslonaWysokosc - 15, 23, al_map_rgb(255, 0, 0), 2);

						// strefa kolizji najezdzcow
						for (int i = 0; i < najezdzcy.size(); ++i)
							if (najezdzcy.at(i).podajPunktyZycia() > 0)
								al_draw_circle(najezdzcy.at(i).podajX() + najezdzcaSzerokosc / 2, najezdzcy.at(i).podajY() + najezdzcaWysokosc / 2, 25, al_map_rgb(255, 0, 0), 2);

						// strefa kolizji wiekszego najezdzcy
						for (int i = 0; i < wiekszyNajezdzca.size(); ++i)
							al_draw_circle(wiekszyNajezdzca.at(i).podajX() + najezdzcaWiekszySzerokosc / 2, wiekszyNajezdzca.at(i).podajY() + najezdzcaWiekszyWysokosc / 6, 48, al_map_rgb(255, 0, 0), 2);

						// strefa kolizji strzalu (dzialko)
						for (int i = 0; i < strzalDzialko.size(); ++i)
							al_draw_circle(strzalDzialko.at(i).podajX(), strzalDzialko.at(i).podajY(), 2, al_map_rgb(255, 0, 0), 2);

						// strefa kolizji strzalu (najezdzca)
						for (int i = 0; i < strzalNajezdzcy.size(); ++i)
							al_draw_circle(strzalNajezdzcy.at(i).podajX(), strzalNajezdzcy.at(i).podajY(), 2, al_map_rgb(255, 0, 0), 2);
					}

					// wypisywanie informacji na ekranie o pozostalych pkt. zycia
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), 10, wysokosc - 46, 0, "ZYCIE: ");
					al_draw_textf(czcionkaTekst_36, al_map_rgb(255, 0, 0), 155, wysokosc - 46, 0, "%i", dzialko.podajPunktyZycia());

					// wypisywanie informacji na ekranie o pkt. zdobytych za zniszczenie najezdzcow
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), 200, wysokosc - 46, 0, "PUNKTY: ");
					al_draw_textf(czcionkaTekst_36, al_map_rgb(255, 0, 0), 380, wysokosc - 46, 0, "%i", gracz.podajPunkty());

					// aktualna fala
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc - 250, wysokosc - 46, 0, "FALA: ");
					al_draw_textf(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc - 250 + 125, wysokosc - 46, 0, "%i", gracz.podajFaleNajezdzcow());
				}
				else {
					// przykrycie ekranu (efekt przezroczystosci)
					al_draw_filled_rectangle(0, 0, szerokosc, wysokosc, al_map_rgba_f(0.9, 0.9, 0.9, 0.1));

					// napis "space invaders"
					al_draw_text(czcionkaTytul_192, al_map_rgb(0, 0, 0), szerokosc / 2 - 192, wysokosc / 2 - 192, 0, ".");

					// napis "pauza"
					al_draw_text(czcionkaTekst_48, al_map_rgb(0, 0, 0), szerokosc / 2 - 82, wysokosc / 2 + 24, 0, "PAUZA");

					// informacja o pozostalych punktach zycia
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 260, wysokosc / 2 + 120, 0, "POZOSTALE PKT. ZYCIA: ");
					al_draw_textf(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 + 236, wysokosc / 2 + 120, 0, "%i", dzialko.podajPunktyZycia());

					// informacja o zdobytych punktach
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 200, wysokosc / 2 + 165, 0, "ZDOBYTE PUNKTY: ");
					al_draw_textf(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 + 177, wysokosc / 2 + 165, 0, "%i", gracz.podajPunkty());

					// aktualna fala
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 80, wysokosc / 2 + 205, 0, "FALA: ");
					al_draw_textf(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 + 45, wysokosc / 2 + 205, 0, "%i", gracz.podajFaleNajezdzcow());
				}
			}
			else if (stanGry == PORAZKA || stanGry == WYGRANA) {

				// komunikat o zwyciestwie badz porazce w zaleznosci od wyniku
				if (stanGry == WYGRANA) {
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 100, wysokosc / 2 - 50, 0, "WYGRANA!");
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 300, wysokosc / 2, 0, "CZY CHCESZ GRAC DALEJ? (T/N)");
				}
				else {
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 100, wysokosc / 2 - 50, 0, "PORAZKA!");
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 380, wysokosc / 2, 0, "CZY CHCESZ ZAGRAC PONOWNIE? (T/N)");
				}
				
				if (grajPonownie) {
					if (stanGry == WYGRANA)
						// jezeli gracz wygra to walczy z kolejna fala
						gracz.ustawFaleNajezdzcow(gracz.podajFaleNajezdzcow() + 1);
					else
						// w.p.p. traci wszystkie punkty
						gracz.ustawPunkty(0);

					// resetowanie stanu gry: dzialko
					dzialko.ustawX(szerokosc / 2 - dzialkoSzerokosc / 2);
					dzialko.ustawY(wysokosc - 75 - dzialkoWysokosc / 2);
					dzialko.ustawPunktyZycia(3);
					
					// resetowanie stany gry: strzaly z dzialka
					strzalDzialko.clear();

					// resetowanie stanu gry: parametry najezdzcow
					koniecOkienka = false;
					czas = 50;
					czasDoWystrzalu = 50;
					kierunek = 1;
					licznik = 0;

					// resetowanie stanu gry: najezdzcy
					najezdzcy.clear();

					// resetowanie stanu gry: ponowne tworzenie najezdzcow
					for (int y = 340; y >= 100; y -= 60) {
						for (int x = 100; x <= 700; x += 60) {
							if (y <= 100)
								najezdzcy.push_back(Najezdzca(gfx_najezdzca_s01_01_, gfx_najezdzca_s01_02_, 3, 1, x - najezdzcaSzerokosc / 2, y - najezdzcaWysokosc / 2));
							else if (y <= 220 && y > 100)
								najezdzcy.push_back(Najezdzca(gfx_najezdzca_s02_01_, gfx_najezdzca_s02_02_, 2, 1, x - najezdzcaSzerokosc / 2, y - najezdzcaWysokosc / 2));
							else if (y <= 340 && y > 220)
								najezdzcy.push_back(Najezdzca(gfx_najezdzca_s03_01_, gfx_najezdzca_s03_02_, 1, 1, x - najezdzcaSzerokosc / 2, y - najezdzcaWysokosc / 2));
						}
					}

					// resetowanie stany gry: strzaly najezdzcow
					strzalNajezdzcy.clear();

					// resetowanie stanu gry: dodatkowy, wiekszy najezdzca
					wiekszyNajezdzca.clear();
					pokazWiekszegoNajezdzce = true;
					ustalonoKierunekWiekszegoNajezdzcy = false;
					kierunekWiekszegoNajezdzcy = 0;

					// resetowanie stanu gry: oslony
					oslony.clear();

					// resetowanie stanu gry: ponowne tworzenie oslon
					for (int i = 1; i <= 4; ++i)
						oslony.push_back(Oslona(gfx_oslona_00, 23, 80, 65, 192 * i + 80 * (i - 1), wysokosc - wysokosc / 3.5));

					// resetowanie stanu gry: podstawowe parametry gry
					liczbaZestrzelonychNajezdzcow = 0;
					grajPonownie = false;

					// resetowanie stanu gry: informacje diagnostyczne
					trafioneDzialko.clear();
					trafionyNajezdzca.clear();
					trafionyWiekszyNajezdzca.clear();
					trafionaOslonaDzialko.clear();
					trafionaOslonaNajezdzca.clear();

					// resetowanie stanu gry: zmiana stanu
					stanGry = GRA;
				}
			}
			else if (stanGry == POMOC) {
				// obrazki
				al_draw_bitmap(gfx_najezdzca_s03_01_, szerokosc / 2 - 125, wysokosc / 2 - 200, 0);
				al_draw_bitmap(gfx_najezdzca_s02_01_, szerokosc / 2 - 125, wysokosc / 2 + najezdzcaWysokosc + 10 - 200, 0);
				al_draw_bitmap(gfx_najezdzca_s01_01_, szerokosc / 2 - 125, wysokosc / 2 + 2 * (najezdzcaWysokosc + 10) - 200, 0);
				al_draw_bitmap(gfx_najezdzca_s00_00_, szerokosc / 2 - 125 - najezdzcaSzerokosc / 2, wysokosc / 2 + 3 * (najezdzcaWysokosc + 10) - 200, 0);

				// punkty
				al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 125, wysokosc / 2 - 200, 0, " =  10 PKT");
				al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 125, wysokosc / 2 + najezdzcaWysokosc + 10 - 200, 0, " = 20 PKT");
				al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 125, wysokosc / 2 + 2 * (najezdzcaWysokosc + 10) - 200, 0, " = 40 PKT");
				al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 125, wysokosc / 2 + 3 * (najezdzcaWysokosc + 10) - 200, 0, " = ?? PKT");

				// sterowanie
				al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 320, wysokosc / 2 + 4 * (najezdzcaWysokosc + 10) - 150, 0, "Sterowanie: strzalki");
				al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 190, wysokosc / 2 + 5 * (najezdzcaWysokosc + 10) - 150, 0, "Pauza: P");
				al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 210, wysokosc / 2 + 6 * (najezdzcaWysokosc + 10) - 150, 0, "Koniec: ESCAPE");

				// napis "POWROT DO MENU" w kolorze czerwonym (jezeli najechano na niego), czarny w.p.p.
				if (kolorCzerwonyPowrot)
					al_draw_text(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 250, wysokosc / 2 + 7 * (najezdzcaWysokosc + 10) - 100, 0, "POWROT DO MENU");
				else
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 250, wysokosc / 2 + 7 * (najezdzcaWysokosc + 10) - 100, 0, "POWROT DO MENU");
			}
			else if (stanGry == WYNIKI) {
				// napis "WYNIKI"
				al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 285, 10, 0, "10 NAJLEPSZYCH WYNIKOW:");

				// wyniki
				if (gracz.sprawdzCzyBrakWynikow())
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 - 150, wysokosc / 2 - 18, 0, "BRAK WYNIKOW.");
				else {
					for (int i = 0; i < gracz.podajLiczbeWynikow() && i <= 10; ++i) {
						int wynik = gracz.podajWynik(i); // al_draw_textf nie chcialo bezposrednio przyjac wynikow
						al_draw_textf(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 - 50, 75 + 50 * i, 0, "%i", wynik);
					}
				}

				// napis "POWROT DO MENU" w kolorze czerwonym (jezeli najechano na niego), czarny w.p.p.
				if (kolorCzerwonyPowrot)
					al_draw_text(czcionkaTekst_36, al_map_rgb(255, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 250, wysokosc / 2 + 7 * (najezdzcaWysokosc + 10) - 100, 0, "POWROT DO MENU");
				else
					al_draw_text(czcionkaTekst_36, al_map_rgb(0, 0, 0), szerokosc / 2 + najezdzcaSzerokosc + 20 - 250, wysokosc / 2 + 7 * (najezdzcaWysokosc + 10) - 100, 0, "POWROT DO MENU");
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(255, 255, 255));

			// informacje dot. liczby stworzonych obiektow
			if (diagnostyka && stanGry == GRA) {
				// system("clear");
				// system("cls");
				cout << "Liczba wiekszych najezdzcow: " << wiekszyNajezdzca.size() << endl;
				cout << "Strzaly (dzialko): " << strzalDzialko.size() << endl;
				cout << "Strzaly (najezdzcy): " << strzalNajezdzcy.size() << endl;
				cout << "Dzialko trafilo najezdzce: " << trafionyNajezdzca.size() << endl;
				cout << "Dzialko trafilo NAJEZDZCE: " << trafionyWiekszyNajezdzca.size() << endl;
				cout << "Dzialko trafilo oslone: " << trafionaOslonaDzialko.size() << endl;
				cout << "Najezdzca trafil dzialko: " << trafioneDzialko.size() << endl;
				cout << "Najezdzca trafil oslone: " << trafionaOslonaNajezdzca.size() << endl;
			}
		}
	}

	// zapis wynikow (zeby nie zasmiecac: tylko jezeli gracz zdobyl jakies pkt.)
	if (gracz.podajPunkty() > 0)
		gracz.zapiszWynik();
	gracz.zapiszWyniki();

	// kasowanie obiektow ALLEGRO
	al_destroy_font(czcionkaTekst_36);
	al_destroy_font(czcionkaTekst_48);
	al_destroy_font(czcionkaTytul_192);
	al_destroy_bitmap(gfx_dzialko_);
	al_destroy_bitmap(gfx_najezdzca_s00_00_);
	al_destroy_bitmap(gfx_najezdzca_s01_01_);
	al_destroy_bitmap(gfx_najezdzca_s01_02_);
	al_destroy_bitmap(gfx_najezdzca_s02_01_);
	al_destroy_bitmap(gfx_najezdzca_s02_02_);
	al_destroy_bitmap(gfx_najezdzca_s03_01_);
	al_destroy_bitmap(gfx_najezdzca_s03_02_);
	al_destroy_bitmap(gfx_oslona_00);
	al_destroy_bitmap(gfx_oslona_01);
	al_destroy_bitmap(gfx_oslona_02);
	al_destroy_bitmap(gfx_oslona_03);
	al_destroy_bitmap(gfx_oslona_04);
	al_destroy_event_queue(kolejkaZdarzen);
	al_destroy_timer(timer);
	al_destroy_display(okienko);
}

bool sprawdzKolizje(const ObiektBazowy * obiekt, const ObiektBazowy * strzal, int obiektSzerokosc, int obiektWysokosc) {
	// liczymy odleglosc miedzy obiektami; w przypadku obiektu (x, y) sa przeskalowane, tak aby dopasowac krawedzie kola i rysunku
	float odleglosc = sqrt(pow(strzal->podajX() - (obiekt->podajX() + obiektSzerokosc), 2) + pow(strzal->podajY() - (obiekt->podajY() + obiektWysokosc), 2));

	return (odleglosc < strzal->podajPromien() + obiekt->podajPromien());
}

bool sprawdzKolizje(const Oslona * oslona, const Strzal * strzal) {
	// strzal "wpadl" w oslone (w prostokat, ktory jest wyznaczony przez wymiary oslony)
	if (oslona->podajX() < strzal->podajX() && oslona->podajX() + oslona->podajSzerokosc() > strzal->podajX() && oslona->podajY() < strzal->podajY() && oslona->podajY() + oslona->podajWysokosc() > strzal->podajY()) {
		// z kwardatu wycinane jest kolo o srodku (x, y)
		float x = oslona->podajX() + oslona->podajSzerokosc() / 2;
		float y = oslona->podajY() + oslona->podajWysokosc() - 15;

		// odleglosc miedzy srodkiem kola a strzalem
		float odleglosc = sqrt(pow(strzal->podajX() - x, 2) + pow(strzal->podajY() - y, 2));

		if (odleglosc > oslona->podajPromienWewnetrzny() + strzal->podajPromien())
			// strzal trafil w obiekt, ale poza bialy fragment wewnatrz oslony
			return true;
		else
			return false;
	}
	return false;
}
