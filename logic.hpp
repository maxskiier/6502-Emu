#ifndef LOGIC_H
#define LOGIC_H
#include <cstdint>
#include <cstddef>
#include <array>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <fstream>
#include <bit>

using byte = std::byte;

extern std::vector<std::string> passedArgs;

namespace logic
{

class stack;

uint8_t getLowOrderByte(uint16_t word)
/* These are all technically UB but this is the easiest way to do it; it's a temporary solution */
{
    union getByte
    {
        uint16_t inVal;
        uint8_t outVal[2];
    };
    getByte conv;
    conv.inVal = word;
    return conv.outVal[0];
}
uint8_t getHighOrderByte(uint16_t word)
{
    union getByte
    {
        uint16_t inVal;
        uint8_t outVal[2];
    };
    getByte conv;
    conv.inVal = word;
    return conv.outVal[1];
}
uint16_t consolidateBytes(uint8_t b1, uint8_t b2)
// Byte 1 is high order, byte 2 is low order
{
    union putByte
    {
        uint8_t inVals[2];
        uint16_t outVal;
    };
    putByte conv;
    conv.inVals[0] = b2;
    conv.inVals[1] = b1;
    return conv.outVal;
}

class cpu
{
private:
    inline static uint16_t programCounterRegister;
    inline static uint8_t m_accumulatorRegister;
    inline static uint8_t m_xRegister;
    inline static uint8_t m_yRegister;
    inline static uint8_t statusRegister;

    inline static bool jammedState = false;
public:
    class m_stack
    {
    private:
        friend class cpu;
        friend class logic::stack;
        inline static uint8_t m_stackPtr = 0xFF;
    };

    inline static void reset()
    {

    }
#define INTERRUPT_TYPE bool
#define INTERRUPT false
#define NMI true

    inline static void interrupt(INTERRUPT_TYPE interruptType = INTERRUPT)
    {
        if (interruptType == INTERRUPT)
        {
            if ((statusRegister & 0b00000100) == 0b00000100) return; // Check the interrupt disable flag, if it's 1 we return
        }
    }
#undef INTERRUPT_TYPE

};

class ram
{
private:
    inline static constexpr size_t m_ramSize = 0x7800;
    inline static std::array<byte, m_ramSize> m_ramContents;
public:

    byte read(uint16_t index) const
    {
        return m_ramContents[index];
    }

    void write(uint16_t index, byte value)
    {
        m_ramContents[index] = value;
        return;
    }
};

class rom
{
private:
    static inline std::ifstream runFile;
    static inline constexpr size_t knownRomSize = 0x8000;
    static inline std::array<byte, knownRomSize> romData;
public:
    static int openRom(int amntArgs, std::string passedMainArg, int mode = 0)
    {
        runFile.exceptions(std::fstream::failbit | std::fstream::badbit); // Enable exceptions for easier error catching
        try
        {
            runFile.open(passedMainArg, std::ios::binary);
        } catch(const std::ios_base::failure& e) {
            runFile.clear();
            runFile.close();
            return 1;
        }
        return 0;
    }
};

class stack
{
private:
    inline static constexpr size_t m_stackSize = 0x100;
    inline static std::array<byte, m_stackSize> m_stackContents;
public:
    static inline void push(byte btp)
    {
        m_stackContents[cpu::m_stack::m_stackPtr] = btp;
        cpu::m_stack::m_stackPtr--;
        return;
    }
    static inline byte pop()
    {
        byte ret = m_stackContents[cpu::m_stack::m_stackPtr];
        cpu::m_stack::m_stackPtr++;
        return ret;
    }
    static inline auto& pull = pop; /* Providing function aliases, as PLA, PLP and PLX/Y were
    the instructions used to pop off the stack and was considered PULLING rather than the Intel standard of POPPING. */

    static inline void setStackPtr(uint8_t newStackPtr = 0xFF)
    {
        logic::cpu::m_stack::m_stackPtr = newStackPtr;
        return;
    }
};

class zeroPage
{
private:
    inline static constexpr size_t m_zpSize = 0x100;
    inline static std::array<byte, m_zpSize> m_zeroPageContents;
public:
    byte read(uint8_t address) const
    {
        return m_zeroPageContents[address];
    }
    void write(uint8_t address, byte data)
    {
        m_zeroPageContents[address] = data;
        return;
    }

};

};

#endif // LOGIC_H
