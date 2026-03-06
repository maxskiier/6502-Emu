#include "../headers/cpu.hpp"
#include "../headers/addrSpace.hpp"

namespace logic
{
class addressSpace;
extern addressSpace addrSpace;
void cpu::cycle()
{
    return;
}
void cpu::reset()
{
    int8_t lo = addrSpace.readRom(0xFFFC);
    int8_t hi = addrSpace.readRom(0xFFFD);
}
void cpu::interrupt(interruptType interrupt)
{
    if (interrupt == regularInterrupt)
    {
        if ((statusRegister & 0b00000100) == 0b00000100) return; // Check the interrupt disable flag, if it's 1 we return
    }
}
cpu* primary;
}
