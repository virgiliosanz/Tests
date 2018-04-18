#ifndef RULE_HPP
#define RULE_HPP

// one rule definition

// direction either right or left
enum Direction {
    Left = -1,
    Right = 1
};

template<typename OldState, typename Input, typename NewState, typename Output, Direction Move>
struct Rule {
    typedef OldState old_state;
    typedef Input input;
    typedef NewState new_state;
    typedef Output output;
    static Direction const direction = Move;
};

#endif
