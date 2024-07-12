// local imports
#include "PatternBlinker.hpp"

std::uint8_t PatternBlinker::getSizeX() const
{
    return std::uint8_t(cells.at(0).size());
}

std::uint8_t PatternBlinker::getSizeY() const
{
    return std::uint8_t(cells.size());
}

// y is not currently used since the initial state is one-dimesional
// I do not know how to disable the warning it gives me about leaving y unused
// I thought that since getcell was const; I could not change it
bool PatternBlinker::getCell(std::uint8_t x, std::uint8_t y) const
{
    return cells.at(y).at(x);
}