#include<iostream>
#include<string>
#include<list>
#include<algorithm>

using namespace std;

/* Composite Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Composite_pattern */

class Graphic {
    public:
        virtual void Draw() = 0;
        virtual ~Graphic() {};
};

class Line: public Graphic {
    public:
        void Draw() override {
            cout << "Draw a line" << endl;
        };
};

class Circle: public Graphic {
    public:
        void Draw() override {
            cout << "Draw a circle" << endl;
        }
};

class Paper: public Graphic {
    public:
        void Add(Graphic *g) {
            l.push_back(g);
        }
        void Del(Graphic *g){
            l.erase(find(l.cbegin(),l.cend(),g));
        }
        void Draw() override {
            for (auto &i:l)
                i->Draw();
        }
        ~Paper() {
            for (auto &i:l)
                delete i;
        }
    private:
        list<Graphic*> l;
};

void CompositeTestCode() {
    /* a composite is an object designed as a composition of
     * one-or-more similar objects, all exhibiting similar 
     * functionality. This is known as a "has-a" relationship
     *  between objects. The key concept is that you can 
     *  manipulate a single instance of the object
     *  just as you would manipulate a group of them.  */
    
    Paper p;
    p.Add(new Circle());
    p.Add(new Line());
    p.Add(new Circle());
    p.Add(new Line());
    p.Draw();
}

int main() {
    CompositeTestCode();
}
