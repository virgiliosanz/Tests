#ifndef IS_SAME_HPP
#define IS_SAME_HPP

template<typename A, typename B>
struct IsSame {
    enum {
        value = false
    };
};

template<typename A>
struct IsSame<A, A> {
    enum {
        value = true
    };
};

#endif
