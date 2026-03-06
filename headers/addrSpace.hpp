#pragma once
#ifndef ADDRSPACE_HPP
#define ADDRSPACE_HPP
#include <cstdint>
#include <cstddef>
#include <array>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <fstream>
#include <exception>

namespace logic
{
class cpu;
extern logic::cpu* primary;
class addressSpace
{
private:
    static constexpr size_t m_stackSize = 0x100;
    std::array<int8_t, m_stackSize> m_stackContents;

    static constexpr size_t m_zpSize = 0x100;
    std::array<int8_t, m_zpSize> m_zeroPageContents;

    static constexpr size_t m_ramSize = 0x1E00;
    std::array<int8_t, m_ramSize> m_ramContents;

    std::ifstream runFile;
    static constexpr size_t knownRomSize = 0x8000;
    std::vector<int8_t> m_romData;
public:

    int8_t readRam(uint16_t index) const;
    void writeRam(uint16_t index, int8_t value);

    int8_t readZp(uint8_t address) const;
    void writeZp(uint8_t address, int8_t data);

    void push(int8_t btp);
    int8_t pop();

    int8_t openRom(int amntArgs, std::string passedMainArg, int8_t mode = 0);
    int8_t readRom(uint16_t offset);

};

}
#endif // ADDRSPACE_HPP
