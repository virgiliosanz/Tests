#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Context
{
    class State
    {
    public:
        virtual void handle() = 0;
        virtual ~State() {}
    };

    class ConcreteState1 : public State
    {
    public:
        void handle() override { cout << "ConcreteState1" << endl; }
    };

    class ConcreteState2 : public State
    {
    public:
        void handle() override { cout << "ConcreteState2" << endl; }
    };

    unique_ptr<State> state;

public:
    Context() : state{ new ConcreteState1 } {}
    ~Context() {}

    void request() { return state->handle(); }
    void changeStateOperation()
    {
        state.reset(new ConcreteState2);
    }
};

int main()
{
    Context ctx;
    ctx.request();
    ctx.changeStateOperation();
    ctx.request();

    return 0;
}