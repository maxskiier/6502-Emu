#pragma once
#ifndef BASEENGINE_HPP
#define BASEENGINE_HPP

#include <cstdint>

// template<typename T>
// concept classCon = std::is_pointer_v<T> && std::is_class_v<std::remove_pointer_t<T>>;

namespace logic {

class cpu;
class ppu;

extern cpu* primary;
extern ppu* graphics;

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
    void cycle();

};
}
#endif // BASEENGINE_HPP
