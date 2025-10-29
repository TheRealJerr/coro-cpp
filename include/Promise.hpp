#pragma once
#include <type_traits>
#include <utility>
#include <exception>
#include <memory>
#include <coroutine>
#include "Command.hpp"
#include "Guard.hpp"

namespace coro
{
    

    // Function object to wrap a coroutine handle
    template <typename T>
    class Function;

    template <typename T>
    class LazyFunction;

    template <typename T>
    class Generator;

    

    // Promise Type For normal function object
    // this promise type will not suspend and will return the result of the coroutine
    template <typename T>
    class FunctionPromise
    {   
    public:
        using handle_t = std::coroutine_handle<FunctionPromise<T>>;

        Function<T> get_return_object() noexcept
        {
            return Function<T>{ handle_t::from_promise(*this)};
        }
        std::suspend_never initial_suspend() const noexcept
        {
            return {};
        }

        std::suspend_always final_suspend() const noexcept
        {
            return {};
        }

        void unhandled_exception()
        {
            std::terminate();
        }
        
        void return_value(const T& value)
        {
            result_ = value;
        }

        const T& result() const { return result_; }

        T& result() { return result_; }
    private:
        T result_;

    };  
    // promise type for lazy function object
    // this promise will suspend until the coroutine is ready to be resumed
    template <typename T>
    class LazyFunctionPromise
    {
    public:
        using handle_t = std::coroutine_handle<LazyFunctionPromise<T>>;
        LazyFunction<T> get_return_object() noexcept
        {
            return LazyFunction<T>{ handle_t::from_promise(*this)};
        }
        std::suspend_always initial_suspend() const noexcept
        {
            return {};
        }
        std::suspend_always final_suspend() const noexcept
        {
            return {};
        }

        void unhandled_exception()
        {
            std::terminate();
        }

        void return_value(const T& value)
        {
            result_ = value;
        }

        const T& result() const { return result_; }

        T& result() { return result_; }
    private:
        T result_;

    };
    
    template <typename T>
    class GeneratorPromise
    {
    public:
        using handle_t = std::coroutine_handle<GeneratorPromise<T>>;
        Generator<T> get_return_object() noexcept
        {
            return Generator<T>{ handle_t::from_promise(*this)};
        }
        std::suspend_always initial_suspend() const noexcept
        {
            return {};
        }
        std::suspend_always final_suspend() const noexcept
        {
            return {};
        }

        void unhandled_exception()
        {
            std::terminate();
        }

        std::suspend_always yield_value(const T& value)
        {
            result_ = value;
            return {};
        }

        void return_void()
        {
            result_ = T{};
        }

        const T& result() const { return result_; }

        T& result() { return result_; }
    private:
        T result_;

    };

    
    
}