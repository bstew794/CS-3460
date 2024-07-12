#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>

// Local Imports
#include "distributions.hpp"

//
// This is in charge of generating a uniform distribution with bins/pairs which are
// returned after the random values have been sorted into them.
//
std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    std::vector<DistributionPair> pairs;

    std::uint32_t binSize = (max - min + 1) / numberBins;

    std::uint32_t localMin = min;
    std::uint32_t localMax = localMin + binSize - 1;

    for (size_t i = 0; i < numberBins; i++)
    {
        DistributionPair newPair(localMin, localMax);
        pairs.push_back(newPair);

        localMin = localMax + 1;
        localMax = localMin + binSize - 1;
    }
    std::random_device randDevice;
    std::mt19937 generator(randDevice());
    std::uniform_int_distribution<> distribution(min, max);

    for (size_t i = 0; i < howMany; i++)
    {
        std::uint32_t randNumber = distribution(generator);

        if (randNumber < min)
        {
            pairs[0].count++;
        }
        else if (randNumber > max)
        {
            pairs[numberBins - 1].count++;
        }
        else
        {
            for (size_t j = 0; j < numberBins; j++)
            {
                if (randNumber < pairs[j].maxValue + 1)
                {
                    pairs[j].count++;
                    break;
                }
            }
        }
    }
    return pairs;
}

//
// This function generates a normal distribution stored in bins/pairs
//
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    std::uint32_t min = static_cast<std::uint32_t>(mean - 4 * stdev);
    std::uint32_t max = static_cast<std::uint32_t>(mean + 4 * stdev);

    std::uint32_t binRemainder = (max - min + 1) % numberBins;

    if (binRemainder != 0)
    {
        max -= 1;
    }

    std::vector<DistributionPair> pairs;

    std::uint32_t binSize = (max - min + 1) / numberBins;

    std::uint32_t localMin = min;
    std::uint32_t localMax = localMin + binSize - 1;

    for (size_t i = 0; i < numberBins; i++)
    {
        DistributionPair newPair(localMin, localMax);
        pairs.push_back(newPair);

        localMin = localMax + 1;
        localMax = localMin + binSize - 1;
    }
    std::random_device randDevice;
    std::mt19937 generator(randDevice());
    std::normal_distribution<float> distribution(mean, stdev);

    for (size_t i = 0; i < howMany; i++)
    {
        float randNumber = distribution(generator);

        if (randNumber < static_cast<float>(min))
        {
            pairs[0].count++;
        }
        else if (randNumber > static_cast<float>(max))
        {
            pairs[numberBins - 1].count++;
        }
        else
        {
            for (size_t j = 0; j < numberBins; j++)
            {
                if (randNumber < static_cast<float>(pairs[j].maxValue) + 1)
                {
                    pairs[j].count++;
                    break;
                }
            }
        }
    }

    return pairs;
}

//
// This function returns a Poisson Distribution stored in bins/pairs
//
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    std::uint32_t min = 0;
    std::uint32_t max = numberBins - 1;

    std::vector<DistributionPair> pairs;

    std::uint32_t binSize = (max - min + 1) / numberBins;

    std::uint32_t localMin = min;
    std::uint32_t localMax = localMin + binSize - 1;

    for (size_t i = 0; i < numberBins; i++)
    {
        DistributionPair newPair(localMin, localMax);
        pairs.push_back(newPair);

        localMin = localMax + 1;
        localMax = localMin + binSize - 1;
    }
    std::random_device randDevice;
    std::mt19937 generator(randDevice());
    std::poisson_distribution<int> distribution(howOften);

    for (size_t i = 0; i < howMany; i++)
    {
        int randNumber = distribution(generator);

        if (randNumber < static_cast<int>(min))
        {
            pairs[0].count++;
        }
        else if (randNumber > static_cast<int>(max))
        {
            pairs[numberBins - 1].count++;
        }
        else
        {
            for (size_t j = 0; j < numberBins; j++)
            {
                if (randNumber < static_cast<int>(pairs[j].maxValue) + 1)
                {
                    pairs[j].count++;
                    break;
                }
            }
        }
    }
    return pairs;
}

//
// This plots the distributions, enough said.
//
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    std::cout << title << std::endl;

    std::uint32_t maxStars = 0;
    int minCoordWidth = 3;

    // find maxStars
    for (size_t i = 0; i < distribution.size(); i++)
    {
        if (distribution[i].count > maxStars)
        {
            maxStars = distribution[i].count;
        }
    }
    std::uint32_t starRatio = 1;

    if (maxStars > maxPlotLineSize)
    {
        starRatio = maxStars / static_cast<std::uint32_t>(maxPlotLineSize);
    }
    for (size_t i = 0; i < distribution.size(); i++)
    {
        std::cout << "[";
        std::cout << std::setw(minCoordWidth) << std::right << distribution[i].minValue;
        std::cout << ",";
        std::cout << std::setw(minCoordWidth) << std::right << distribution[i].maxValue;
        std::cout << "] : ";
        std::cout << std::string(distribution[i].count / starRatio, '*') << std::endl;
    }
}