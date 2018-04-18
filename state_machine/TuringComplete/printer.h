#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <ostream>

template<typename Rule>
struct RulePrinter {
    typedef typename Rule::old_state old_state;
    typedef typename Rule::input input;
    typedef typename Rule::new_state new_state;
    typedef typename Rule::output output;
    static Direction const direction = Rule::direction;

    static void print_dot(std::ostream& os)
    {
        os << old_state::name << " -> "
                << new_state::name;
        os << " [ label = \"" << input::name << " -> "
                << output::name << ','
                << (direction==Left ? "L" : "R") << "\" ];\n";
    }
};

template<typename Transitions>
struct TransitionsPrinter {
    typedef Transitions transitions;
    static void print_dot(std::ostream& os)
    {
        RulePrinter<typename transitions::type>::print_dot(os);
        TransitionsPrinter<typename transitions::tail>::print_dot(os);
    }
};

template<>
struct TransitionsPrinter<TypeList<>> {
    static void print_dot(std::ostream& os)
    {
        // empty
    }
};

enum {
    LeftToRight,
    TopToBottom
};

template<typename Turing>
struct DiagramPrinter {
    typedef typename Turing::input input;
    typedef typename Turing::transitions transitions;
    typedef typename Turing::start_state start_state;

    // runtime stuff
    static void print_dot(std::ostream& os, int rank_dir)
    {
        char const* rank_codes[] = {"LR", "TB"};
        if (rank_dir<0 || rank_dir>=sizeof rank_codes/sizeof *rank_codes)
            return;
        os << "digraph finite_state_machine {\n";
        os << "rankdir=" << rank_codes[rank_dir] << ";\n";
        os << "node [shape = circle];\n";
        TransitionsPrinter<transitions>::print_dot(os);
        os << "}" << std::endl;
    }
};

#endif
