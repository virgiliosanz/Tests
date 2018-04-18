#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

template<bool C, typename = void>
struct EnableIf { /* no typedef here */ };

template<typename Type>
struct EnableIf<true, Type> {
    typedef Type type;
};

#endif
