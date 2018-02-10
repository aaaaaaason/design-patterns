#include<iostream>

using namespace std;

/* Facade Pattern
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Facade_pattern */

class Engine {
    public:
        void InstallEngine() {
            cout << "Engine is installed" << endl;
        }

        void TestIt() {
            cout << "Engine is okay" << endl;
        }
};

class Body {
    public:
        void InstallBody() {
            cout << "Body is installed" << endl;
        }

        void CheckBody() {
            cout << "Check the body" << endl;
        }
};

class Coating {
    public:
        void DoCoating() {
            cout << "Coating is done" << endl;
        }

        void Inspect() {
            cout << "Inspect the coating" << endl;
        }
};

class Car {
    public:
        Car(Engine *ee, Body *bb, Coating *cc): e{ee}, b{bb}, c{cc} {}
        void SetupCar() {
            /* Offer a simplified API to ease the usage of complex
             * subsystem */

            e->InstallEngine();
            b->InstallBody();
            b->CheckBody();
            e->TestIt();
            c->DoCoating();
            b->CheckBody();
            c->Inspect();
        }
    private:
        Engine *e;
        Body *b;
        Coating *c;
};

void FacadeTestCode() {
    Engine e;
    Body b;
    Coating c;
    Car car(&e, &b, &c);
    car.SetupCar();    
};

int main() {
    FacadeTestCode();
}
