#ifndef TURING_HPP
#define TURING_HPP

// building block for one state
template<int n>
struct State {
    enum {
        value = n
    };

    // name of the state
    static char const* name;
};

template<int n>
char const* State<n>::name = "unnamed";

/*
 * Two predefined states
 */
struct QAccept {
    enum {
        value = -1
    };
    static char const* name;
};

struct QReject {
    enum {
        value = -2
    };
    static char const* name;
};

// building blocks for our input
template<int n>
struct Input {
    enum {
        value = n
    };

    // name of the input
    static char const* name;

    template<int... I>
    struct Generate {
        typedef TypeList<Input<I>...> type;
    };
};

template<int n>
char const* Input<n>::name = "unnamed";

/*
 * one predefined input
 */
typedef Input<-1> InputBlank;

template<typename Config, typename Transitions, typename = void>
struct Controller {
    // some parameters that we do expose
    typedef Config config;
    enum {
        position = config::position
    };
    typedef typename Conditional<
            static_cast<int>(GetSize<typename config::input>::value)<=static_cast<int>(position),
            AppendItem<InputBlank, typename config::input>,
            Identity<typename config::input>>::type::type input;
    typedef typename config::state state;

    // input cell that the head is over
    typedef typename GetItem<input, position>::type cell;

    // the rule we now gonna take. we use a matcher template to find the rule
    template<typename Item, typename State, typename Cell>
    struct Matcher {
        typedef typename Item::old_state checking_state;
        typedef typename Item::input checking_input;
        enum {
            value = IsSame<State, checking_state>::value &&
                    IsSame<Cell, checking_input>::value
        };
    };
    typedef typename FindItem<Transitions, Matcher, state, cell>::type rule;

    // define the new parameters passed to the next recursion step
    typedef typename ReplaceItem<input, position, typename rule::output>::type new_input;
    typedef typename rule::new_state new_state;
    typedef Configuration<new_input,
            new_state,
            Max<position+rule::direction, 0>::value> new_config;

    typedef Controller<new_config, Transitions> next_step;
    typedef typename next_step::end_config end_config;
    typedef typename next_step::end_input end_input;
    typedef typename next_step::end_state end_state;
    enum {
        end_position = next_step::position
    };
};

template<typename Input, typename State, int Position, typename Transitions>
struct Controller<Configuration<Input, State, Position>, Transitions,
        typename EnableIf<IsSame<State, QAccept>::value ||
                IsSame<State, QReject>::value>::type> {
    typedef Configuration<Input, State, Position> config;
    enum {
        position = config::position
    };
    typedef typename Conditional<
            static_cast<int>(GetSize<typename config::input>::value)<=static_cast<int>(position),
            AppendItem<InputBlank, typename config::input>,
            Identity<typename config::input>>::type::type input;
    typedef typename config::state state;

    // yeah, we are at the end!
    typedef config end_config;
    typedef input end_input;
    typedef state end_state;
    enum {
        end_position = position
    };
};

/*
 * accepts an input-typelist, the transitions type-list, and the start-state type.
 */
template<typename Input, typename Transitions, typename StartState>
struct TuringMachine {
    typedef Input input;
    typedef Transitions transitions;
    typedef StartState start_state;

    // will either become QAccept or QReject depending on the rules
    typedef Controller<Configuration<Input, StartState, 0>, Transitions> controller;
    typedef typename controller::end_config end_config;
    typedef typename controller::end_input end_input;
    typedef typename controller::end_state end_state;
    enum {
        end_position = controller::end_position
    };
};

#endif
