#include <future>
#include <iostream>

int calculate_the_answer_to_LtUaE()
{
    std::cout << "Llamada a la función larga" << std::endl;
    return 5;
}

void do_stuff()
{
    std::cout << "Aquí tendria que currar, si acaso le pongo un sleep" << std::endl;
}

int main()
{
    std::future<int> the_answer = std::async(calculate_the_answer_to_LtUaE);
    // auto the_answer = std::async(calculate_the_answer_to_LtUaE);
    do_stuff();
    std::cout << "The answer to life, the universe and everything is "
              << the_answer.get() << std::endl;
}
