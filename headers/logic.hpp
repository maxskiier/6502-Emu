#pragma once

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
#include <exception>
#include "../iniLib/ini.h"

/* Copyright 2025-2026 Maxwell Doose */

using byte = std::byte;

extern std::vector<std::string> passedArgs;
namespace logic {
class cpu;
class ppu;
}
extern logic::ppu ppu;

namespace logic
{

constexpr uint16_t makeWord(uint8_t lo, uint8_t hi) noexcept
{
    return static_cast<uint16_t>(lo) | (static_cast<uint16_t>(hi) << 8);
}

constexpr uint8_t getLoByte(uint16_t word) noexcept
{
    return static_cast<uint8_t>(word & 0x00FF);
}

constexpr uint8_t getHiByte(uint16_t word) noexcept
{
    return static_cast<uint8_t>((word >> 8) & 0x00FF);
}

constexpr std::string eightBitIntToStr(const uint8_t conv) noexcept
{
    return std::to_string(static_cast<unsigned int>(conv));
}
constexpr uint8_t strToEightBitInt(const std::string &conv) noexcept
{
    return static_cast<uint8_t>(std::stoi(conv));
}

class iniInterface final
{
private:
    mINI::INIFile settingsFile;
    mINI::INIStructure settings;

    mINI::INIFile opcodesFile;
    mINI::INIStructure opcodes;

    bool initialized = false;
public:
    iniInterface() : settingsFile("settings.ini"), opcodesFile("opcodes.ini") { initialized = true; }

    std::string readSettingsINISection(std::string section, std::string key);
    std::string readOpcodesINISection(std::string section, std::string key);
};

};

#endif // LOGIC_H
