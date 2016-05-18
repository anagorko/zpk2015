#include <MidiFile.h>
#include <Options.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fluidsynth.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const float TPS = 1000;   // ticks per second - clock resolution
const float QPS = 1;      // quarter notes per second
const float FPS = 60;     // display frames per second

const string compositions[] = {
    "scott-joplin-peacherine-rag.mid",
    "frederic-chopin-nocturne-no20.mid",
    "40-1-polonaise.mid",
    "frederic-chopin-piano-sonata-2-op35-3-funeral-march.mid"
};

string composition_filename = compositions[3];

using namespace std;

class Note
{
    int start, end;
    int tone;
    int velocity;
    int key;
    ALLEGRO_COLOR color;
    
public:
    Note() {
        start = end = tone = velocity = key = -1;
        color = al_map_rgb(255,255,255);
    }
    Note(int s, int e, int t, int v, int k)
        : start(s), end(e), tone(t), velocity(v), key(k)
    {
        color = al_map_rgb(255,255,255);
    }
    
    void setStart(int s) { start = s; }
    void setEnd(int e) { end = e; }
    void setTone(int t) { tone = t; }
    void setVelocity(int v) { velocity = v; }
    void setKey(int k) { key = k; }
    void setColor(ALLEGRO_COLOR c) { color = c; }
    
    int getStart() const { return start; }
    int getEnd() const { return end; }
    int getTone() const { return tone; }
    int getVelocity() const { return velocity; }
    int getKey() const { return key; }    
    ALLEGRO_COLOR getColor() const { return color; }
};

ostream& operator<<(ostream& os, const Note& n)
{
    return os << n.getStart() << " -- " << n.getEnd() << ": " << n.getTone() << " " << n.getVelocity() << " " << n.getKey();
}

bool operator<=(const Note& n, int t) 
{
    return n.getStart() <= t;
}

bool operator<=(int t, const Note& n)
{
    return t <= n.getEnd();
}

class Composition
{
    vector<Note> n;
    
    int lowRange, highRange;
    int tpq;
    
public:
    int getTPQ() { return tpq; }
    
    bool load(string filename) {
        MidiFile midifile;
        midifile.read(filename);
        midifile.joinTracks();
    
        tpq = midifile.getTicksPerQuarterNote();
        
        lowRange = 255; highRange = 0;
        
        int e = 0;
        int tick = 0;
    
        int start[256];
        int v[256];
    
        // Czytanie nut z pliku MIDI
        while (e < midifile[0].size()) {
        
            while (e < midifile[0].size() && midifile[0][e].tick <= tick) {
                cout << "Tick: " << tick << ". ";
                cout << "Event: " << e << ". ";
                
                if ((midifile[0][e][0] & 0xF0) == 0x90 && midifile[0][e][2] > 0) {
                    cout << " Note ON (track " << midifile[0][e].track << ") " << (int) midifile[0][e][1] << ".";

                    int note = midifile[0][e][1];
                    
                    if (note < lowRange) { lowRange = note; }
                    if (note > highRange) { highRange = note; }
                    
                    start[note] = tick;
                    v[note] = midifile[0][e][2];
                
                } else if ((midifile[0][e][0] & 0xF0) == 0x80 
                          || ((midifile[0][e][0] & 0xF0) == 0x90 && midifile[0][e][2] == 0)) {
                    cout << " Note OFF " << (int) midifile[0][e][1] << ".";
            
                    Note note(start[midifile[0][e][1]], tick, midifile[0][e][1], v[midifile[0][e][1]], -1);
                    note.setKey(0);
                    
                    n.push_back(note);
                } else {
                    cout << " Event type " << hex << (int) midifile[0][e][0] << " " << (int) midifile[0][e][1] << " " << (int) midifile[0][e][2] << dec;
                }
                cout << endl;
                e++;
            }
        
            tick++;
        }
        
        int lasttick[4] = { 0, 0, 0, 0 };
        
        // randomly assign note keys
        for (Note& note: n) {            
            for (int i = 0; i < 4; i++) {
                if (note.getStart() > lasttick[i] + 50 && note.getEnd() - note.getStart() > 30) {
                    if (rand() % 100 <= 25) {
                        lasttick[i] = note.getEnd() + (note.getEnd() - note.getStart());
                        note.setKey(i+1);
                    }
                }
            }
        }
        
        return n.size() > 0;
    }
    
    int getLowRange() {
        return lowRange;
    }
    
    int getHighRange() {
        return highRange;
    }

    vector<Note>& getNotes() {
        return n;
    }
};

class Piano
{
    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_player_t* player;
    fluid_audio_driver_t* adriver;

    string soundfont, driver;
    
public:
    Piano(string _soundfont = "fluidr3.sf2", string _driver = "portaudio")
        : soundfont(_soundfont), driver(_driver)
    {
        settings = NULL;
        synth = NULL;
        player = NULL;
        adriver = NULL;
    }

    ~Piano() {
        if (adriver) { delete_fluid_audio_driver(adriver); }
        if (player) { delete_fluid_player(player); }
        if (synth) { delete_fluid_synth(synth); }
        if (settings) { delete_fluid_settings(settings); }
    }
        
    bool init() {
        settings = new_fluid_settings();
        synth = new_fluid_synth(settings);
        player = new_fluid_player(synth);
        fluid_settings_setstr(settings, "audio.driver", driver.c_str());
        adriver = new_fluid_audio_driver(settings, synth);

        if (fluid_synth_sfload(synth, soundfont.c_str(), 1) == FLUID_FAILED) {
            return false;
        }
        
        return true;
    }
    
    void play(const Note& n) {
        fluid_synth_noteon(synth, 0, n.getTone(), n.getVelocity());
    }
    
    void stop(const Note& n) {
        fluid_synth_noteoff(synth, 0, n.getTone());                
    }
};

class Display
{
    ALLEGRO_DISPLAY     *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER       *timer = NULL;
    
    int width, height;
    int lowRange, highRange;
    
public:
    Display()
    {
        lowRange = 0;
        highRange = 255;
    }
    
    ~Display()
    {
        if (display) { al_destroy_display(display); }
    }
    
    bool init(int w = 1024, int h = 600) {
        width = w;
        height = h;
        
        if (!al_init() || !al_init_primitives_addon() || !al_install_keyboard()) {
             return false;
        }
        display = al_create_display(width, height);

        event_queue = al_create_event_queue();

        if (!event_queue) { return false; }
    
        timer = al_create_timer(1.0/TPS);

        if (!timer) { return false; }
    
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_timer_event_source(timer)); 
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_start_timer(timer);
        
        clear(); flip();
        
        return true;
    }

    void setRange(int l, int h) { lowRange = l; highRange = h; }
    
    void drawNote(const Note& n, int tick)
    {
        float noteWidth = (float) width / (float) (highRange - lowRange + 1);
        
        float relTone = n.getTone() - lowRange;
        al_draw_filled_rectangle(0.05 * noteWidth + relTone * noteWidth, n.getStart() - tick, (relTone + 0.95) * noteWidth, n.getEnd() - tick, n.getColor());
    }
    
    void waitForEvent(ALLEGRO_EVENT &ev) {
        al_wait_for_event(event_queue, &ev);
    }
    
    bool eventQueueEmpty() {
        return al_is_event_queue_empty(event_queue);
    }
    
    void clear() {
        al_clear_to_color(al_map_rgb(0,0,0));
    }
    
    void flip() {
        al_flip_display();
    }
    
    int getWidth() { return width; }
    int getHeight() { return height; }
};

class Game
{
    int state;

protected:
    Composition c;
    int tick;
    
    virtual void evaluateGameState() {}
    
public:
    static const int PreGame = 1;
    static const int InProgress = 2;
    static const int GameWon = 3;
    static const int GameLost = 4;
    
    Game() {
        setGameState(PreGame);
        tick = 0;
    }

    void init(Composition _c) {
        c = _c;
        setGameState(InProgress);
        tick = 0;
    }

    int getGameState() { return state; }
    void setGameState(int s) { state = s; }
    
    void nextBeat() { 
        tick++; this -> evaluateGameState();
    }
    void setBeat(int t) { tick = t; }
    int getBeat() { return tick; }
            
    virtual void keyDown(int) {}
    virtual void mouseClick(int, int) {}

    virtual void draw(Display&) {}
    
    virtual void play(Piano& p) {
        bool play = false;
        for (Note n: c.getNotes()) {
            if (n.getStart() >= tick || n.getEnd() >= tick) {
                play = true;
            }
            if (n.getStart() == tick) {
                cout << n << endl;
                p.play(n);
            }
            if (n.getEnd() == tick) {
                p.stop(n);
            }
        }
        if (!play) {
            state = GameWon;
        }
    }
};

class MusicalBox : public Game
{    
public:
    virtual void draw(Display &d) {
        d.setRange(c.getLowRange(), c.getHighRange());
        
        for (Note n: c.getNotes()) {
            if (n.getStart() <= tick) {
                n.setColor(al_map_rgb(0,0,255));
            } else {
                n.setColor(al_map_rgb(255,255,255));
            }
            d.drawNote(n, tick);
        }
    }
};

class PianoTiles : public Game
{
    void evaluateGameState() {
        // check if there are unplayed notes that moved out of the time frame
        for (Note& n: c.getNotes()) {
            if (n.getEnd() <= tick - 20 && n.getKey() > 0) {
                n.setKey(-n.getKey()); n.setColor(al_map_rgb(100, 0, 0)); break;
            }
        }
    }

public:
    virtual void draw(Display &d) {
        d.setRange(1, 4);
        
        al_draw_line(0,d.getHeight()/2,d.getWidth(),d.getHeight()/2, al_map_rgb(50,50,50),1);
        
        for (Note n: c.getNotes()) {
            if (n.getKey() >= 1 && n.getKey() <= 4) {
                // not played note
                Note p = n;
                p.setTone(p.getKey());
                d.drawNote(p, tick - 300);
            }
            if (n.getKey() >= -4 && n.getKey() <= -1) {
                // a played note
                Note p = n;
                p.setTone(-p.getKey());

                d.drawNote(p, tick - 300);
            }
        }
    }

    virtual void keyDown(int k) 
    {
        // find displayed notes with specified key and set their key to negative value
        // if no such note exists, player lost
        
        bool foundNote = false;
        
        for (Note& n: c.getNotes()) {
            if (n.getStart() <= tick + 20 && n.getEnd() >= tick - 20 && n.getKey() == k) {
                n.setKey(-k); n.setColor(al_map_rgb(0,0,100));
                foundNote = true; break;
            } else if (n.getStart() <= tick + 300 && n.getEnd() >= tick - 300 && n.getKey() == k) {
                n.setKey(-k); n.setColor(al_map_rgb(100, 0, 0)); break;
            }
        }        
        
        if (!foundNote) {
            // setGameState(GameLost);
            cout << "LOST" << endl;
        }
    }

};

int main(int argc, char** argv) 
{    
    srand(time(NULL));
    
    Piano p;   
 
    if (!p.init()) {
        cout << "Piano initialization failed." << endl; return -1;
    }

    Display d;
    
    int w = argc == 1 ? 400 : 1024;
    
    if (!d.init(w)) {
        cout << "Display initialization failed." << endl; return -1;
    }
    
    Composition c;
    
    if (!c.load(composition_filename)) {
        cout << "Failed to load midi file." << endl; return -1;
    }
       
    Game* g;
    
    if (argc > 1 && string(argv[1]) == "-b") {
        g = new MusicalBox();
    } else {
        g = new PianoTiles();
    }
    
    g -> init(c);
    g -> setBeat(-100);
    
    float nextFrameTime = 0.0;
    float nextBeatTime = 0.0;
    float time = 0.0;

    bool newFrame = true;
    bool newBeat = true;
    
    while (g -> getGameState() == Game::InProgress) {
        ALLEGRO_EVENT ev;
        d.waitForEvent(ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER) {
            time += 1.0 / TPS;
            
            if (time >= nextFrameTime) {
                nextFrameTime += 1.0 / FPS;
                newFrame = true;
            }
            if (time >= nextBeatTime) {
                nextBeatTime += 1.0 / (QPS * c.getTPQ());
                newBeat = true;
                
                g -> nextBeat();
            }
        }
        
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                break;
            }
            
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_A: g -> keyDown(1); break;
            case ALLEGRO_KEY_S: g -> keyDown(2); break;
            case ALLEGRO_KEY_D: g -> keyDown(3); break;
            case ALLEGRO_KEY_F: g -> keyDown(4); break;
            }
        }
        
        if (newBeat && d.eventQueueEmpty()) {
            newBeat = false;
            
            g -> play(p);
        }
        
        if (newFrame && d.eventQueueEmpty()) {
            newFrame = false;

            d.clear();            
            g -> draw(d);
            d.flip();
        }
    }
    

    return 0;
}
