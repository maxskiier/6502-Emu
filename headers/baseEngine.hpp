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
    template<typename T>
    struct promise_type
    {
    private:
        T* baseStruct;
    public:
        std::exception_ptr exception_;
        promise_type(T* base)
        {
            *baseStruct = base;
            return;
        }
        std::suspend_never initial_suspend()
        {
            return {};
        }
        std::suspend_never final_suspend() noexcept
        {
            return {};
        }

        auto yield_value(uint8_t step)
        {
            baseStruct->cpuStep = step;
            return std::suspend_always{};
        }

        Task get_return_object()
        {
            return {};
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

        ~promise_type() = default;
    };
    uint8_t cpuStep = 0;

    promise_type<Task> promise{this};
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
