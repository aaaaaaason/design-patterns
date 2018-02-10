#include<iostream>
#include<string>
#include<memory>

using namespace std;

/* Adaptor Pattern 
 * The code is referenced from
 * https://en.wikipedia.org/wiki/Adapter_pattern */

/* The interface for clients */
class Recharge {
    public:
        virtual void DoRecharge() = 0;
};

/* Original interface */
class AndroidPhone {
    public:
        virtual void RechargeInMicroUSB() = 0;
};

class MyS8: public AndroidPhone {
    public:
        void RechargeInMicroUSB() {
            cout << "S8 is plugged using MicroUSB" << endl;
        }
};

class MyHTC: public AndroidPhone {
    public:
        void RechargeInMicroUSB() {
            cout << "HTC is plugged using MicroUSB" << endl;
        }
};

/* Adaptor */
class AndroidPhoneAdaptor: public Recharge {
    public:
        AndroidPhoneAdaptor(AndroidPhone* p): phone{p} {}

        void DoRecharge() override {
            phone->RechargeInMicroUSB();
            cout << "Andorid phone recharging" << endl;
        }
    private:
        AndroidPhone *phone;
};

void AdaptorTestCode() {
    MyS8 s8;
    MyHTC htc;
    AndroidPhoneAdaptor ad1{&s8};
    AndroidPhoneAdaptor ad2{&htc};
    ad1.DoRecharge();
    ad2.DoRecharge();
}

int main() {
    AdaptorTestCode();
}
