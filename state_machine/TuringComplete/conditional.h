#ifndef CONDITIONAL_HPP
#define CONDITIONAL_HPP

template<bool C, typename A, typename B>
struct Conditional {
    typedef A type;
};

template<typename A, typename B>
struct Conditional<false, A, B> {
    typedef B type;
};

#endif
