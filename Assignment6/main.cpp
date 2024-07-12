#include <chrono>
#include <thread>

//local imports
#include "LifeSimulator.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"

int main()
{
    // initilizing base patterns
    // please note that all of my patterns provide no padding
    auto patAcorn = PatternAcorn();
    auto patBlink = PatternBlinker();
    auto patBlock = PatternBlock();
    auto patGlide = PatternGlider();
    auto patGliderGun = PatternGosperGliderGun();

    // console window size
    std::uint8_t sizeX = static_cast<std::uint8_t>(rlutil::tcols());
    std::uint8_t sizeY = static_cast<std::uint8_t>(rlutil::trows());

    auto lifeSim = LifeSimulator(sizeX, sizeY);
    auto renderer = RendererConsole(sizeX, sizeY);

    // pattern insertion loop yet to be implemented, wanted it to dsplay things correctly first
    lifeSim.insertPattern(patGliderGun, 0, 0);
    lifeSim.insertPattern(patGlide, patGliderGun.getSizeX(), patGliderGun.getSizeY());
    lifeSim.insertPattern(patBlock, 0, patGliderGun.getSizeY() + 1);
    lifeSim.insertPattern(patBlink, 0, patGliderGun.getSizeY() + patBlock.getSizeY() + 4);
    lifeSim.insertPattern(patAcorn, patGliderGun.getSizeX() + 40, patGliderGun.getSizeY() + 5);

    rlutil::cls();
    rlutil::locate(1, 1);
    rlutil::hidecursor();

    // rendering loop
    // I swear the acorn is there it just expands very quickly after the first frame
    for (auto i = 0; i < 300; i++)
    {
        renderer.render(lifeSim);
        lifeSim.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    rlutil::cls();
    rlutil::showcursor();
    rlutil::resetColor();

    return 0;
}