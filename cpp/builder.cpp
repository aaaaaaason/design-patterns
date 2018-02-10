#include<iostream>
#include<vector>
#include<string>
#include<memory>

using namespace std;

/* Builder Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Builder_pattern
 * http://www.oodesign.com/builder-pattern.html */

class Car {
    public:
        Car(string brand, string model, string color, int numOfDoors): _brand(brand), _model(model),
            _color(color), _numOfDoors(numOfDoors) {}
        
        void ShowCar() {
            cout << "brand: " << _brand << endl << "model: " << _model << endl << 
                "color: " << _color << endl << "Num of Doors: " << _numOfDoors << endl;
        }

    private:
        string _brand;
        string _model;
        string _color;
        int _numOfDoors;
};

class CarBuilder {
    public:
        virtual Car* BuildCar() = 0;
        virtual void SetColor(const string & color) = 0;
        virtual void SetTargetPrice(int price) = 0;
    protected:
        string _color;
        int _numOfDoors;
        string _model;
};

class MyCarBuilder: public CarBuilder {
    public:
        void SetColor(const string & color) override {
            _color = color;
        }

        void SetTargetPrice(int price) override {
            if (price < 200000) {
                _numOfDoors = 2;
                _model = "Terrible car";
            } else {
                _numOfDoors = 4;
                _model = "Not bad car";
            }
        }

        Car* BuildCar() override {
            return new Car("My brand", _model, _color, _numOfDoors);
        }
};

class SportsCarBuilder: public CarBuilder {
    public:
        void SetColor(const string & color) override {
            _color = string("Good looking ").append(color);
        }
        void SetTargetPrice(int price) override {
            if (price < 3000000) {
                _numOfDoors = 0;
                _model = "Dangerours one";
            } else {
                _numOfDoors = 2;
                _model = "Fantastic one";
            }
        }

        Car* BuildCar() override {
            return new Car("SportsCar", _model, _color, _numOfDoors);
        }
};

/* Example 2 */

class Computer {
    public:
        enum Storage {
            HDD,
            SSD
        };
        enum CPU {
            Intel,
            AMD
        };
        Computer(CPU c, vector<Storage> s, bool GPU = false): cpu(c), storage(s), hasGPU(GPU) {}
    private:
        CPU cpu;
        vector<Storage> storage;
        bool hasGPU;
};

class ComputerBuilder {
    public:
        virtual ComputerBuilder& SelectCPU(Computer::CPU c) = 0;
        virtual ComputerBuilder& UpgradeGPU(bool hasGPU) = 0;
        virtual ComputerBuilder& AddStorage(Computer::Storage s) = 0;
        virtual Computer* BuildComputer() = 0;    
};

class GamingComputerBuilder: public ComputerBuilder {
    public:
        ComputerBuilder& SelectCPU(Computer::CPU c) override {
            if (c == Computer::Intel)
                cout << "Install CPU: 7700K" << endl;
            else {
                cout << "Install CPU: Ryzen7" << endl;
            }
            return *this; 
        }

        ComputerBuilder& UpgradeGPU(bool hasGPU) override {
            this->hasGPU = hasGPU;
            if (hasGPU)
                cout << "Install 1080Ti" << endl;
            return *this;
        }

        ComputerBuilder& AddStorage(Computer::Storage s) override {
            if (s)
                cout << "Install SSD" << endl;
            else
                cout << "Install HDD" << endl;
            storage.push_back(s);
            return *this;
        }

        Computer* BuildComputer() override {
            cout << "New gaming computer is built!" << endl;
            return new Computer(cpu, storage, hasGPU);
        }

    protected:
        Computer::CPU cpu;
        vector<Computer::Storage> storage;
        bool hasGPU;
};

void BuilderTestCode1(){
    cout << "BuilderTestCode1: " << endl;
    MyCarBuilder myBuild;
    SportsCarBuilder sportsBuild;
    myBuild.SetColor("Yellow");
    myBuild.SetTargetPrice(3000);
    sportsBuild.SetColor("Black");
    sportsBuild.SetTargetPrice(20000000);
    unique_ptr<Car> car1(myBuild.BuildCar());
    unique_ptr<Car> car2(sportsBuild.BuildCar());
    car1->ShowCar();
    car2->ShowCar();
}

void BuilderTestCode2(){
    cout << "BuilderTestCode2: " << endl;
    GamingComputerBuilder builder;
    unique_ptr<Computer> pc(builder.SelectCPU(Computer::Intel).UpgradeGPU(true).AddStorage(
            Computer::SSD).AddStorage(Computer::SSD).BuildComputer());
}

int main() {
    BuilderTestCode1();
    BuilderTestCode2();
}
