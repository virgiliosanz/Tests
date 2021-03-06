#include <iostream>

using namespace std;

constexpr bool is_prime_recursive(size_t number, size_t c)
{
    return (c * c > number) ? true : (number % c == 0)
                                         ? false
                                         : is_prime_recursive(number, c + 1);
}

constexpr bool is_prime_func(size_t number)
{
    return (number <= 1) ? false : is_prime_recursive(number, 2);
}

int main(void)
{
    // const int num = 13;
    const int num = 4256233;
    static_assert(is_prime_func(num), "..."); // Computed at compile-time
    int i = num;
    int j = is_prime_func(i); // Computed at run-time

    cout << "J: " << j << endl;
}
