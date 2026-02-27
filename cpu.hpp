#ifndef CPU_HPP
#define CPU_HPP
#include <cstdint>
#include <cstddef>

namespace addrSpace
{
class stack;
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
    class m_stack {
        private:
        friend class cpu;
        friend class addrSpace::stack;
        inline static uint8_t m_stackPtr = 0xFF;
    };

    void hardReset()
    {

    }

};

#endif // CPU_HPP
