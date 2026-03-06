#pragma once

#include "../headers/ppu.hpp"

namespace logic
{
std::array<uint8_t, ppu::fbSize> ppu::fbGetter()
{
    return fb;
}
uint8_t* ppu::fbPtrGetter()
{
    return fb.data();
}
ppu* graphics;
}
