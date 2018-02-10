#include <iostream>

using namespace std;

/* Template Method Design Pattern 
 * The code is referenced from 
 * http://www.bogotobogo.com/DesignPatterns/template.php */

class AssembleCar {
    public:
        void TemplateMethod() {
            cout << "Instruction 1:" << endl;
            GetBody(); 
            cout << "Instruction 2:" << endl;
            InsertEngine();
            cout << "Instruction 3:" << endl;
            Coating();
        }

        virtual void GetBody() = 0;
        virtual void InsertEngine() = 0;
        virtual void Coating() = 0;
};

class AssembleTruck: public AssembleCar {
    public:
        void GetBody() override {
            cout << "Get a truck body" << endl;
        }
        void InsertEngine() override {
            cout << "Insert a truck engine" << endl;
        }
        void Coating() override {
            cout << "Do truck coating" << endl;
        }
};

class AssembleTank: public AssembleCar {
    public:
        void GetBody() override {
            cout << "Get a tank body" << endl;
        }
        void InsertEngine() override {
            cout << "Insert a tank engine" << endl;
        }
        void Coating() override {
            cout << "Do tank coating" << endl;
        }
};

void TemplateMethodTestCode() {
    AssembleTruck tr;
    tr.TemplateMethod();    
    cout << endl;
    AssembleTank ta;
    ta.TemplateMethod();
}

int main() {
    TemplateMethodTestCode();
}
