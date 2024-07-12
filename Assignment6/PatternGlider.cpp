//local imports
#include "PatternGlider.hpp"

std::uint8_t PatternGlider::getSizeX() const
{
    return std::uint8_t(cells.at(0).size());
}

std::uint8_t PatternGlider::getSizeY() const
{
    return std::uint8_t(cells.size());
}

bool PatternGlider::getCell(std::uint8_t x, std::uint8_t y) const
{
    return cells.at(y).at(x);
}
