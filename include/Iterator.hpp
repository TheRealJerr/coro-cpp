#pragma once
#include <cassert>
#include "Promise.hpp"
#include "Command.hpp"
#include "Guard.hpp"

namespace coro
{
    template <typename T>
    class GeneratorIterator
    {
    public:
        using self = GeneratorIterator<T>;
        using ref = self&;
        using const_ref = const self&;


        using promise_type = GeneratorPromise<T>;
        using handle_t = std::coroutine_handle<promise_type>;

        GeneratorIterator(CoroHandleGuard<promise_type> handle) : handle_(std::move(handle)) {}

        GeneratorIterator(self&& other) noexcept : handle_(Tools::exchange(other.handle_, nullptr)) {}

        const T& operator*() const { return handle_.promise().result(); }
        
        T& operator*() { return handle_.promise().result(); }

        ref operator++() {
            assert(not handle_.done());
            handle_.resume();
            return *this;
        }
        
        void operator++(int){
            ++*this;
        }
        

        ref operator=(self&& other) noexcept{
            handle_ = Tools::exchange(other.handle_, nullptr);
            return *this;
        }
        // end() of the range
        friend bool operator==(const_ref a, std::default_sentinel_t){
            return a.handle_.done();
        }

    private:
        CoroHandleGuard<promise_type> handle_;
    };

}