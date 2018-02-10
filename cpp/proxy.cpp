#include<iostream>
#include<memory>
#include<string>

using namespace std;

/* Proxy Pattern
 * The code is referenced from
 * https://en.wikipedia.org/wiki/Proxy_pattern */

class DatabaseAccessInterface {
    public:
        virtual ~DatabaseAccessInterface(){}
        virtual bool Connect() = 0;
};

class ProxyDatabase: public DatabaseAccessInterface {
    public:
        ProxyDatabase(DatabaseAccessInterface* r): real{r} {}
        bool Connect() override {
            /* Do access control or other works */
            cout << "Proxy database checking ..." << endl;
            return real->Connect();
        }
    private:
        unique_ptr<DatabaseAccessInterface> real;
};

class RealDatabase: public DatabaseAccessInterface {
    public:
        bool Connect() override {
            /* Do its real works */
            cout << "Real database connecting ..." << endl;
            return true;
        }
};

void ProxyPatternTestCode() {
    unique_ptr<DatabaseAccessInterface> p{new ProxyDatabase{new RealDatabase()}};
    p->Connect();
}

int main() {
    ProxyPatternTestCode();
}
