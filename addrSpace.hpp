#pragma once


#ifndef ADDRSPACE_HPP
#define ADDRSPACE_HPP
#include <array>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include "cpu.hpp"
#include "addrSpace.hpp"

using byte = std::byte;

extern std::vector<std::string> passedArgs;

class cpu;

namespace addrSpace
{
class ram
{
private:
    inline static constexpr size_t m_ramSize = 0x7800;
    inline static std::array<byte, m_ramSize> m_ramContents;
public:

};

class rom
{
private:
    std::ifstream runFile;

public:
    void openRom(int amntArgs, char* passedMainArgs[]) {

    }
};

class stack
{
private:
    inline static constexpr size_t m_stackSize = 0xFF;
    inline static std::array<byte, m_stackSize> m_stackContents;
public:
    void push(byte btp)
    {

    }
    byte pop() {
        byte ret = m_stackContents[cpu::m_stack::m_stackPtr];
        cpu::m_stack::m_stackPtr++;
        return ret;
    }
};

class zeroPage
{
private:
    inline static constexpr size_t m_zpSize = 0x100;
    inline static std::array<byte, m_zpSize> m_zeroPageContents;
public:

};
}
#endif // ADDRSPACE_HPP
