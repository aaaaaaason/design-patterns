#include<iostream>
#include<string>
#include<memory>

using namespace std;

/* Singleton Design Pattern */

class Singleton {
    public:
        static Singleton* GetInstance();
        void ShowUnique() {
            cout << this << endl;
        }
        
        Singleton(const Singleton& obj) = delete;
        Singleton& operator=(const Singleton& obj) = delete;
        ~Singleton(){
            cout << "Delete the unique object" << endl;
        }
    private:
        Singleton() = default;
        static unique_ptr<Singleton> instance;
};

unique_ptr<Singleton> Singleton::instance{nullptr};

Singleton* Singleton::GetInstance() {
    if (instance) {
        cout << "Already created" << endl;
        return instance.get();
    } else {
        cout << "Create the unique instance" << endl;
        instance.reset(new Singleton());
        return instance.get();
    }
}

void SingletonTestCode() {
    Singleton *s1 = Singleton::GetInstance();
    Singleton *s2 = Singleton::GetInstance();
    s1->ShowUnique();
    s2->ShowUnique();
    //Singleton s3 = *s1;
    //s3.ShowUnique();
}

int main() {
    SingletonTestCode();
}
