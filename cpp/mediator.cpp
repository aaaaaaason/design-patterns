#include<iostream>
#include<memory>
#include<string>

using namespace std;

/* Mediator Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Mediator_pattern */

class Colleague;

class Mediator {
    public:
        void Notify(Colleague *c, const string &content);
        void SetColleague(Colleague *cc1, Colleague *cc2) {
            c1 = cc1, c2 = cc2;
        }
    private:
        /* This just want to be a simple example, 
         * I think mediator can get more colleagues and have 
         * complex logic to deal with interactions between them */
        Colleague *c1;
        Colleague *c2;
};

class Colleague {
    public:
        Colleague(Mediator *mm): m{mm} {}
        virtual void NotifySomething(const string &content) = 0;
        virtual void NotifyMeSomething(const string &content) = 0;
    protected:
        /* Therefore, colleague should only be coupled with mediator */
        Mediator *m;
};

void Mediator::Notify(Colleague *c, const string &content) {
    /* Maybe mediator can check the contect and to decide who shoule
     * be notified? (specific group of colleagues or whatever) */
    if (c == c1)
        c2->NotifyMeSomething(content);
    else
        c1->NotifyMeSomething(content);
}

class Colleague1: public Colleague {
    public:
        Colleague1(Mediator *mm): Colleague{mm} {}
        void NotifySomething(const string &content) override {
            m->Notify(this, content);
        }
        void NotifyMeSomething(const string &content) override {
            cout << "Colleague1 got message: " << content << endl;
        }
};

class Colleague2: public Colleague {
    public:
        Colleague2(Mediator *mm): Colleague{mm} {}
        void NotifySomething(const string &content) override {
            m->Notify(this, content);
        }
        void NotifyMeSomething(const string &content) override {
            cout << "Colleague2 got message: " << content << endl;
        }
};

void MediatorTestCode() {
    Mediator m;
    Colleague1 c1{&m};
    Colleague2 c2{&m};
    m.SetColleague(&c1, &c2);
    c1.NotifySomething("Hello, this is c1");
    c2.NotifySomething("Hello, I'm c2");
}

int main() {
    MediatorTestCode();
}
