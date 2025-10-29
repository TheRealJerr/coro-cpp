#include "Promise.hpp"

template <typename T>
class GeneratorIterator
{
public:
    using self_type = GeneratorIterator<T>;
    using self_ref = GeneratorIterator<T>&;
    using promise_type = GeneratorPromise<T>;
    using handle_t = std::coroutine_handle<promise_type>;

    GeneratorIterator(handle_t handle) : handle_(handle) {}

    T& operator*() const { return handle_.promise().value_; }

    self_ref operator++()
    {
        assert(not handle_.done());
        handle_.resume();
        return *this;
    }

    
private:
    handle_t handle_;
};
