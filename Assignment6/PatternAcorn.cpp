//local imports
#include "PatternAcorn.hpp"

std::uint8_t PatternAcorn::getSizeX() const
{
    return std::uint8_t(cells.at(0).size());
}

std::uint8_t PatternAcorn::getSizeY() const
{
    return std::uint8_t(cells.size());
}

bool PatternAcorn::getCell(std::uint8_t x, std::uint8_t y) const
{
    return cells.at(y).at(x);
}