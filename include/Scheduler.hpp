#pragma once
#include "Command.hpp"
#include <list>


namespace coro
{

    class WakeupAwaitable;
    // this a Scheduler class that manages the execution of coroutines
    class Scheduler
    {
    public:
        using handle_t = std::coroutine_handle<>;
        Scheduler() = default;
        ~Scheduler() = default;
        void enqueue(handle_t handle) {
            assert(not handle.done());
            coroutines_.push_back(handle);
        }
        void run() const {
            while(not coroutines_.empty())
            {
                auto active_coro = coroutines_.front();
                coroutines_.pop_front();
                assert(not active_coro.done());
                active_coro.resume();

                if(active_coro.done())
                    active_coro.destroy();
            }
        }
        class WakeupAwaitable
        {
        public:

            bool await_ready()noexcept
            {
                return false;
            }

            void await_suspend(std::coroutine_handle<> handle)noexcept
            {
                Scheduler{}.enqueue(handle);
            }

            void await_resume()noexcept
            {};
        };

        WakeupAwaitable wake_up() const { return WakeupAwaitable{}; }
    private:
        static inline std::list<handle_t> coroutines_; 
    };
}