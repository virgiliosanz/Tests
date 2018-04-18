#include <iostream>

using namespace std;

class State;
class Machine {
  public:
    Machine();
    void setCurrent(State *s) {
        current = s;
    }
    void on();
    void off();

  private:
    class State *current;
};

class ON;
class OFF;

class State {
  public:
    virtual void on(Machine *m) {
        cout << "   already ON\n";
    }
    virtual void off(Machine *m) {
        cout << "   already OFF\n";
    }
  private:
    static ON on();
    static OFF off();
};

void Machine::on() {
    current->on(this);
}

void Machine::off() {
    current->off(this);
}

class ON: public State {
  public:
    ON() {
        cout << "   ON-ctor ";
    };
    ~ON() {
        cout << "   dtor-ON\n";
    };
    void off(Machine *m);
};

class OFF: public State {
  public:
    OFF() {
        cout << "   OFF-ctor ";
    };
    ~OFF() {
        cout << "   dtor-OFF\n";
    };
    void on(Machine *m) {
        cout << "   going from OFF to ON";
        m->setCurrent(&on);
        delete this;
    }
};

void ON::off(Machine *m) {
    cout << "   going from ON to OFF";
    m->setCurrent(off);
    delete this;
}

Machine::Machine() {
    current = off;
    cout << '\n';
}

int main() {
    Machine fsm;
    int num;

    while (1) {
        cout << "Enter 0/1: ";
        cin >> num;

        if (num == 0) {
            fsm.off();
        } else {
            fsm.on();
        }
    }
}
