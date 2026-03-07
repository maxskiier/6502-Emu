#include "../headers/cpu.hpp"
#include "../headers/addrSpace.hpp"
#include "../headers/logic.hpp"

namespace logic
{
class addressSpace;
extern addressSpace addrSpace;
extern iniInterface ini;

std::string cpu::decodeT1(uint8_t opcode)
{
    return ini.readOpcodesINISection(eightBitIntToStr(opcode), "name");
}
std::string cpu::decodeT2(uint8_t opcode)
{
    return ini.readOpcodesINISection(eightBitIntToStr(opcode), "mode");
}
void cpu::cycle()
{
    bus = addrSpace.readRom(programCounterRegister);
    return;
}
void cpu::reset(bool coldStart)
{
    m_statusRegister ^= 0b0000100;
    int8_t lo = addrSpace.readRom(0xFFFC);
    int8_t hi = addrSpace.readRom(0xFFFD);
    programCounterRegister = logic::makeWord(lo, hi);
    return;
}
void cpu::interrupt(interruptType interrupt)
{
    if (interrupt == regularInterrupt)
    {
        if ((m_statusRegister & 0b00000100) == 0b00000100) return; // Check the interrupt disable flag, if it's 1 we return
    }
}
cpu* primary;
}
