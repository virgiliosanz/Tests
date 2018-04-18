//
// Created by Virgilio Sanz on 20/5/16.
//

#include "Relay.h"
#define digitalWrite(PIN, ACTION) std::cout << "Pin id: " << PIN << "Action: "#ACTION << std::endl;

namespace RelayNS {
    struct State;
    struct Iddle;
    struct Working;
    struct Deactivate;
}

struct RelayImpl {
    RelayNS::State* state;
    uint8_t pin;

    // States
    RelayNS::Iddle *iddle;
    RelayNS::Working *working;
    RelayNS::Deactivate *off;

    RelayImpl();
    ~RelayImpl();

    void set_state(RelayNS::State* _state);

    void activate();
    void deactivate();

    bool is_active();

    void turn_on();
    void turn_off();
    bool is_on();
};

namespace RelayNS {
    struct State {
        virtual void activate(RelayImpl* machine) = 0;
        virtual void deactivate(RelayImpl* machine) = 0;

        virtual bool is_active() = 0;

        virtual void turn_on(RelayImpl* machine) = 0;
        virtual void turn_off(RelayImpl* machine) = 0;
        virtual bool is_on() = 0;
    };

    struct Deactivate : State {
        virtual void activate(RelayImpl* machine) { machine->set_state(machine->iddle); };
        virtual void deactivate(RelayImpl* machine) { machine->set_state(machine->off); };

        virtual bool is_active() { return false; };

        virtual void turn_on(RelayImpl* machine) { }
        virtual void turn_off(RelayImpl* machine) { }
        virtual bool is_on() { return false; }
    };

    struct Working : State {
        virtual void activate(RelayImpl* machine) { };
        virtual void deactivate(RelayImpl* machine)
        {
            digitalWrite(machine->pin, LOW);
            machine->set_state(machine->off);
        };

        virtual bool is_active() { return true; };

        virtual void turn_on(RelayImpl* machine) { }
        virtual void turn_off(RelayImpl* machine)
        {
            digitalWrite(machine->pin, LOW);
            machine->set_state(machine->iddle);
        }

        virtual bool is_on() { return true; }

    };
    struct Iddle : State {
        virtual void activate(RelayImpl* machine) { };
        virtual void deactivate(RelayImpl* machine) { machine->set_state(machine->off); };
        virtual bool is_active() { return true; };

        virtual void turn_on(RelayImpl* machine) { digitalWrite(machine->pin, HIGH); }
        virtual void turn_off(RelayImpl* machine) { }
        virtual bool is_on() { return false; }

    };
}

// RelayImpl - Implementation
void RelayImpl::RelayImpl(uint8_t pin_) {
    pin = pin_;

    iddle = new RelayNS::Iddle{};
    working = new RelayNS::Working{};
    off = new RelayNS::Deactivate{};

    state = iddle;
}

void RelayImpl::~RelayImpl() {
    delete iddle;
    delete working;
    delete off;
}

void RelayImpl::set_state(RelayNS::State* _state) { state = _state; }

void RelayImpl::activate() { state->activate(*this); }
void RelayImpl::deactivate() { state->deactivate(*this); }

bool RelayImpl::is_active() { return state->is_active(); }

void RelayImpl::turn_on() { state->turn_on(*this); }
void RelayImpl::turn_off() { state->turn_off(*this); }
bool RelayImpl::is_on() { return state->is_on(); }

// Relay - Implementation
Relay::Relay(uint8_t pin)
{
    _impl = new RelayImpl{pin};
}

Relay::~Relay()
{
    delete _impl;
}

void Relay::activate() { _impl->activate(); }
void Relay::deactivate() { _impl->deactivate(): }

bool is_active() { return _impl->is_active(); }

void Relay::turn_on() { _impl->switch_on(); }
void Relay::turn_off() { _impl->switch_off(); }

void Relay::turn()
{
    if (is_on()) {
        turn_off();
    }
    else {
        turn_on();
    }
}

bool is_on() { return _impl->is_on(); }