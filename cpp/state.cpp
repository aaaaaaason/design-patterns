#include<iostream>
#include<string>
#include<memory>

using namespace std;

/* State Pattern
 * The code is referenced from
 * https://en.wikipedia.org/wiki/State_pattern */

class TcpClient;

class TcpClientState {
    public:
        TcpClientState(TcpClient *cli): c{cli} {}
        virtual void Operation() = 0;
        virtual ~TcpClientState() {};
    protected:
        TcpClient *c;
};

class TcpClient{
    public:
        enum State {
            SYN,
            SYNACK,
            ACK,
            TOTAL
        };
        TcpClient();
        void Run() {
            state[st]->Operation();
        }
        void SetState(State s) {
            st = s;
        }
    private:
        unique_ptr<TcpClientState> state[TOTAL];
        State st;
};

class SynState: public TcpClientState {
    public:
        SynState(TcpClient *c): TcpClientState{c} {}
        void Operation() override {
            cout << "Send SYN = 1" << endl;
            c->SetState(TcpClient::SYNACK);
        }          
};

class SynAckState: public TcpClientState {
    public:
        SynAckState(TcpClient *c): TcpClientState{c} {}
        void Operation() override {
            cout << "Wait for SYN = 1, ACK = 1" << endl;
            c->SetState(TcpClient::ACK);
        }
};

class AckState: public TcpClientState {
    public:
        AckState(TcpClient *c): TcpClientState{c} {}
        void Operation() override {
            cout << "Send ACK = 1" << endl;
        }
};

TcpClient::TcpClient() {
    state[SYN].reset(new SynState{this});
    state[SYNACK].reset(new SynAckState{this});
    state[ACK].reset(new AckState{this});
    st = SYN;
}

void StatePatternTestCode() {
    TcpClient client;
    client.Run();
    client.Run(); 
    client.Run();
}

int main() {
    StatePatternTestCode();
}

