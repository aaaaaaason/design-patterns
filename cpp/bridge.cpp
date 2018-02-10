#include<iostream>
#include<string>
#include<memory>

using namespace std;

/* Bridge Pattern 
 * The code is referenced from
 * http://www.bogotobogo.com/DesignPatterns/bridge.php 
 * Adapter makes things work after they're designed; 
 * Bridge makes them work before they are [GoF].
 * If you have orthogonal hierachies then this pattern
 * provides a way to decouple the interface and the 
 * implementation. */

class DrawInterface {
    public:
        virtual void Draw() = 0;
};

class DrawTool {
    public:
        virtual void DrawWith() = 0;
};

class DrawCat: public DrawInterface {
    public:
        DrawCat(DrawTool *t): tool{t} {}

        void Draw() override {
            cout << "Draw a cat" << endl;
            tool->DrawWith();
        }
    private:
        DrawTool *tool;
};

class DrawDog: public DrawInterface {
    public:
        DrawDog(DrawTool* t): tool{t} {}
        void Draw() override {
            cout << "Draw a dog" << endl;
            tool->DrawWith();
        }
    private:
        DrawTool * tool;
};

class DrawWithPencil: public DrawTool {
    public:
        void DrawWith() override {
            cout << "Use a pencil" << endl;
        }
};

class DrawWithBrush: public DrawTool {
    public:
        void DrawWith() override {
            cout << "Use a brush" << endl;
        }
};

void BridgeTestCode() {
    DrawWithPencil pencil;
    DrawWithBrush brush;
    DrawDog dogBox{&pencil};
    DrawCat catBox{&brush};
    dogBox.Draw();
    catBox.Draw();
}

int main() {
    BridgeTestCode();
}
