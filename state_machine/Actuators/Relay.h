#pragma once

struct RelayImpl;

typedef unsigned char uint8_t;
/**
 * Class to control a Relay:
 *
 * it can be activate or deactivate. So, depending on that state it listen to switch commands.
 */
class Relay {
public:
    Relay(uint8_t pin);
    ~Relay();

    void activate();
    void deactivate();
    bool is_active();

    void turn_on();
    void turn_off();
    void turn();
    bool is_on();

private:
    RelayImpl* _impl;
};