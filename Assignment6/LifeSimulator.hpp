#pragma once
#include <vector>

// Local imports
#include "Pattern.hpp"

class LifeSimulator
{
  public:
    LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY);

    void insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY);
    void update();

    std::uint8_t getSizeX() const;
    std::uint8_t getSizeY() const;
    bool getCell(std::uint8_t x, std::uint8_t y) const;

  private:
    std::vector<std::vector<bool>> cells; //variable to store state of each cell

    // The function below is used in update() to get alive neighbors
    std::uint8_t getNumOfLiveNeighbors(std::uint8_t x, std::uint8_t y);
};