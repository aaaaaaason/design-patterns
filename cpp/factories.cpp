#include<iostream>
#include<string>
#include<vector>
#include<memory>

using namespace std;

/* Abstact Factory Pattern:
 * This example is referenced from the website:
 * http://www.bogotobogo.com/DesignPatterns/abstractfactorymethod.php */

/* Each kind of product and its interface */

class Button {
    public:
        virtual ~Button(){}
        virtual void Paint() = 0;
};

class MacButton: public Button {
    public:
        void Paint() override {
            cout << "Mac button" << endl;
        }
};

class WinButton: public Button {
    public:
        void Paint() override {
            cout << "Win button" << endl;
        }
};

class ScrollBar {
    public:
        virtual ~ScrollBar() {}
        virtual void Paint() = 0;
};

class MacScrollBar: public ScrollBar {
    public:
        void Paint() override {
            cout << "Mac scrollbar" << endl;
        }
};

class WinScrollBar: public ScrollBar {
    public:
        void Paint() override {
            cout << "Win scrollbar" << endl;
        }
};

/* Now it's the abstract factory part */

class Factory {
    public:
        virtual ~Factory() {}
        virtual Button *CreateButton() = 0;
        virtual ScrollBar *CreateScrollBar() = 0;
};

class MacFactory: public Factory {
    public:
        Button* CreateButton() override {
            return new MacButton();
        }

        ScrollBar* CreateScrollBar() override {
            return new MacScrollBar();
        }
};

class WinFactory: public Factory {
    public:
        Button* CreateButton() override {
            return new WinButton();
        }

        ScrollBar* CreateScrollBar() override {
            return new WinScrollBar;
        }
};

void AbstractFactoryTestCode() {
    cout << "AbstractFactoryTestCode" << endl;
    unique_ptr<Factory> winFact(new WinFactory());
    winFact->CreateButton()->Paint();
    winFact->CreateScrollBar()->Paint();
    unique_ptr<Factory> macFact(new MacFactory());
    macFact->CreateButton()->Paint();
    macFact->CreateScrollBar()->Paint();
}

/* Factory Method Pattern
 * This example is referenced from the website:
 * https://gist.github.com/pazdera/1099562 */

/* Create products */

class Cup {
    public:
        enum Color{
            Red,
            Blue
        };
        static Cup* GetCup(Color color);
        virtual void ShowColor() = 0;
};

class RedCup: public Cup {
    public:
        void ShowColor() {
            cout << "Red one" << endl;
        }
};

class BlueCup: public Cup {
    public:
        void ShowColor() {
            cout << "Blue one" << endl;
        }
};

Cup* Cup::GetCup(Cup::Color color) {
    switch(color) {
        case(Cup::Red):
            return new RedCup();
            break;
        case(Cup::Blue):
            return new BlueCup();
            break;
        default:
            throw invalid_argument("invalid color");
    }
}

void FactoryMethodTestCode() {
    cout << "FactoryMethodTestCode" << endl;
    unique_ptr<Cup> red{Cup::GetCup(Cup::Red)};
    unique_ptr<Cup> blue{Cup::GetCup(Cup::Blue)};
    red->ShowColor();
    blue->ShowColor();
}

int main() {
    AbstractFactoryTestCode();
    FactoryMethodTestCode();
}

