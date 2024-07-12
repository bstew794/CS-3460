#include <array>

//local imports
#include "Pattern.hpp"

class PatternAcorn : public Pattern
{
  public:
    using Pattern::Pattern;

    virtual std::uint8_t getSizeX() const override;
    virtual std::uint8_t getSizeY() const override;
    virtual bool getCell(std::uint8_t x, std::uint8_t y) const override;

  private:
    // array to store "Acorn" pattern as true/false values
    // false = dead, true = alive
    const std::array<std::array<bool, 7>, 3> cells = { { { false, true, false, false, false, false, false },
                                                         { false, false, false, true, false, false, false },
                                                         { true, true, false, false, true, true, true } } };
};