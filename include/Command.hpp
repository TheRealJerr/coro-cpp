#pragma once
#include <iostream>
#include <coroutine>
#include <type_traits>
#include <utility>
namespace Tools
{
    // provide std::exchange which is defined in C++23

    template <typename T, typename U>
    T exchange(T& obj, U&& new_value)
    {
        T old_value = std::move(obj);
        obj = std::forward<U>(new_value);
        return old_value;
    }

    
}