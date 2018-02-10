#include<iostream>
#include<string>
#include<list>
#include<memory>

using namespace std;

/* Observer Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Observer_pattern */

class MessageUpdater;

class MessageObserver {
    public:
        virtual void LetMeKnow(MessageUpdater *u) = 0;
};

class MessageUpdater {
    public:
        void Attach(MessageObserver *o) {
            ob.push_back(o);
        }

        void Detach(MessageObserver *o) {
            ob.remove_if([&o](MessageObserver *i){return i == o;});
        }

        void UpdateMe(const string &str) {
            info = str;
            for (auto &p:ob)
                p->LetMeKnow(this);
        }

        string GetInfo() {
            return info;
        }

    private:
        list<MessageObserver*> ob;
        string info;
};

class MessageObserver1: public MessageObserver {
    public:
    void LetMeKnow(MessageUpdater *u) override {
        cout << "This is observer 1 ..." << endl;
        string info = u->GetInfo();
        cout << "Get message: " << info << endl;
    }
};

class MessageObserver2: public MessageObserver {
    public:
    void LetMeKnow(MessageUpdater *u) override {
        cout << "This is observer 2 ..." << endl;
        string info = u->GetInfo();
        cout << "Get message: " << info << endl;
    }
};

void ObserverPatternTestCode() {
    MessageUpdater up;
    MessageObserver1 ob1;
    MessageObserver2 ob2;
    up.Attach(&ob1);
    up.Attach(&ob2);
    string s1 = "This is a message";
    up.UpdateMe(s1);
    up.Detach(&ob1);
    string s2 = "Another message";
    up.UpdateMe(s2);
}

int main() {
    ObserverPatternTestCode();
}
