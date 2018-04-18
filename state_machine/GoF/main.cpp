#include "machine.h"

int main()
{
    Machine m;

    std::cout << " ------ Starting Machine ------ " << std::endl;
    m.start();

    std::cout << " ------ Moving and Painting (1) ------ " << std::endl;
    m.bringDown();
    m.bringDown();
    m.liftUp();
    m.liftUp();
    m.turnRight();
    m.paint(Machine::Color::BLUE);
    m.turnLeft();
    m.paint(Machine::Color::RED);
    m.paint(Machine::Color::BLUE);

    std::cout << " ------ Moving and Painting (2) ------ " << std::endl;
    m.bringDown();
    m.bringDown();
    m.liftUp();
    m.liftUp();
    m.turnRight();
    m.paint(Machine::Color::BLUE);
    m.turnLeft();
    m.paint(Machine::Color::RED);
    m.paint(Machine::Color::BLUE);

    return 0;
}