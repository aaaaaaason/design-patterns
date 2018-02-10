#include<iostream>
#include<string>
#include<memory>

using namespace std;

/* Iterator Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Iterator_pattern */

template<typename T>
class Iterator {
    public:
        virtual Iterator& Next() = 0;
        virtual bool HasNext() = 0;
        virtual ~Iterator() {}
        virtual T Value() = 0;
};

template<typename T>
class Aggregate {
    public:
        virtual unique_ptr<Iterator<T>> CreateIterator() = 0;
};

class MyStaticIntArray;

class MyStaticIntIterator: public Iterator<int> {
    public:
        MyStaticIntIterator(MyStaticIntArray *my): idx{0}, arr{my} {}
        Iterator<int>& Next() override { 
            ++idx;
            return *this;
        }

        bool HasNext() override;
        int Value() override;
    private:
        int idx;
        MyStaticIntArray *arr;
};

class MyStaticIntArray: public Aggregate<int> {
    friend class MyStaticIntIterator;
    public:
        MyStaticIntArray(int size) {
            pa = new int [size];
            this->size = size;
            /* Just an initialization */
            for (int i = 0; i < size; ++i)
                pa[i] = i;
        }

        ~MyStaticIntArray() {
            cout << "MyStaticIntArray destoy" << endl;
            delete [] pa;
        }

        unique_ptr<Iterator<int>> CreateIterator();

    private:
        int *pa;
        int size;
};

bool MyStaticIntIterator::HasNext() {  
    return idx == (arr->size - 1)? false : true;
}

int MyStaticIntIterator::Value() {
    return arr->pa[idx];
}

unique_ptr<Iterator<int>> MyStaticIntArray::CreateIterator() {
    return make_unique<MyStaticIntIterator>(this);        
}

void IteratorTestCode() {
    const int size = 20;
    MyStaticIntArray my{size};
    auto it = my.CreateIterator();
    it->HasNext();
    for (int i = 0; i < size; ++i) {
        cout << "HasNext: " << it->HasNext() << "  Value: " << it->Value() << endl;
        it->Next();
    }
}

int main() {
    IteratorTestCode();
}
