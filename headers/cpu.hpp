#pragma once
#ifndef CPU_HPP
#define CPU_HPP
#include <cstdint>
#include "baseEngine.hpp"
#include "addrSpace.hpp"

namespace logic {

class cpu : public logic::engine
{
private:
    uint16_t programCounterRegister;
    uint8_t m_accumulatorRegister;
    uint8_t m_xRegister;
    uint8_t m_yRegister;
    uint8_t m_statusRegister;
    uint8_t bus;
    std::string instructionType;

    uint8_t cpuStep = 0;
    /* Decimal 1 is fetch, decimal 2 is decode, decimal 3 is execute */
    uint8_t tState = 0;

    bool jammedState = false;

    std::string decodeT1(uint8_t opcode);
    std::string decodeT2(uint8_t opcode);
#define READ false
#define WRITE true
    bool rw = READ;
    cpu* CPUPtr = this;
public:
    void cycle();
    class m_stack
    {
    private:
        friend class cpu;
        friend class logic::addressSpace;
        uint8_t m_stackPtr = 0xFF;
    public:
        void setStackPtr(uint8_t newStackPtr = 0xFF)
        {
            m_stackPtr = newStackPtr;
            return;
        }
        uint8_t returnStackPtr() const
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

    void reset(bool coldStart = false);
    typedef bool interruptType;
    static constexpr bool regularInterrupt = false; // Aliases for the types of interrupts
    static constexpr bool nmi = true;

    void interrupt(interruptType interrupt = regularInterrupt);

};

}
#endif // CPU_HPP
