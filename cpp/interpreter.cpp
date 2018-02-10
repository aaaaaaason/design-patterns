#include<iostream>
#include<stack>
#include<string>
#include<map>
#include<memory>

using namespace std;

/* Interpreter Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Interpreter_pattern */

class Expression {
    public:
        virtual int Interpret(map<string, Expression*> &var) = 0;
        virtual ~Expression(){};
};

class Number: public Expression {
    public:
        Number(int n): num{n} {}
        int Interpret(map<string, Expression*> &var) override {
            return num;
        }
    private:
        int num;
};

class Plus: public Expression {
    public:
        Plus(Expression *l, Expression *r): left{l}, right{r} {};
        int Interpret(map<string, Expression*> &var) override {
            return left->Interpret(var) + right->Interpret(var);
        }
    private:
        unique_ptr<Expression> left, right;
};

class Minus: public Expression {
    public:
        Minus(Expression *l, Expression *r): left{l}, right{r} {}
        int Interpret(map<string, Expression*> &var) {
            return left->Interpret(var) - right->Interpret(var);
        }
    private:
        unique_ptr<Expression> left, right;
};

class Variable: public Expression {
    public:
        Variable(string n): name(n) {}
        int Interpret(map<string, Expression*> &var) {
            return var[name]->Interpret(var);
        }
    private:
        string name;
};

class Evaluator: public Expression {
    public:
        Evaluator(string e) {
            stack<Expression*> stk;
            for (auto &c : e) {
                switch(c) {
                case '+':
                {
                    Expression *t1 = stk.top();
                    stk.pop();
                    Expression  *t2 = stk.top();
                    stk.pop();
                    stk.push(new Plus(t2, t1));
                    break;
                }
                case '-':
                {
                    Expression *t1 = stk.top();
                    stk.pop();
                    Expression *t2 = stk.top();
                    stk.pop();
                    stk.push(new Minus(t2, t1));
                    break;
                }
                case ' ':
                {
                    continue;
                    break;
                }
                default:
                {
                    string t{c};
                    stk.push(new Variable(t));
                    break;
                }
                }
            }
            root = stk.top();
            stk.pop();
        }
        int Interpret(map<string, Expression*> &var) override {
            return root->Interpret(var);
        } 
    private:
        Expression *root;
};

void InterpreterTestCode() {
    string exp{"w x z - +"};
    Evaluator eval{exp};
    map<string, Expression*> context;
    Number w{5}, x{10}, z{42};
    context["w"] = &w;
    context["x"] = &x;
    context["z"] = &z;
    cout << eval.Interpret(context) << endl;
};

int main() {
    InterpreterTestCode();
}
