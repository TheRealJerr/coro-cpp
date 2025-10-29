#pragma once
#include "Promise.hpp"
#include "Guard.hpp"

namespace coro
{
    template <typename T>
    class Generator {
        
    public:
        // Store the coroutine handle
        using promise_type = GeneratorPromise<T>;
        using handle_t = std::coroutine_handle<promise_type>;
        Generator(handle_t handle)
        : handle_(handle) 
        {}
        
        // Let the coroutine generate the next result if it's not yet done
        bool exhausted() {
            if (not handle_.done())
                handle_.resume();
            return handle_.done();
        }

        T get() {
            return handle_.promise().result_;
        }
    private:
        CoroHandleGuard<promise_type> handle_;
    };
}