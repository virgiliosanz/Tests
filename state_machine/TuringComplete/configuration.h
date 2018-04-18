#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

/*
 * This struct represents the configuration of one turing machine
 * at one time.
 */
template<typename Input, typename State, int Position>
struct Configuration {
    typedef Input input;
    typedef State state;
    enum {
        position = Position
    };
};

#endif
