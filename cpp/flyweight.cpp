#include<iostream>
#include<map>
#include<string>
#include<memory>

using namespace std;

/* Flyweight Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Flyweight_pattern */

class CoffeeInfo {
    public:
        CoffeeInfo(double p, string n, string f): unitPrice{p}, name{n}, from{f} {}
        void PrintInfo() {
            cout << "Unitprice: " << unitPrice << endl;
            cout << "Name: " << name << endl;
            cout << "From: " << from << endl;
        }
    private:
        double unitPrice;
        string name;
        string from;
};

class CoffeeJar {
    public:
        CoffeeJar(CoffeeInfo *i, int wei): info{i}, weight{wei} {}
        void ReadJar() {
            info->PrintInfo();
            cout << "Weight: " << weight << endl;
        }
        void ShowShared() {
            cout << info << endl;
        }
    private:
        CoffeeInfo *info;
        int weight;
};

class CoffeeJarFactory {
    public:
        enum CoffeeType {
            Bean1,
            Bean2,
            BeanTypeTotal
        };
        static CoffeeJar* BuyCoffee(int weight, CoffeeType t){
            return new CoffeeJar{&info[t], weight};
        }
    private:
        static CoffeeInfo info[BeanTypeTotal];
};

CoffeeInfo CoffeeJarFactory::info[CoffeeJarFactory::BeanTypeTotal] = {{30.5, "Bean1", "Place1"}, {40, "Bean2", "Place2"}};

void FlyweightTestCode() {
    unique_ptr<CoffeeJar> p[4];
    p[0].reset(CoffeeJarFactory::BuyCoffee(10, CoffeeJarFactory::Bean1));
    p[1].reset(CoffeeJarFactory::BuyCoffee(20, CoffeeJarFactory::Bean2));
    p[2].reset(CoffeeJarFactory::BuyCoffee(30, CoffeeJarFactory::Bean1));
    p[3].reset(CoffeeJarFactory::BuyCoffee(40, CoffeeJarFactory::Bean2));

    /* CoffeeInfo are shared between all CoffeeJars
     * Large numbers of objects can be supported efficiently */
    p[0]->ShowShared();
    p[1]->ShowShared();
    p[2]->ShowShared();
    p[3]->ShowShared();
}

int main() {
    FlyweightTestCode();
}
