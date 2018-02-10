#include<iostream>
#include<string>
#include<memory>
using namespace std;

/* Command Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Command_pattern */

/* Receiver */
class MusicPlayer {
    public:
        void Play(string song){
            cout << "Play: " << song << endl;
        }

        void Stop() {
            cout << "Stop playing" << endl;
        }

        void Shuffle() {
            cout << "Shuffling ... " << endl;
        }
};

class MusicPlayerCommand {
    public:
        virtual void Execute() = 0;
        MusicPlayerCommand(MusicPlayer *pm): m{pm} {}
        MusicPlayerCommand(): m{nullptr} {}
    protected:
        MusicPlayer *m;
};

class PlayCommand: public MusicPlayerCommand {
    public:
        PlayCommand(MusicPlayer *pm, string *s): MusicPlayerCommand{pm}, song{s} {}
        void Execute() override {
            m->Play(*song);
        }
    private:
        string *song;
};

class StopCommand: public MusicPlayerCommand {
    public:
        StopCommand(MusicPlayer *pm): MusicPlayerCommand{pm} {}
        void Execute() override {
            m->Stop();
        }
};

class ShuffleCommand: public MusicPlayerCommand {
    public:
        ShuffleCommand(MusicPlayer *pm): MusicPlayerCommand{pm} {}
        void Execute() override {
            m->Shuffle();
        }
};

void CommandTestCode() {
    MusicPlayer player;
    string str{"song1"};
    unique_ptr<MusicPlayerCommand> p{make_unique<PlayCommand>(&player, &str)};
    unique_ptr<MusicPlayerCommand> s{make_unique<StopCommand>(&player)};
    unique_ptr<MusicPlayerCommand> sh{make_unique<ShuffleCommand>(&player)};
    p->Execute();
    s->Execute();
    sh->Execute();
}

int main() {
    CommandTestCode();
}
