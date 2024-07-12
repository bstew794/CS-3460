#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>

// Local Imports
#include "distributions.hpp"

//
// This is the main entry point of a C++ program.
//
int main()
{
    auto uniform = generateUniformDistribution(100000, 0, 79, 40);
    plotDistribution("--- Uniform ---", uniform, 80);

    auto normal = generateNormalDistribution(100000, 50, 5, 40);
    plotDistribution("--- Normal ---", normal, 80);

    auto poisson = generatePoissonDistribution(100000, 6, 40);
    plotDistribution("--- Poisson ---", poisson, 80);

    return 0;
}