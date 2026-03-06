#include "../headers/baseEngine.hpp"
#include "../headers/cpu.hpp"
#include "../headers/ppu.hpp"

namespace logic
{

void engine::cycle()
{
    ppuPtr->cycle();
    if (this->awaitCPUCycle == 0)
    {
        cpuPtr->cycle();
        this->cpuCycleCounter++;
        this->awaitCPUCycle = 0;
    } else this->awaitCPUCycle--;
}

}
