#ifndef MAX_HPP
#define MAX_HPP

template<int A, int B>
struct Max {
    enum {
        value = A>B ? A : B
    };
};

#endif
