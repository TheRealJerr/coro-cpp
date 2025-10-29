#include <Generator.hpp>
#include <Task.hpp>

void test_generator()
{
    auto gen = []() -> coro::Generator<int> {
        co_yield 1;
        co_yield 2;
        co_yield 3;
    };
    for(auto result : gen())
    {
        std::cout << result << std::endl;
    }
}

void test_task()
{
    auto c = []() -> coro::Task {
        printf("stage one");
        co_await coro::Scheduler{}.wake_up();
        printf("stage two");
        co_await coro::Scheduler{}.wake_up();
        printf("stage three");
    };

    c().detach();
    c().detach();
    c().detach();
    coro::Scheduler{}.run();
};

int main()
{
    test_generator();
    test_task();
    return 0;
}