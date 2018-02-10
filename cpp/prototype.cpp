#include<iostream>
#include<string>
#include<memory>

using namespace std;

/* Prototype Design Pattern
 * The code is referenced from
 * https://en.wikipedia.org/wiki/Prototype_pattern */

class ProtoType {
    public:
        virtual ~ProtoType() {}
        virtual ProtoType* Clone() = 0;
        virtual void ShowType() = 0;
};

class ConcreteProtoType1: public ProtoType {
    public:
        ConcreteProtoType1(/* some parameters */) {
            /* a complex object and we may need to do
             * lots of things here or such as we need
             * to initialize it using I/O */
        }

        ProtoType* Clone() override {
            return new ConcreteProtoType1();
        }

        void ShowType() override {
            cout << "This is ConcreteProtoType1" << endl;
        }
    private:
        /* Then if we can maintain a complex object 'prototype' here
         * we can directly create a copy and return to users */
};

class ConcreteProtoType2: public ProtoType {
    public:
        ConcreteProtoType2(){
        }
        ProtoType* Clone() override {
            return new ConcreteProtoType2();
        }
        void ShowType() override {
            cout << "This is ConcreteProtoType2" << endl;
        }
    private:
        /* The same, this pattern eliminated the potentially expensive overhead
         * of initializing an object, please remember that there's no virtual
         * constructor */
};

void ProtoTypeTestCode() {
    ConcreteProtoType1 pt1;
    ConcreteProtoType2 pt2;
    unique_ptr<ProtoType> ob1{pt1.Clone()};
    unique_ptr<ProtoType> ob2{pt2.Clone()};
    ob1->ShowType();
    ob2->ShowType();
}

int main() {
    ProtoTypeTestCode();
}
