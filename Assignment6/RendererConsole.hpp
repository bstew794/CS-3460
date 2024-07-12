//local imports
#include "Renderer.hpp"

class RendererConsole : public Renderer
{
  public:
    // The below constructor is used to build prevCells with sizeX and sizeY
    RendererConsole(std::uint8_t sizeX, std::uint8_t sizeY);
    virtual void render(const LifeSimulator& simulation) override;

  private:
    // 2-D vector to store previous state of the console cells as true/false values
    std::vector<std::vector<bool>> prevCells;
};