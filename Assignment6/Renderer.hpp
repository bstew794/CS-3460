//local imports
#include "LifeSimulator.hpp"

class Renderer
{
  public:
    virtual void render(const LifeSimulator& simulation) = 0;
};