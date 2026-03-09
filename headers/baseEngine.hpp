#pragma once
#include <exception>
#ifndef BASEENGINE_HPP
#define BASEENGINE_HPP

#include <cstdint>
#include <coroutine>
#ifdef __APPLE__
#include "engineImplementations/cocoa.hpp"
#elif defined(_WIN32) || defined(_WIN64)
#include "engineImplementations/win32.hpp
#elif defined(__LINUX__) || defined(LINUX)
#include "wayland.hpp"
#else
static_assert(false, "System is incompatabile with codebase");
#endif

// template<typename T>
// concept classCon = std::is_pointer_v<T> && std::is_class_v<std::remove_pointer_t<T>>;

namespace logic {

class cpu;
class ppu;

extern cpu* primary;
extern ppu* graphics;

struct Task
{
    struct promise_type
    {
    public:
        std::exception_ptr exception_;
        std::suspend_always initial_suspend()
        {
            return {};
        }
        std::suspend_never final_suspend() noexcept
        {
            return {};
        }

        auto yield_value(uint8_t step)
        {
            cpuStep = step;
            return std::suspend_always{};
        }

        static constexpr uint8_t fetch = 0;
        static constexpr uint8_t decode = 1;
#define T_STATE(n) static constexpr uint8_t executeT##n = n
        T_STATE(1); // Damned pice of shit consteval not working...
        T_STATE(2); // Temporary until C++26 releases
        T_STATE(3); // Reflection will be used in the future
        T_STATE(4);
        T_STATE(5);
        T_STATE(6);
        T_STATE(7);
#undef T_STATE
        Task get_return_object()
        {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        void return_void()
        {
            return;
        }

        void unhandled_exception()
        {
            exception_ = std::current_exception();
            return;
        }
        uint8_t cpuStep = 0;

        ~promise_type() = default;
    };

    std::coroutine_handle<promise_type> promise;
};

class engine
{
private:
    cpu* cpuPtr = primary;
    ppu* ppuPtr = graphics;

    uint64_t masterCycleCounter;
    uint64_t cpuCycleCounter;
    uint64_t ppuCycleCounter;
    uint8_t awaitCPUCycle = 3;
public:
    Task cycle();

    uint16_t pollKeyboard();
};
}
#endif // BASEENGINE_HPP
