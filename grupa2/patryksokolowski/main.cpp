#include<iostream>
#include<vector>
#include<math.h>
#include <conio.h>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace std;

#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5\allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

// STAŁE ODPOWIADAJĄCE ZA WIELKOŚĆ EKRANU GRY ORAZ ILOŚĆ KLATEK NA SEKUNDĘ

const int screen_w = 800;
const int screen_h = 600;
const float FPS = 60.0;

// KLASA VEKTOR DO PRZESTAWIENIA POZYZJI OBIEKTÓW NA PŁASZCZYŹNIE

class Vect
{
    float x, y;

public:
    Vect() : Vect(0.0, 0.0) {
    }
    Vect(float _x, float _y) {
        setX(_x);
        setY(_y);
    }

    float distanceTo(Vect p)
    {
        float dx = x - p.x;
        float dy = y - p.y;

        return sqrt(dx*dx + dy*dy);
    }

    float getX() const { return x; }
    float getY() const { return y; }

    void setX(float _x) { x = _x; }
    void setY(float _y) { y = _y; }

    Vect& operator*=(float f) {
        x *= f; y *= f; return *this;
    }

    Vect& operator+=(Vect v) {
        x += v.x; y += v.y; return *this;
    }
};

Vect operator*(Vect v, float f)
{
    v *= f;
    return v;
}
Vect operator+(Vect v1, Vect v2)
{
    v1 += v2;
    return v1;
}

// KLASA FLYING - DZIEDZICZYĆ BĘDĄ Z NIEJ KLASY DLA WSZYSTKICH OBIEKTÓW LATAJĄCYCH
// ZAWIERA METODY WPÓLNE DLA WSZYSTKICH OBIEKTÓW WYŚWITLKANYCH NA EKRANIE
// PRĘDKOŚĆ, KĄT OBORTU, POŁOŻENIE, ORAZ KLASY ODPOWIADAJĄCE
// ZA NARYSOWANIE OBIEKTÓW NA EKRANIE GRY

class Flying
{
protected:
    ALLEGRO_BITMAP* bitmap;

    Vect p, v;
    float a, r;

public:
    Flying(){};
    Flying(ALLEGRO_BITMAP* bm)
    {
        bitmap = bm;
    }

    Vect getPosition() const { return p; }
    void setPosition(const Vect _p) { p = _p; }

    Vect getVelocity() const { return v; }
    void setVelocity(Vect _v) { v = _v; }

    float getRotation() const { return r; }
    void setRotation(float _r) { r = _r; }

    float getAngle() const { return a; }
    void setAngle(float _a) { a = _a; }

    virtual void move(float time) {
        Vect p = getPosition();
        p += getVelocity() * time;
        if (p.getX() > screen_w) { p.setX(p.getX() - screen_w); }
        if (p.getY() > screen_h) { p.setY(p.getY() - screen_h); }
        if (p.getX() < 0) { p.setX(p.getX() + screen_w); }
        if (p.getY() < 0) { p.setY(p.getY() + screen_h); }
        setPosition(p);

        float a = getAngle();
        a += getRotation() * time;
        setAngle(a);
    }

    bool collidesWith(Flying* f) const
    {
        return getPosition().distanceTo(f -> getPosition()) <
                (diameter() + f -> diameter()) / 2;
    }

    virtual float diameter() const { return 0; }
    virtual ALLEGRO_BITMAP* getBitmap() const { return bitmap; }
    void draw(){
            al_draw_rotated_bitmap(getBitmap(),
                                   al_get_bitmap_width(getBitmap()) / 2,
                                   al_get_bitmap_height(getBitmap()) / 2,
                                   getPosition().getX(),
                                   getPosition().getY(),
                                   getAngle(),
                                   0);

            al_draw_rotated_bitmap(getBitmap(),
                                   al_get_bitmap_width(getBitmap()) / 2,
                                   al_get_bitmap_height(getBitmap()) / 2,
                                   getPosition().getX() + screen_w,
                                   getPosition().getY(),
                                   getAngle(),
                                   0);

            al_draw_rotated_bitmap(getBitmap(),
                                   al_get_bitmap_width(getBitmap()) / 2,
                                   al_get_bitmap_height(getBitmap()) / 2,
                                   getPosition().getX() - screen_w,
                                   getPosition().getY(),
                                   getAngle(),
                                   0);

            al_draw_rotated_bitmap(getBitmap(),
                                   al_get_bitmap_width(getBitmap()) / 2,
                                   al_get_bitmap_height(getBitmap()) / 2,
                                   getPosition().getX(),
                                   getPosition().getY() + screen_h,
                                   getAngle(),
                                   0);

            al_draw_rotated_bitmap(getBitmap(),
                                   al_get_bitmap_width(getBitmap()) / 2,
                                   al_get_bitmap_height(getBitmap()) / 2,
                                   getPosition().getX(),
                                   getPosition().getY() - screen_h,
                                   getAngle(),
                                   0);
    }
};


// KLASA DO PRZEDSTAWIENIA OBEIKTOW KONTROLOWANYCH PRZEZ UZYTKOWNIKA
class Controlled : public Flying
{
    bool left;
    bool right;
    bool forw;

public:
    Controlled()
    {
        left = false; right = false; forw = false;
    }

    void turnLeft(bool l) { left = l; }
    void turnRight(bool r) { right = r; }
    void forward(bool f) { forw = f; }

    virtual void move(float time) {
        if (left) {
            setRotation(getRotation() - 0.1);
        }
        if (right) {
            setRotation(getRotation() + 0.1);
        }
        if (forw) {
            setVelocity(getVelocity() + Vect(2*cos(getAngle()), 2*sin(getAngle())));
        }
        if (!left and !right) {
            setRotation(getRotation()/1.05);
        }
        if (!forw){
            setVelocity(getVelocity()*0.95);
        }
        Flying::move(time);
    }
};
// KLASA STATKU KOSMPICZNEGO
class Spaceship : public Controlled
{
public:
    Spaceship(){};
    Spaceship(ALLEGRO_BITMAP* bm)
    {
        bitmap = bm;
    }

    virtual float diameter() const { return 48; }
};


// NAJWIĘKSZA ASTEROIDA

class Asteroid : public Flying
{
protected:
    bool big;
    bool biggest;
public:
    Asteroid(){};
    Asteroid(ALLEGRO_BITMAP* bm)
    {
        bitmap = bm;
        big = true;
        biggest = true;
    }

    virtual float diameter() const { return 64; }
    bool isBig(){
        return big;
    }
    bool isBiggest(){
        return biggest;
    }
};

// MNIEJSZA ASTEROIDA
class SmallAsteroid: public Asteroid
{
    public:
        SmallAsteroid(){};
        SmallAsteroid(ALLEGRO_BITMAP* bm)
    {
        bitmap = bm;
        big = true;
        biggest = false;
    }
    virtual float diameter() const { return 32; }
};

// NAJMNIEJSZA ASTEROIDA

class SmallestAsteroid: public Asteroid
{
    public:
        SmallestAsteroid(){};
        SmallestAsteroid(ALLEGRO_BITMAP* bm)
    {
        bitmap = bm;
        big = false;
        biggest = false;
    }

    virtual float diameter() const { return 24; }
};

// KLASA KULI

class Bullet : public Flying
{
    float fireTime;
public:
    Bullet(){};
    Bullet(ALLEGRO_BITMAP* bm)
    {
        bitmap = bm;
    }

    Bullet(float t,ALLEGRO_BITMAP* bm)
    {
        bitmap = bm;
        fireTime = t;
    }
    float getFireTime(){
       return fireTime;
    }
    virtual float diameter() const { return 5; }
};

class Game
{
    string state;
public:
    Game(){
        state = "start";
    }
    string getState(){
        return state;
    }
    void setState(string s){
        state = s;
    }
};


// KLASA ODPOWIADAJACA ZA NAJWIEKSZE WYNIKI W GRZE
class HighScores
{
    string filename;
    vector<int> scores;
    vector<string> names;
public:
    HighScores(string x){
        filename=x;
        scores.resize(5);
        names.resize(5);
    }
    HighScores(){
        HighScores("scores");
    }
    bool isTop(int i){
        if (i>scores[4]) return true;
        return false;
    }
    bool saveScore(int sc,ALLEGRO_USTR* s){
        if(sc<scores[4]) return false;
        for (int i=0;i<5;i++){
            if(sc>scores[i]){
                scores.insert(scores.begin()+i,sc);
                names.insert(names.begin()+i,al_cstr(s));
                break;
            }
        }
        scores.resize(5);
        names.resize(5);
    }
    void saveFile(){
        ofstream out(filename+".txt");
        for (int i=0;i<5;i++){
            out << names[i] << " " << scores[i] << endl;
        }
        out.close();
    }
    void loadFile(){
        ifstream in(filename+".txt");
        for (int i=0;i<5;i++){
            in >> names[i] >> scores[i];
        }
        in.close();
    }
    string getName(int i){
        return names[i];
    }
    int getScore(int i){
        return scores[i];
    }
};
// WEKTORY ZAWIERAJACE OBIEKTY OBECNE W GRZE
vector<Asteroid*> asteroids;
vector<Spaceship*> spaceship;
vector<Bullet*> bullets;

// FUNKCJA TWORZACA ASTEROIDE
void create_asteroid(ALLEGRO_BITMAP* bm)
{
    Asteroid *a = new Asteroid(bm);

    do {
        a -> setPosition(Vect(rand() % screen_w, rand() % screen_h));
    } while (a -> getPosition().distanceTo(spaceship[0] -> getPosition()) < 200);

    a -> setAngle(rand());
    a -> setRotation(((float) (rand() % 200) - 100) / 100.0);
    a -> setVelocity(Vect((rand() % 60) - 30, (rand() % 60) - 30));

    asteroids.push_back(a);
}

// FUNKCJA TWORZACA MNIEJSZA ASTEROIDE
void create_small_asteroid(Asteroid* x,ALLEGRO_BITMAP* bm)
{
    for (int m=0;m<3;m++){
    SmallAsteroid *a = new SmallAsteroid(bm);
    a -> setPosition(x -> getPosition());
    a -> setAngle(rand());
    a -> setRotation(((float) (rand() % 200) - 100) / 100.0);
    a -> setVelocity(Vect((rand() % 60) - 30, (rand() % 60) - 30));
    asteroids.push_back(a);
    }
}
// FUNKCJA TWORZACA NAJMNIEJSZA ASTEROIDE
void create_smallest_asteroid(Asteroid* x,ALLEGRO_BITMAP* bm)
{
    for (int m=0;m<3;m++){
    SmallestAsteroid *a = new SmallestAsteroid(bm);
    a -> setPosition(x -> getPosition());
    a -> setAngle(rand());
    a -> setRotation(((float) (rand() % 200) - 100) / 100.0);
    a -> setVelocity(Vect((rand() % 60) - 30, (rand() % 60) - 30));
    asteroids.push_back(a);
    }
}

// FUNKCJA WYSTRZELOWUJACA KULE
void fire(Spaceship s, float t,ALLEGRO_SAMPLE* sound,ALLEGRO_BITMAP* bm)
{
    Bullet *b = new Bullet(t,bm);
    b -> setPosition(s.getPosition());
    b -> setAngle(s.getAngle());
    b -> setRotation(0);
    b -> setVelocity(Vect(cos(s.getAngle())*350, sin(s.getAngle())*350));
    bullets.push_back(b);
    al_play_sample(sound,1.0,0.0,3.0,ALLEGRO_PLAYMODE_ONCE,0);
}

// FUNKCJA POKAZUJACA NAJWIEKSZE WYNIKI
void showScores(ALLEGRO_FONT* h,ALLEGRO_FONT* hs,HighScores s,ALLEGRO_BITMAP* t){
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(t,0,0,0);
        al_draw_text(h,al_map_rgb(255,255,255),screen_w/5,screen_h/5,ALLEGRO_ALIGN_CENTER,"High Scores");
        for (int i=0;i<5;i++){
            al_draw_textf(hs,al_map_rgb(255,255,255),screen_w/3,screen_h/3+50*i,ALLEGRO_ALIGN_CENTER,"            %i",s.getScore(i));
            al_draw_text(hs,al_map_rgb(255,255,255),screen_w/3,screen_h/3+50*i,ALLEGRO_ALIGN_CENTER,s.getName(i).c_str());
        }
        al_draw_text(h,al_map_rgb(255,255,255),0,screen_h-100,ALLEGRO_ALIGN_LEFT,"Click E to go back to start menu");
        al_flip_display();
}


int main(int, char**)
{
    if (!al_init() || !al_install_keyboard() || !al_init_image_addon()) {
        cout << "B³¹d inicjalizacji." << endl;
        return 1;
    }
// WCZYTANIE EKRANU TIMERA, KOLEJKI ZDARZEN I BITMAP DO TLA
    ALLEGRO_DISPLAY *display = al_create_display(screen_w, screen_h);
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_BITMAP *tlo = al_load_bitmap("galaxy.jpg");
    ALLEGRO_BITMAP *start = al_load_bitmap("galaxy2.jpg");
    ALLEGRO_BITMAP *lost = al_load_bitmap("final.jpg");
// WCZYTANIE BITMAP OBIEKTOW LATAJACYCH
    ALLEGRO_BITMAP *bm[5];
    bm[0] = al_load_bitmap("asteroid.png");
    bm[1] = al_load_bitmap("spaceship.png");
    bm[2] = al_load_bitmap("asteroidBIG.png");
    bm[3] = al_load_bitmap("asteroidSMALL.png");
    bm[4] = al_load_bitmap("bullet.png");
// SPRAWDZANIE CZY INICJALIZACJA SIE POWIODLA
    if (display == NULL || timer == NULL || event_queue == NULL) {
        cout << "B³¹d inicjalizacji." << endl;
        return 2;
    }
// INICJALIZACJE ALLEGRO
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
// WCZYTANIE CZCIONEK DO WYPISYWANIA NAPISOW
    ALLEGRO_FONT *font = al_load_font("starwars.ttf", 12, 0);
    ALLEGRO_FONT *hs_head = al_load_font("starwars.ttf", 42, 0);
    ALLEGRO_FONT *hs = al_load_font("starwars.ttf", 24, 0);
// WCZYTANIE DZWIEKOW WYTRZELENIA ORAZ ROZBICIA ASTEROIDY
    ALLEGRO_SAMPLE *shot = al_load_sample("shot.wav");
    ALLEGRO_SAMPLE *ex = al_load_sample("exploasion.wav");
    al_reserve_samples(10);
// ZMIENNE DO WYPISYWANIA NICKU PO GRZE
    ALLEGRO_USTR* nick = al_ustr_new("");
    int size_n = (int)al_ustr_size(nick);
// WYCZYSZCZENIE EKRANU I WCZYTANIE PIERWSZEGO TLA
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(start,0,0,0);
    al_flip_display();
// STWORZENIE GRY I TABELICY WYNIKOW ORAZ WCZYTANIE TABLICY Z
    Game* g = new Game();
    HighScores* h = new HighScores("scores");
    h -> loadFile();
// ZMIENNA DO PRZECHWYTYWANIE EVENTOW
    ALLEGRO_EVENT e;
// ZMIENNA ODLICZAJACA CZAS
    float time = 0.0;
    float time2= 0.0;
// ZMIENNA ODLICZAJACA WYNIK
    int score = 0;
// STWORZENIE STATKU
     Spaceship *s = new Spaceship(bm[1]);
                    s -> setPosition(Vect(screen_w / 2, screen_h / 2));
                    s -> setAngle(0);
                    s -> setRotation(0);
                    s -> setVelocity(Vect(0, 0));

                    spaceship.push_back(s);
// KOLEJKA ZDARZEN
    while (g ->getState()=="start"){
    al_ustr_truncate(nick,0);
    size_n = 0;
    al_wait_for_event(event_queue, &e);
    bool draw = true;
    if (e.type==ALLEGRO_EVENT_KEY_DOWN){
        switch(e.keyboard.keycode){
        case ALLEGRO_KEY_S: // START GRY
            g -> setState("go");
            // WYCZYSZCZENIE WYNIKU, CZASU ORAZ WEKTOROW Z ASTEROIDAMI I KULAMI I PRZESUNIECIE STATKU NA SRODEK
                    score = 0;
                    time = 0.0;
                    time2= 0.0;
                    al_start_timer(timer);
                    for (int i =0;i<asteroids.size();i++){
                        delete asteroids[i];
                    }
                    for (int i =0;i<bullets.size();i++){
                        delete bullets[i];
                    }
                    asteroids.clear();
                    bullets.clear();
                    s -> setPosition(Vect(screen_w / 2, screen_h / 2));
                    s -> setAngle(0);
                    s -> setRotation(0);
                    s -> setVelocity(Vect(0, 0));
                    s -> forward(false);
                    s -> turnLeft(false);
                    s -> turnRight(false);
            // STWORZENIE ASTEROID
                    for (int i = 0; i < 8; i++) {
                        create_asteroid(bm[2]);
                    }
            // PETLA GRY
                    while (g ->getState()=="go")
                    {
                        // process events
                        ALLEGRO_EVENT ev;
                        al_wait_for_event(event_queue, &ev);

                        // PRZSUNIECIE OBIEKTOW
                        if(ev.type == ALLEGRO_EVENT_TIMER) {
                            draw = true;
                            // move objects
                            for (Spaceship* f: spaceship) {
                                f -> move(1.0 / FPS);
                            }
                            for (Asteroid* f: asteroids) {
                                f -> move(1.0 / FPS);
                            }
                            for (Bullet* f: bullets) {
                                f -> move(1.0 / FPS);
                            }
                            time = time + 1.0 / FPS;
                            time2 = time2 + 1.0 / FPS;
                            for (int i=0;i<bullets.size();i++){
                                if(bullets[i] -> getFireTime()+1.5<time){
                                    delete bullets[i];
                                    bullets.erase(bullets.begin()+i);
                                }
                            }
                            if (time2>10.0) {
                                time2 = 0.0;
                                create_asteroid(bm[2]);
                            }
                        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                            break;
                        } else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { // PRZECHWYCENIE STEROWANIA STATKU ORAZ WYSTRZELIWANIE KULEK
                             switch(ev.keyboard.keycode) {
                                 case ALLEGRO_KEY_UP:
                                    s -> forward(true);
                                    break;
                                 case ALLEGRO_KEY_LEFT:
                                    s -> turnLeft(true);
                                    break;
                                 case ALLEGRO_KEY_RIGHT:
                                    s -> turnRight(true);
                                    break;
                                 case ALLEGRO_KEY_SPACE:
                                    fire(*s,time,shot,bm[4]);
                                    break;
                            }
                        } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
                             switch(ev.keyboard.keycode) {
                                 case ALLEGRO_KEY_UP:
                                    s -> forward(false);
                                    break;
                                 case ALLEGRO_KEY_LEFT:
                                    s -> turnLeft(false);
                                    break;
                                 case ALLEGRO_KEY_RIGHT:
                                    s -> turnRight(false);
                                    break;
                            }
                        }

                        // SPRAWDZANIE KOLIZJI KUL Z ASTEROIDAMI
                        for (int i=0;i<asteroids.size();i++)
                        {
                            for (int j=0;j<bullets.size();j++){
                                if (asteroids[i] -> collidesWith(bullets[j])) {
                                    delete bullets[j];
                                    bullets.erase(bullets.begin()+j);
                                    al_play_sample(ex,1.0,0.0,2.0,ALLEGRO_PLAYMODE_ONCE,0);
                                    if (asteroids[i] -> isBig()){
                                        if (asteroids[i] -> isBiggest()) create_small_asteroid(asteroids[i],bm[0]);
                                        else create_smallest_asteroid(asteroids[i],bm[3]);
                                        delete asteroids[i];
                                        score += 10;
                                        asteroids.erase(asteroids.begin()+i);
                                        al_play_sample(ex,1.0,0.0,2.0,ALLEGRO_PLAYMODE_ONCE,0);
                                    }
                                    else {
                                        delete asteroids[i];
                                        score += 10;
                                        asteroids.erase(asteroids.begin()+i);
                                        al_play_sample(ex,1.0,0.0,2.0,ALLEGRO_PLAYMODE_ONCE,0);
                                    }
                                }
                            }
                        }
                        // SPRAWDZANIE KOLIZJI STATKU Z ASTEROIDAMI
                        int coll=0;
                        for (int i=0;i<asteroids.size();i++){
                            if(asteroids[i] -> collidesWith(s)) coll++;
                        }
                        if (coll > 0) { g -> setState("lost");}

                        // RYSOWANIE OBIEKTOW
                        if (draw && al_is_event_queue_empty(event_queue)) {
                            al_clear_to_color(al_map_rgb(0,0,0));
                            al_draw_bitmap(tlo,0,0,0);
                            for (Spaceship* f: spaceship) {
                                f -> draw();
                            }
                            for (Asteroid* f: asteroids) {
                                f -> draw();
                            }
                            for (Bullet* f: bullets) {
                                f -> draw();
                            }
                            al_draw_textf(font,al_map_rgb(255,255,255),screen_h/10,screen_w/10,ALLEGRO_ALIGN_CENTER,"SCORE: %i",score);
                            al_flip_display();
                            draw = false;
                        }
                    };
                    // PETLA DLA PRZEKRANEJ GRY
                    while (g -> getState()=="lost"){
                            al_wait_for_event(event_queue, &e);
                            // SPRAWDZANIE CZY WYNIK MIESCI SIE W TOP 5
                            if(h -> isTop(score)){
                                while(size_n<3){
                                    al_wait_for_event(event_queue, &e);
                                    if (e.type==ALLEGRO_EVENT_KEY_CHAR){
                                            if(e.keyboard.unichar >= 32){
                                                size_n += al_ustr_append_chr(nick, e.keyboard.unichar);
                                            }
                                            else if(e.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
                                                if(al_ustr_prev(nick, &size_n))
                                                al_ustr_truncate(nick, size_n);
                                            }
                                    }
                                al_clear_to_color(al_map_rgb(0,0,0));
                                al_draw_bitmap(lost,0,0,0);
                                al_draw_textf(hs_head,al_map_rgb(255,255,255),screen_w/3,screen_h/3,ALLEGRO_ALIGN_CENTER,"Your score: %i",score);
                                al_draw_textf(hs,al_map_rgb(255,255,255),screen_w/3,screen_h/3+35,ALLEGRO_ALIGN_CENTER,"Please enter your 3 character nickname:",score);
                                al_draw_ustr(hs,al_map_rgb(255,255,255),screen_w-150,screen_h/3+35,ALLEGRO_ALIGN_CENTER,nick);
                                al_draw_text(hs_head,al_map_rgb(255,255,255),20,screen_h-40,ALLEGRO_ALIGN_LEFT,"[E]xit");
                                al_flip_display();
                                if (size_n==3){
                                    h -> saveScore(score,nick);
                                    h -> saveFile();
                                }
                                }
                            }
                            else { // TLO PO PRZEGRANEJ GRZE JESLI WYNIK NIE MIESCI SIE W TOP 5
                                al_clear_to_color(al_map_rgb(0,0,0));
                                al_draw_bitmap(lost,0,0,0);
                                al_draw_textf(hs_head,al_map_rgb(255,255,255),screen_w/3,screen_h/3,ALLEGRO_ALIGN_CENTER,"Your score: %i",score);
                                al_draw_textf(hs,al_map_rgb(255,255,255),screen_w/3,screen_h/3+35,ALLEGRO_ALIGN_CENTER,"It was too low to get into TOP 5",score);
                                al_draw_text(hs_head,al_map_rgb(255,255,255),20,screen_h-40,ALLEGRO_ALIGN_LEFT,"[E]xit");
                                al_flip_display();
                            }
                        if (e.keyboard.keycode==ALLEGRO_KEY_E){ // PRZECHODZENIE SPOWROTEM DO EKRANU STARTOWEGO
                            g -> setState("start");
                            al_draw_bitmap(start,0,0,0);
                            al_flip_display();
                        }
                    }

            break;
        case ALLEGRO_KEY_T:// EKRAN NAJLEPSZYCH WYNIKOW W HISTORII
            g -> setState("scores");
            showScores(hs_head,hs,*h,tlo);
            while (g ->getState()=="scores"){
            al_wait_for_event(event_queue, &e);
            if (e.keyboard.keycode==ALLEGRO_KEY_E){
                g -> setState("start");
                al_draw_bitmap(start,0,0,0);
                al_flip_display();
            }
            }
            break;
        case ALLEGRO_KEY_E:
            // WYJSCIE Z GRY
            g -> setState("quit");
            return 0;
            break;
        }
    }
    }
    return 0;
delete s;
al_destroy_timer(timer);
al_destroy_display(display);
al_destroy_bitmap(tlo);
al_destroy_bitmap(start);
al_destroy_bitmap(lost);
al_destroy_bitmap(bm[0]);
al_destroy_bitmap(bm[1]);
al_destroy_bitmap(bm[2]);
al_destroy_bitmap(bm[3]);
al_destroy_bitmap(bm[4]);
al_destroy_font(font);
al_destroy_font(hs_head);
al_destroy_font(hs);
al_destroy_sample(shot);
al_destroy_sample(ex);
delete g;
delete h;
al_ustr_free(nick);
}
