#include "Command.hpp"
#include "Guard.hpp"
#include "Scheduler.hpp"

namespace coro
{
    struct Task {
        struct promise_type {
            using handle_t = std::coroutine_handle<promise_type>;
            Task get_return_object() {
                return Task{handle_t::from_promise(*this)};
            }
            std::suspend_always initial_suspend() noexcept { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            void return_void() {}
            void unhandled_exception() {}
        };

        void detach() {
            // Give control of this coroutine to the scheduler
            
            Scheduler{}.enqueue(handle_.detach());
        }

        // Store the coroutine handle
        explicit Task(promise_type::handle_t handle)
        : handle_(handle) {}
    private:
        CoroHandleGuard<promise_type> handle_;
    };

    // 可等待协程
    struct AwaitableTask
    {
        struct promise_type {
            using handle_t = std::coroutine_handle<promise_type>;
            Task get_return_object() {
                return Task{handle_t::from_promise(*this)};
            }
            std::suspend_always initial_suspend() noexcept { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            void return_void() {}
            void unhandled_exception() {}
        };
        
        bool await_ready() const noexcept { return false; }

        std::coroutine_handle<> await_suspend(std::coroutine_handle<> caller)noexcept 
        {
            
        }

        CoroHandleGuard<promise_type> handle_;
    };
}