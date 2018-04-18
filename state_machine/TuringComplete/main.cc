
#include "max.h"
#include "enable_if.h"
#include "is_same.h"
#include "conditional.h"
#include "rule.h"
#include "identify.h"
#include "typelist.h"
#include "configuration.h"
#include "turing.h"

#include "printer.h"

template<>
char const* Input<-1>::name = "_";

char const* QAccept::name = "qaccept";
char const* QReject::name = "qreject";

#include <iostream>

int main()
{
    typedef Input<1> x;
    x::name = "x";
    typedef Input<2> x_mark;
    x_mark::name = "x_mark";
    typedef Input<3> split;
    split::name = "split";
    typedef State<0> start;
    start::name = "start";
    typedef State<1> find_blank;
    find_blank::name = "find_blank";
    typedef State<2> go_back;
    go_back::name = "go_back";

    // syntax: Rule< State, Input, NewState, Output, Move >
    typedef TypeList<
            Rule<start, x, find_blank, x_mark, Right>,
            Rule<find_blank, x, find_blank, x, Right>,
            Rule<find_blank, split, find_blank, split, Right>,
            Rule<find_blank, InputBlank, go_back, x, Left>,
            Rule<go_back, x, go_back, x, Left>,
            Rule<go_back, split, go_back, split, Left>,
            Rule<go_back, x_mark, start, x, Right>,
            Rule<start, split, QAccept, split, Left>> rules;

    typedef TuringMachine<TypeList<x, x, x, x, split>, rules, start> double_it;
    static_assert(IsSame<double_it::end_input, TypeList<x, x, x, x, split, x, x, x, x>>::value,
            "Hmm... This is borky!");

    DiagramPrinter<double_it>::print_dot(std::cout, LeftToRight);
}
