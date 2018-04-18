#include <iostream>

using namespace std;

int main()
{
    auto myfunc = []() { cout << "Greetings from the lambda" << endl;  };

    myfunc();

    return 1;
}

