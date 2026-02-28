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

using byte = std::byte;

extern std::vector<std::string> passedArgs;

namespace logic
{

class stack;

uint8_t getLowOrderByte(int16_t number)
{
#define LOW_ORDER 1
    union getByte
    {
        int16_t inVal;
        uint8_t outVal[];
    };
    getByte conv;
    conv.inVal = number;
    return conv.outVal[LOW_ORDER];
#undef LOW_ORDER
}
uint8_t getHighOrderByte(int16_t number)
{
#define HIGH_ORDER 0
    union getByte
    {
        int16_t inVal;
        uint8_t outVal[];
    };
    getByte conv;
    conv.inVal = number;
    return conv.outVal[HIGH_ORDER];
#undef HIGH_ORDER
}

class cpu
{
private:
    inline static uint16_t programCounterRegister;
    inline static int8_t m_accumulatorRegister;
    inline static int8_t m_xRegister;
    inline static int8_t m_yRegister;
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

    byte read(uint16_t index)
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
    std::ifstream runFile;
    size_t knownRomSize = 0x8000;

public:
    int openRom(int amntArgs, std::string passedMainArg, int mode = 0)
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
    byte read(uint8_t address)
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
