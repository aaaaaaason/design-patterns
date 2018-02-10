#include<iostream>

using namespace std;

/* Decorator Pattern
 * The code is referenced from
 * https://en.wikipedia.org/wiki/Decorator_pattern
 * This pattern is used when:
 * a. Responsibilities should be added to (and removed from) 
 * an object dynamically at run-time.
 * b. A flexible alternative to subclassing for extending 
 * functionality should be provided */

class Human {
    public:
        virtual void Walk() = 0;
};

class Man: public Human {
    public:
        void Walk() override {
            cout << "Walk man" << endl;
        }
};

class WalkDecorator: public Human {
    public:
        WalkDecorator(Human *i): m{i} {}
        void Walk() = 0;
    protected:
        Human *m;
};

class WalkWithShoes: public WalkDecorator {
    public:
        WalkWithShoes(Human* i): WalkDecorator{i} {}
        void Walk() override {
            m->Walk();
            cout << "with shoes" << endl;
        }
};

void DecoratorTestCode() {
    Man m;
    WalkWithShoes w = WalkWithShoes(&m);
    w.Walk();
}

int main() {
    DecoratorTestCode();
}
