#include <Function.hpp>
#include <iostream>

void test_function()
{
    auto f = []() -> coro::LazyFunction<int> {
        co_return 42;
    };

    std::cout << f() << std::endl;
}
int main()
{
    test_function();
    return 0;
}