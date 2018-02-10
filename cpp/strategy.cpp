#include<iostream>
#include<string>

using namespace std;

/* Strategy Pattern 
 * The code is referenced from
 * https://en.wikipedia.org/wiki/Strategy_pattern */

class AttackStrategy {
    public:
        virtual void Attack() = 0;
        virtual ~AttackStrategy() {}
};

class RodAttack: public AttackStrategy {
    public:
        void Attack() override {
            cout << "Punch!!" << endl;
        }
};

class GunAttack: public AttackStrategy {
    public:
        void Attack() override {
            cout << "Bang!!" << endl;
        }
};

class BareHandAttack: public AttackStrategy {
    public:
        void Attack() override {
            cout << "Crunch!!" << endl;
        }
};


class Man {
    public:
        void SetAttackStrategy(AttackStrategy *attack) {
            s = attack;
        }
        Man(): s{nullptr} {}
        void Attack() {
            s->Attack();
        }
    private:
        AttackStrategy *s;
};

void StrategyPatternTestCode() {
    Man m;
    GunAttack gun;
    RodAttack rod;
    BareHandAttack bare;
    m.SetAttackStrategy(&gun);
    m.Attack();
    m.SetAttackStrategy(&rod);
    m.Attack();
    m.SetAttackStrategy(&bare);
    m.Attack();
}

int main() {
    StrategyPatternTestCode();
}
