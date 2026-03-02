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
#include <functional>

/* Copyright 2025-2026 Maxwell Doose */

using byte = std::byte;

extern std::vector<std::string> passedArgs;
namespace logic {
class cpu;
}
extern logic::cpu primary;

namespace logic
{

constexpr uint16_t makeWord(uint8_t lo, uint8_t hi) noexcept {
    return static_cast<uint16_t>(lo) | (static_cast<uint16_t>(hi) << 8);
}

constexpr uint8_t getLoByte(uint16_t word) noexcept {
    return static_cast<uint8_t>(word & 0x00FF);
}

constexpr uint8_t getHiByte(uint16_t word) noexcept {
    return static_cast<uint8_t>((word >> 8) & 0x00FF);
}

class ram;


class cpu
{
private:
    uint16_t programCounterRegister;
    uint8_t m_accumulatorRegister;
    uint8_t m_xRegister;
    uint8_t m_yRegister;
    uint8_t statusRegister;

    bool jammedState = false;
public:
    class m_stack
    {
    private:
        friend class cpu;
        friend class logic::ram;
        uint8_t m_stackPtr = 0xFF;
    public:
        void setStackPtr(uint8_t newStackPtr = 0xFF)
        {
            m_stackPtr = newStackPtr;
            return;
        }
        uint returnStackPtr()
        { return m_stackPtr; }

        void decStackPtr()
        {
            m_stackPtr--;
            return;
        }
        void incStackPtr()
        {
            m_stackPtr++;
            return;
        }
    };
    m_stack stackInterface;

    void reset()
    {

    }
    typedef bool interruptType;
    static constexpr bool regularInterrupt = false; // Aliases for the types of interrupts
    static constexpr bool nmi = true;

    void interrupt(interruptType interrupt = regularInterrupt)
    {
        if (interrupt == regularInterrupt)
        {
            if ((statusRegister & 0b00000100) == 0b00000100) return; // Check the interrupt disable flag, if it's 1 we return
        }
    }

};

class ram
{
private:
    static constexpr size_t m_ramSize = 0x1D00;
    std::array<byte, m_ramSize> m_ramContents;

    static constexpr size_t m_stackSize = 0x100;
    std::array<byte, m_stackSize> m_stackContents;

    static constexpr size_t m_zpSize = 0x100;
    std::array<byte, m_zpSize> m_zeroPageContents;
public:

    byte readRam(uint16_t index)
    {
        return m_ramContents[index];
    }
    void writeRam(uint16_t index, byte value)
    {
        m_ramContents[index] = value;
        return;
    }

    byte readZp(uint8_t address)
    {
        return m_zeroPageContents[address];
    }
    void writeZp(uint8_t address, byte data)
    {
        m_zeroPageContents[address] = data;
        return;
    }

    void push(byte btp)
    {
        m_stackContents[primary.stackInterface.returnStackPtr()] = btp;
        primary.stackInterface.decStackPtr();
        return;
    }
    byte pop()
    {
        byte ret = m_stackContents[primary.stackInterface.returnStackPtr()];
        primary.stackInterface.incStackPtr();
        return ret;
    }

};

class rom
{
private:
    std::ifstream runFile;
    static constexpr size_t knownRomSize = 0x8000;
    static inline std::array<byte, knownRomSize> romData;
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

};

#endif // LOGIC_H
