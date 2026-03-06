#include "../headers/cpu.hpp"
#include "../headers/addrSpace.hpp"

namespace logic
{
class cpu;
extern logic::cpu* primary;
class addressSpace;
int8_t addressSpace::readRam(uint16_t index) const
{
    return m_ramContents[index];
}
void addressSpace::writeRam(uint16_t index, int8_t value)
{
    m_ramContents[index] = value;
    return;
}

int8_t addressSpace::readZp(uint8_t address) const
{
    return m_zeroPageContents[address];
}
void addressSpace::writeZp(uint8_t address, int8_t data)
{
    m_zeroPageContents[address] = data;
    return;
}

void addressSpace::push(int8_t btp)
{
    m_stackContents[primary->stackInterface.returnStackPtr()] = btp;
    primary->stackInterface.decStackPtr();
    return;
}
int8_t addressSpace::pop()
{
    int8_t ret = m_stackContents[primary->stackInterface.returnStackPtr()];
    primary->stackInterface.incStackPtr();
    return ret;
}

int8_t addressSpace::openRom(int amntArgs, std::string passedMainArg, int8_t mode)
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
    int temp;
    while (runFile >> temp) {
        m_romData.push_back(temp);
    }
    runFile.close();
    return 0;
}
int8_t addressSpace::readRom(uint16_t offset)
{
    return m_romData[offset];
}
logic::addressSpace addrSpace;
}
