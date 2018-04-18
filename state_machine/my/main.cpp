#include "Machine.h"
#include <iostream>
#include <stdexcept>

int main()
{
    Machine m(10);

    m.sell(10);
    std::cout << "Sold 10 $" << std::endl;

    try {
        m.sell(1);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    m.refill(20);
    std::cout << "Refilled 20 $" << std::endl;

    m.sell(10);
    std::cout << "Sold 10 $" << std::endl;
    std::cout << m.getCurrentStock() << " $ left" << std::endl;

    m.sell(5);
    std::cout << "Sold 5 $" << std::endl;
    std::cout << m.getCurrentStock() << " $ left" << std::endl;

    try {
        m.sell(10);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
