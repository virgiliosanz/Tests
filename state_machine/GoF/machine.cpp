#include "machine.h"

void Machine::start() {
    LevelState::init<High>(*this, levelState);
    DirectionState::init<Left>(*this, directionState);
}

void Machine::Red::paint(Machine::Color color) {
    if (Color::BLUE == color) change<Blue>();
    else ColorState::paint(color);
}

void Machine::Blue::paint(Machine::Color color) {
    if (Color::RED == color) change<Red>();
    else ColorState::paint(color);
}
