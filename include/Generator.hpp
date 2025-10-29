#pragma once
#include "Promise.hpp"
#include "Guard.hpp"
#include "Iterator.hpp"

namespace coro
{
    template <typename T>
    class Generator {
        
    public:
        // Store the coroutine handle
        using promise_type = GeneratorPromise<T>;
        using handle_t = std::coroutine_handle<promise_type>;

        using iterator = GeneratorIterator<T>;

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

        iterator begin()
        {
            handle_.resume();
            return iterator(std::move(handle_));
        }

        std::default_sentinel_t end()
        {
            return {};
        }
    private:
        CoroHandleGuard<promise_type> handle_;
    };
}