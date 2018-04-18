// http://codereview.stackexchange.com/questions/40686/state-pattern-c-template
#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <string>

#include "genericstate.h"

class Machine {
  public:
    Machine() {}
    ~Machine() {}
    void start();

  public:
    enum class Color { BLUE, RED };

  public:
    void liftUp() { levelState->liftUp(); }
    void bringDown() { levelState->bringDown(); }
    void paint(Color color) { directionState->paint(color); }
    void turnRight() { directionState->turnRight(); }
    void turnLeft() { directionState->turnLeft(); }

  private:
    static void print(const std::string &str) { std::cout << str << std::endl; }

    static void unhandledEvent() { print("unhandled event"); }
    void changedColor() { print("changed color"); }

  private:
    struct LevelState : public GenericState<Machine, LevelState> {
        using GenericState::GenericState;
        virtual void liftUp() { unhandledEvent(); }
        virtual void bringDown() { unhandledEvent(); }
    };
    StateRef<LevelState> levelState;

    struct High : public LevelState {
        using LevelState::LevelState;
        void entry() { print("entering High"); }
        void liftUp() { print("already High"); }
        void bringDown() { change<Low>(); }
        void exit() { print("leaving High"); }
    };

    struct Low : public LevelState {
        using LevelState::LevelState;
        void entry() { print("entering Low"); }
        void liftUp() { change<High>(); }
        void bringDown() { print("already Low"); }
        void exit() { print("leaving Low"); }
    };

  private:
    struct ColorState : public GenericState<Machine, ColorState> {
        using GenericState::GenericState;
        virtual void paint(Color color) {
            (void)color;
            unhandledEvent();
        }
    };

    struct Red : public ColorState {
        using ColorState::ColorState;
        void entry() { m.changedColor(); }
        void paint(Color color);
    };

    struct Blue : public ColorState {
        using ColorState::ColorState;
        void entry() { m.changedColor(); }
        void paint(Color color);
    };

  private:
    struct DirectionState : public GenericState<Machine, DirectionState> {
        using GenericState::GenericState;
        virtual void paint(Color color) {
            (void)color;
            unhandledEvent();
        }
        virtual void turnRight() { unhandledEvent(); }
        virtual void turnLeft() { unhandledEvent(); }
    };
    StateRef<DirectionState> directionState;

    struct Left : public DirectionState {
        using DirectionState::DirectionState;
        void entry() { ColorState::init<Red>(m, colorState); }
        void paint(Color color) { colorState->paint(color); }
        void turnRight() { change<Right>(); }

      private:
        StateRef<ColorState> colorState;
    };

    struct Right : public DirectionState {
        using DirectionState::DirectionState;
        void turnLeft() { change<Left>(); }
    };
};

#endif // MACHINE_H
