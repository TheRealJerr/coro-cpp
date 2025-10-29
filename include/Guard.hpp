#pragma once
#include <coroutine>
#include "Command.hpp"

namespace coro
{
    // A guard use RAII to manage the lifetime of a coroutine handle
    template <typename promise_type>
    class CoroHandleGuard
    {
        using handle_t = std::coroutine_handle<promise_type>;

        handle_t handle_;

    public:

        CoroHandleGuard(handle_t handle) : handle_(std::move(handle)) {}

        CoroHandleGuard(std::nullptr_t) : handle_(nullptr) {}

        CoroHandleGuard() = default;

        // delete Constructors and assignment operators
        CoroHandleGuard(const CoroHandleGuard&) = delete;

        CoroHandleGuard& operator=(const CoroHandleGuard&) = delete;
        // 
        CoroHandleGuard(CoroHandleGuard&& other) noexcept 
            : handle_(Tools::exchange(other.handle_, nullptr)) 
        {}

        promise_type& promise()
        {
            return handle_.promise();
        }

        void resume() const noexcept
        {
            handle_.resume();
        }
        bool done() const noexcept
        {
            return handle_.done();
        }
        // detach the coroutine handle and return it
        // give the ownership of the coroutine to the caller
        std::coroutine_handle<> detach()
        {
            return Tools::exchange(handle_, nullptr);
        }

        ~CoroHandleGuard()
        {
            if (handle_ != nullptr)
                handle_.destroy();
        }
    };
}