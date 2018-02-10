#include<iostream>
#include<memory>
#include<string>

using namespace std;

/* Chain of Responsibility Pattern
 * The code is referenced from
 * http://www.bogotobogo.com/DesignPatterns/chain_of_responsibility.php */

struct SoundTrack {
    string soundData;
    SoundTrack(string s): soundData{s} {}
};

class ProcessingStage {
    public:
        ProcessingStage(): next{nullptr} {}
        void Process(SoundTrack &t) {
            /* Not every stage needs processing in the definition
             * of this pattern, may have mechanism to determine
             * the actual stage for the responsibility */
            MyProcessStage(t);
            if (next)
                next->Process(t);
        }
        void SetNextStage(ProcessingStage &s) {
            next = &s;
        }
    protected:
        virtual void MyProcessStage(SoundTrack &t) = 0;
    private:
        ProcessingStage *next;
};

class Compressor: public ProcessingStage {
    protected:
        void MyProcessStage(SoundTrack &t) override {
            t.soundData.insert(0,"<compressor>");
            t.soundData.append("</compressor>");
        }
};

class Reverb: public ProcessingStage {
    protected:
        void MyProcessStage(SoundTrack &t) override {
            t.soundData.insert(0,"<reverb>");
            t.soundData.append("</reverb>");
        }
};

class Gain: public ProcessingStage {
    protected:
        void MyProcessStage(SoundTrack &t) override {
            t.soundData.insert(0,"<gain>");
            t.soundData.append("</gain>");
        }
};

void ChainOfResponsibilityTestCode() {
    SoundTrack tr{"Song1"};
    Compressor comp;
    Reverb re;
    Gain g;
    re.SetNextStage(g);
    g.SetNextStage(comp);
    re.Process(tr);
    cout << tr.soundData << endl;
}

int main() {
    ChainOfResponsibilityTestCode();
}
