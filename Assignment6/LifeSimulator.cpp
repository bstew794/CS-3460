//local imports
#include "LifeSimulator.hpp"

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{
    for (auto i = 0; i < sizeY; ++i)
    {
        cells.push_back(std::vector<bool>());

        for (auto j = 0; j < sizeX; ++j)
        {
            cells.at(i).push_back(false);
        }
    }
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    // iterators used for cells 2-D vector
    auto currX = startX;
    auto currY = startY;

    //main logic loop
    for (std::uint8_t i = 0; i < pattern.getSizeY(); ++i)
    {
        currX = startX; // reset x to begining of row for each row (typewriter style)

        if (currY >= getSizeY())
        {
            break; // this row of the pattern is out of bounds to the bottom
        }
        for (std::uint8_t j = 0; j < pattern.getSizeX(); ++j)
        {
            if (currX >= getSizeX())
            {
                break; // this cell is out of bounds to the right
            }
            // cell is good to add to the current model, move to the next cell to the right
            cells.at(currY).at(currX) = pattern.getCell(j, i);
            ++currX;
        }
        // row added, move to the next row
        ++currY;
    }
}

void LifeSimulator::update()
{
    // newcells ensures that previous calculations don't affect the current calculation
    // it keeps generations seperate
    auto newCells = cells;

    //main logic loop
    for (std::uint8_t i = 0; i < getSizeY(); i++)
    {
        for (std::uint8_t j = 0; j < getSizeX(); j++)
        {
            auto aliveCount = getNumOfLiveNeighbors(j, i); // get alive neighbors count

            // cell is alive or dead
            if (getCell(j, i))
            {
                // cell dies becuase of rules 1 and 3 or underpopulation and overpopulation
                if (aliveCount < 2 || aliveCount > 3)
                {
                    newCells.at(i).at(j) = false;
                }
                // alive cells with 2 or three living neighbors stay alive so do nothing (rule 2)
            }
            // dead cell is made alive by rule 4 (reproduction)
            else if (aliveCount == 3)
            {
                newCells.at(i).at(j) = true;
            }
            // cell is dead and/or rules 1 through 4 do not apply to them
        }
    }
    cells = newCells; //update current model of the states
}

std::uint8_t LifeSimulator::getSizeX() const
{
    return std::uint8_t(cells.at(0).size());
}

std::uint8_t LifeSimulator::getSizeY() const
{
    return std::uint8_t(cells.size());
}

bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    // makes sure that cells out of bounds to the right are counted as false
    if (x >= getSizeX() || y >= getSizeY())
    {
        return false;
    }
    return cells.at(y).at(x);
}

std::uint8_t LifeSimulator::getNumOfLiveNeighbors(std::uint8_t x, std::uint8_t y)
{
    std::uint8_t liveCount = 0; // count of alive neighbors
    std::uint8_t startY = 0;    // point to start looking y
    std::uint8_t startX = 0;    //point to start looking x

    //The following conditionals make sure to ignore cells out of bounds to the left
    if (x - 1 >= 0)
    {
        startX = x - 1;
    }
    if (y - 1 >= 0)
    {
        startY = y - 1;
    }
    // main logic loop
    for (auto i = startY; i <= y + 1; ++i)
    {
        for (auto j = startX; j <= x + 1; ++j)
        {
            // check if current neighbor is alive
            if (getCell(j, i))
            {
                ++liveCount;
            }
        }
    }
    // prevents cell from counting itself as an alive neighbor
    if (getCell(x, y))
    {
        --liveCount;
    }
    return liveCount;
}