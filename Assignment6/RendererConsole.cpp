//import local
#include "RendererConsole.hpp"

#include "rlutil.h"

RendererConsole::RendererConsole(std::uint8_t sizeX, std::uint8_t sizeY)
{
    for (auto i = 0; i < sizeY; ++i)
    {
        prevCells.push_back(std::vector<bool>());

        for (auto j = 0; j < sizeX; ++j)
        {
            prevCells.at(i).push_back(false);
        }
    }
}

void RendererConsole::render(const LifeSimulator& simulation)
{
    char aliveChar = 'X';
    char deadChar = ' ';

    for (std::uint8_t i = 0; i < simulation.getSizeY(); ++i)
    {
        for (std::uint8_t j = 0; j < simulation.getSizeX(); ++j)
        {
            auto prevCell = prevCells.at(i).at(j);
            auto cell = simulation.getCell(j, i);

            // check if cell value changed between renders
            if (prevCell != cell)
            {
                rlutil::locate(j + 1, i + 1);
                prevCells.at(i).at(j) = cell; // assign old cell with new cell data

                // change the console according to the new cell's value.
                if (cell)
                {
                    rlutil::setChar(aliveChar);
                }
                else
                {
                    rlutil::setChar(deadChar);
                }
            }
        }
    }
    rlutil::locate(1, 1); // recenter cursor
}