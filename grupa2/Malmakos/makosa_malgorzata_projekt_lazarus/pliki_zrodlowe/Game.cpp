#include "Game.h"

/**** Definicje skladnikow klasy game ****/

Game::Game() {

    //funkcje wymagane do uzycia elementow bilblioteki allegro
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_acodec_addon();

    al_install_mouse();
    al_install_keyboard();
    al_install_audio();

    //Tworze okno z naglowkiem "Lazarus game" o globalnie okreslonej szerokosci i wysokosci
    display = al_create_display(screenWidth, screenHeight);//wielkosc i dlugos w pixelach
    al_set_window_title(display, "Lazarus Game");

    create_levels(); // tworze levele
}

void Game::create_levels() {

    //definicja wektorow leveli, wektory 300 elementowe
    vector<int> l1_tab {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    vector<int> l2_tab {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    vector<int> l3_tab {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1,3,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    //tworzenie leveli
    Level level1(20, 15, l1_tab);
    Level level2(20, 15, l2_tab);
    Level level3(20, 15, l3_tab);

    //wektor wszystkich leveli, wektor ktory trzyma informacje o typie level
    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);
}

void Game::start() {
    //graficzne i dzwiekowe elementy
    al_clear_to_color(al_map_rgb(192,192,192));
    image = al_load_bitmap("Background.bmp");//tlo
    title  = al_load_bitmap("Title.gif");//tytul "lazarus'
    wall = al_load_bitmap("Wall.gif");// kwadrat sciana
    woodbox = al_load_bitmap("WoodBox.gif");// kwadrat drewniany
    lazarus = al_load_bitmap("lazarus.gif");//gracz
    button = al_load_bitmap("Button.gif"); // punkt koncowy
    stone = al_load_bitmap("StoneBox.gif"); // kwadrat kamienny
    move_sound = al_load_sample("Move.wav"); // dzwiek ruchu
    point = al_load_sample("Button.wav"); // dziek przejscia do nastepnego levelu
    song = al_load_sample("game.wav");// muzyka w tle gry
    al_draw_bitmap(image, 0, 0, NULL); // rysuje tlo
    al_draw_bitmap(title, 70, 90, NULL); // rysuje napis lazarus na tle
    al_reserve_samples(10); // definiuje liczbe instancji dzwiekowych, wykorzystywanych przez domyslny mixer

    font = al_load_font("FFF_Tusj.ttf", 40, NULL); // definicja czcionki do napisow na przyciskach na pierwszym ekranie
    al_draw_text(font, al_map_rgb(255,255,255), screenWidth*0.25, screenHeight*0.85, ALLEGRO_ALIGN_CENTRE, "START"); // rysuje napis przycisku
    al_draw_text(font, al_map_rgb(255,255,255), screenWidth*0.75, screenHeight*0.85, ALLEGRO_ALIGN_CENTRE, "QUIT"); // rysuje napis przycisku
    al_flip_display(); // posylam na ekran wszystkie elementy graficzne

    songInstance = al_create_sample_instance(song); // instancja do odtwarzania muzyki w calej grze
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP); // zapetlenie muzyki
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer()); // dolaczenie instancji do mixera domyslnego


    timer = al_create_timer(0.15); // definicja timera, potrzebna do odmierzania czasu dla spadajacych kwadratow
    event_queue=al_create_event_queue(); // definicja kolejki zdarzen

    //kolejne funkcje biblioteki allegro dla kolejki zdarzen, muzyki w tle oraz timera
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_mouse_event_source());
    al_register_event_source(event_queue,al_get_keyboard_event_source());

    al_play_sample_instance(songInstance);
    al_start_timer(timer);

 // jesli nie koniec gry, wystepuja zdarzenia
    while(!done) {
        ALLEGRO_EVENT events;

        al_wait_for_event(event_queue, &events);
        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                //co sie dzieje gdy zamkniemy okno
            done = true;
        }

        else if(events.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            //gdy klikniemy lewym przyciskiem myszy w przycisk "start"
            if(events.mouse.button == 1 && events.mouse.x >= 92 && events.mouse.x < 230 &&
                    events.mouse.y >= 414 && events.mouse.y < 444) {
                game_state = 1; // ustawiam stan gry na "w grze"
                loaded_level = 0; // zmienna pomocnicza, poczatkowy level ma miejsce w wektorach leveli 0,
                //potrzebne przy nastepnych zdarzeniach, poniewaz ruch w prawo, lub lewo nie moze dokonywac sie
                //w menu
                current_level = levels[0]; // zmienna informujaca, w ktorym levelu jestesmy
                draw_level(current_level); // rysuje pierwszy level
            }
            if(events.mouse.button == 1 && events.mouse.x >= 425 && events.mouse.x < 532 &&
                    events.mouse.y >= 414 && events.mouse.y < 444 ) {
                // jesli lewym przyciskiem myszy klikniemy na quit - wychodzimy z gry
                done = true;
            }
        }
        else if(events.type == ALLEGRO_EVENT_KEY_DOWN) {
            //zdarzenia ruch w lewo lub w prawo
            if(loaded_level != -1) {
                switch(events.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT: // jak wcisnieta zostala lewa strzalka
                   move_left(); // idz w lewo
                   break;

                case ALLEGRO_KEY_RIGHT: // jak prawa
                   move_right(); // idz w prawo
                   break;
                }
            }
        }
        else if(events.type == ALLEGRO_EVENT_TIMER) {
                // jesli timer to spadaja kwadraty
            box_act(); // funkcja odpowiadajaca za spadanie kwadratow
        }
    }
}

// funkcja rysujaca level
void Game::draw_level(Level level) {
    al_draw_bitmap(image, 0, 0, NULL); // tlo
    for(int i=0; i<level.get_height(); i++) {
        for(int j=0; j<level.get_width(); j++) {
            switch(level.get_position(j,i)) {
            case 0:
                break;
            case 1:
                draw_metal_box(j,i); // wstawia grafike sciany w miejsce o danych wspolrzednych
                break;
            case 2:
                draw_wood_box(j,i); // wstawia grafike drewnianego kwadratu w miejsce o danych wspolrzednych
                break;
            case 3:
                player_pos_x = j; // przypisuje pozycje gracza -> potrzebne m. in. przy ruchach i spadajacych kwadratach
                player_pos_y = i; // jw.

                draw_player(j,i); // wstawia grafike gracza
                break;
            case 4:
                draw_point(j,i); // wstawia grafike punktu koncowego
                break;
            case 5:
                draw_stone_box(j,i); // wstawia grafike kwadratu kamiennego
                break;
            }
        }
    }

    al_flip_display(); // posyla na ekran elementy
}

//zwraca nastepny level - wykorzystywane w ruchu gracza
Level Game::get_next_level() {
    if(loaded_level == levels.size()-1) {
            //gdy ostatni level konczy gre
            victory();
            return Level();
    } else {
        al_play_sample(point, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);// dzwiek nowego levelu
        loaded_level += 1; // zwieksza level o 1
        next_level=true; // zmienna pomocnicza, wskazuje spadajacym kwadratom kiedy maja przestac spadac
                         // i przede wszystkim szukac pozycji gracza
        return levels[loaded_level]; // zwraca nastepny level
    }

}

// funkcje rysujace kwadraty, gracza i punkt koncowy
// grafika skalowana z 40 x 40 pikseli do 32 x 32
void Game::draw_stone_box(int x, int y) {
    al_draw_scaled_bitmap(stone, 0,0, 40, 40, x*32, y*32, 32, 32, NULL);
}

void Game::draw_metal_box(int x, int y) {
    al_draw_scaled_bitmap(wall, 0,0, 40, 40, x*32, y*32, 32, 32, NULL);
}

void Game::draw_wood_box(int x, int y) {
    al_draw_scaled_bitmap(woodbox, 0,0, 40, 40, x*32, y*32, 32, 32, NULL);
}

void Game::draw_player(int x, int y) {
    al_draw_scaled_bitmap(lazarus, 0,0, 40, 40, x*32, y*32, 32, 32, NULL);
}

void Game::draw_point(int x, int y) {
    al_draw_scaled_bitmap(button, 0,0, 40, 40, x*32, y*32, 32, 32, NULL);
}

// funkcja losujaca typ kwadratu ktory ma spadac
int Game::type(){
     srand (time(NULL));
     int los = rand() % 10 + 1;

     if(los>5){
        return 2;
     }else{
        return 5;
     }
}
// funkcja, ktora odpowiada ze spadajace kwadraty
void Game::box_act() {
    if(game_state != 1) {
        // jesli stan gry nie jest "w grze"
        return; // to nie rob nic
    }

    if(box_pos_x == -1 && box_pos_y == -1) { // jesli kwadrat nie zaczal spadac
        typ = type(); // losowanie typu kwadratu i przypisanie go do zmiennej typ
        box_pos_x = player_pos_x; // przypisanie pozycji x gracza pozycji kwadratu
        box_pos_y = 0; // przypisanie 0 pozycji y kwadratu, poniewaz zaczyna spadac od samej gory
        current_level.set_position(box_pos_x,box_pos_y,typ); // wstawienie do levelu kwadratu w miejsce wyzej wyznaczone
        next_level=false; // zmienna pomocnicza, gracz nie przeszedl do nastepnego levelu
    } else if(current_level.get_position(box_pos_x,box_pos_y+1)==1 || current_level.get_position(box_pos_x,box_pos_y+1)==5) {
        // jesli nastepna pozycja jest zajeta przez 1, lub 5 to zacznij spadanie od poczatku - wazne!! gdy nastepny jest drewniany to zastepujemy go
        box_pos_x = -1;
        box_pos_y = -1;
    } else if(current_level.get_position(box_pos_x,box_pos_y+1)==3) {
        // jesli nastepny jest gracz, niestety nastepuje koniec gry
        game_over();
    } else if(current_level.get_position(box_pos_x,box_pos_y+1)==2 && typ == 2){
        // przypadek szczegolny, dwa drewniane kwadraty moga na siebie spasc, nie niszcza sie
        box_pos_x = -1;
        box_pos_y = -1;
    }else{
        if(next_level){ // jesli kwadrat nadal spada oraz gracz przeszedl wlasnie do nowego levelu
                // to kwadrat zaczyna spadac od pocztaku
            box_pos_x = -1;
            box_pos_y = -1;
        }else{// jesli spada i nie ma kwadratu przed soba
            current_level.set_position(box_pos_x,box_pos_y,0); // swoja pozycje zastepuje 0
            current_level.set_position(box_pos_x,box_pos_y+1,typ); // nastepna zostaje zastapiona wylosowanym typem
            box_pos_y += 1; // kwadrat koryguje swoja pozycje y, x nie musi bo jest stala
        }
    }

    draw_level(current_level); // przerysowanie levelu ze zmianami
}

// funkcja konczaca gre po kolizji z kwadratem
void Game::game_over() {
    game_state = 2; // ustawia stan gry na 2
    al_draw_text(font, al_map_rgb(255,255,255),320, 240, ALLEGRO_ALIGN_CENTRE, "GAME OVER");// wypisanie informacji o koncu gry
    al_flip_display();
    al_rest(10.0);
    done = true;
}
//funkcja konczaca gre po wygranej
void Game::victory() {
    game_state = 2;
    al_draw_text(font, al_map_rgb(255,255,255),320, 240, ALLEGRO_ALIGN_CENTRE, "THE END");
    al_flip_display();
    al_rest(10.0);
    done = true;
    }

// funkcja odpowiadajaca za ruch w lewo, gracz moze poruszac sie w poziomie, albo o jeden kwadrat w gore w lewo, moze
// spadac o dowolna ileosc kwadratow, uwaza na sciany i sufit, nie moze przechodzic przez nie
void Game::move_left(){
    if(player_pos_x != 0){
            for(int i=0; i<current_level.get_height();i++){
                if(current_level.get_position(player_pos_x-1, player_pos_y+i) != 0 && current_level.get_position(player_pos_x-1, player_pos_y+i)!=4 ){
                if(player_pos_y != 0){
                    if(current_level.get_position(player_pos_x-1, player_pos_y+i-1)!=0 && current_level.get_position(player_pos_x-1, player_pos_y+i-1)!=4){
                        break;
                    }else{
                       current_level.set_position(player_pos_x, player_pos_y, 0);
                           if(current_level.get_position(player_pos_x-1, player_pos_y+i-1)!=4){
                           current_level.set_position(player_pos_x-1, player_pos_y+i-1, 3);
                           //current_level.print_level();
                            break;
                               }else{
                                    current_level = get_next_level();
                                    break;
                               }
                    }
                }else{
                    current_level.set_position(player_pos_x, player_pos_y, 0);
                           if(current_level.get_position(player_pos_x-1, player_pos_y+i-1)!=4){
                           current_level.set_position(player_pos_x-1, player_pos_y+i-1, 3);
                           //current_level.print_level();
                            break;
                               }else{
                                    current_level = get_next_level();
                                    break;
                               }

                }
            }
        }
    }
        if(game_state == 1) {
            al_play_sample(move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0); // dzwiek ruchu
            draw_level(current_level); // przerysowanie levelu
        }


}

// jw. tylko w przypadku ruchu w prawo
void Game::move_right(){
    if(player_pos_x != current_level.get_width()-1){
            for(int i=0; i<current_level.get_height();i++){
                if(current_level.get_position(player_pos_x+1, player_pos_y+i) != 0 && current_level.get_position(player_pos_x+1, player_pos_y+i)!=4 ){
                if(player_pos_y != 0){
                    if(current_level.get_position(player_pos_x+1, player_pos_y+i-1)!=0 && current_level.get_position(player_pos_x+1, player_pos_y+i-1)!=4){
                        break;
                    }else{
                       current_level.set_position(player_pos_x, player_pos_y, 0);
                           if(current_level.get_position(player_pos_x+1, player_pos_y+i-1)!=4){
                           current_level.set_position(player_pos_x+1, player_pos_y+i-1, 3);
                           //current_level.print_level();
                            break;
                               }else{
                                    current_level = get_next_level();
                                    break;
                               }
                    }
                }else{
                    current_level.set_position(player_pos_x, player_pos_y, 0);
                           if(current_level.get_position(player_pos_x+1, player_pos_y+i-1)!=4){
                           current_level.set_position(player_pos_x+1, player_pos_y+i-1, 3);
                           //current_level.print_level();
                            break;
                               }else{
                                    current_level = get_next_level();
                                    break;
                               }

                }
            }
        }
    }
        if(game_state == 1) {
        al_play_sample(move_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
        draw_level(current_level);
    }


}

//destruktor gry
Game::~Game()
{

    if(timer){al_destroy_timer(timer);};
    if(font){al_destroy_font(font);};
    if(image){al_destroy_bitmap(image);};
    if(title){al_destroy_bitmap(title);};
    if(wall){al_destroy_bitmap(wall);};
    if(woodbox){al_destroy_bitmap(woodbox);};
    if(lazarus){al_destroy_bitmap(lazarus);};
    if(button){al_destroy_bitmap(button);};
    if(stone){al_destroy_bitmap(stone);};
    if(move_sound){al_destroy_sample(move_sound);};
    if(point){al_destroy_sample(point);};
    if(song){al_destroy_sample(song);};
    if(songInstance){al_destroy_sample_instance(songInstance);};
    if(event_queue){al_destroy_event_queue(event_queue);};
    if(display){al_destroy_display(display);};

}
