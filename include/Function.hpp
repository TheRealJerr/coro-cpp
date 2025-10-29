#include "Promise.hpp"

namespace coro
{
    template <typename T>
    class Function
    {
    public:
        using promise_type = FunctionPromise<T>;
        using handle_t = promise_type::handle_t;

        
        Function(handle_t handle) : handle_(handle) {}


        T get() {
            return handle_.promise().result();
        }

        operator T() { return get(); }
    private:
        CoroHandleGuard<promise_type> handle_;
        
    };


    template <typename T>
    class LazyFunction
    {   
    public:
        using promise_type = LazyFunctionPromise<T>;
        using handle_t = promise_type::handle_t;

        LazyFunction(handle_t handle) : handle_(handle) {}

        T get()
        {
            if(not handle_.done())
                handle_.resume();
            return handle_.promise().result();
        }
        
        operator T() { return get(); }

    private:
        CoroHandleGuard<promise_type> handle_;
    };
}