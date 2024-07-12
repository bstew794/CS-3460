//local imports
#include "PatternBlock.hpp"

std::uint8_t PatternBlock::getSizeX() const
{
    return std::uint8_t(cells.at(0).size());
}

std::uint8_t PatternBlock::getSizeY() const
{
    return std::uint8_t(cells.size());
}

bool PatternBlock::getCell(std::uint8_t x, std::uint8_t y) const
{
    return cells.at(y).at(x);
}