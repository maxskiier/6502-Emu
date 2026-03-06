#ifndef PPU_HPP
#define PPU_HPP

#include <array>
#include <cstdint>
#include <cstddef>
#include "baseEngine.hpp"
namespace logic
{

class ppu : public logic::engine
{
public:
    static constexpr size_t fbSize = 72*144;
private:
    std::array<uint8_t, fbSize> fb;

public:
    std::array<uint8_t, fbSize> fbGetter();
    uint8_t* fbPtrGetter();
};

}

#endif // PPU_HPP
