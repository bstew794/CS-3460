#include "PatternGosperGliderGun.hpp"

std::uint8_t PatternGosperGliderGun::getSizeX() const
{
    return std::uint8_t(cells.at(0).size());
}

std::uint8_t PatternGosperGliderGun::getSizeY() const
{
    return std::uint8_t(cells.size());
}

bool PatternGosperGliderGun::getCell(std::uint8_t x, std::uint8_t y) const
{
    return cells.at(y).at(x);
}