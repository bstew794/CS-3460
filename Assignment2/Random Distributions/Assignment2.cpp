#include <iomanip>
#include <iostream>
#include <random>

//
// This class was provided at https://usu.instructure.com/courses/676471/assignments/3380012
//
class DistributionPair
{
  public:
    DistributionPair(std::uint32_t minValue, std::uint32_t maxValue) :
        minValue(minValue),
        maxValue(maxValue),
        count(0)
    {
    }
    std::uint32_t minValue;
    std::uint32_t maxValue;
    std::uint32_t count;
};

// function prototypes
std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins);
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins);
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins);
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize);
void test();

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

    test();
    return 0;
}

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

// ------------------------------------------------------------------
//
// Testing Code
//
// ------------------------------------------------------------------
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

namespace testing::detail
{
    using namespace std::string_literals;

    using Bins = std::vector<std::pair<std::uint32_t, std::uint32_t>>;
    using DistFunc = std::function<std::vector<DistributionPair>()>;

#define CS3460_ASSERT_EQ(expected, actual, message)                    \
    if (expected != actual)                                            \
    {                                                                  \
        fail(message, "[ Expected", expected, "but got", actual, "]"); \
        return;                                                        \
    }

#define CS3460_CASE(x) \
    [] {               \
        return x;      \
    };                 \
    std::cout << " Case " << #x << "\n";

    template <typename Message>
    void failInternal(const Message& message)
    {
        std::cout << message << " ";
    }

    template <typename Message, typename... Messages>
    void failInternal(const Message& message, const Messages&... messages)
    {
        failInternal(message);
        failInternal(messages...);
    }

    template <typename... Messages>
    void fail(const Messages&... messages)
    {
        std::cout << "  Assertion failed: ";
        failInternal(messages...);
        std::cout << "\n";
    }

    Bins generateBins(const std::uint32_t min, const std::uint32_t max, const std::uint8_t numberBins)
    {
        const auto binRange = (max - min) / numberBins;
        auto minBin = min;
        auto maxBin = min + binRange;

        Bins results(numberBins);
        for (std::uint8_t bin = 0u; bin < numberBins; bin++)
        {
            results[bin] = { minBin, maxBin };
            minBin = maxBin + 1;
            maxBin = minBin + binRange;
        }

        return results;
    }

    void returnsTheExpectedBins(const DistFunc& func, const Bins& bins)
    {
        const auto result = func();
        CS3460_ASSERT_EQ(bins.size(), result.size(), "Wrong number of bins");
        for (auto i = 0u; i < bins.size(); i++)
        {
            CS3460_ASSERT_EQ(bins[i].first, result[i].minValue, "Wrong minimum value for bin "s + std::to_string(i));
            CS3460_ASSERT_EQ(bins[i].second, result[i].maxValue, "Wrong maximum value for bin "s + std::to_string(i));
        }
    }

    void hasTheCorrectTotalAcrossAllBins(const DistFunc& func, const std::uint32_t howMany)
    {
        const auto result = func();
        const auto add_counts = [](std::uint32_t total, const DistributionPair& bin)
        {
            return total + bin.count;
        };
        CS3460_ASSERT_EQ(howMany, std::accumulate(result.cbegin(), result.cend(), 0u, add_counts),
                         "Wrong number of elements across all bins");
    }

    void testUniformDistribution()
    {
        std::cout << "Testing generateUniformDistribution\n";
        auto func = CS3460_CASE(generateUniformDistribution(100000, 0, 79, 40));
        returnsTheExpectedBins(func, generateBins(0, 79, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }

    void testNormalDistribution()
    {
        std::cout << "Testing generateNormalDistribution\n";
        auto func = CS3460_CASE(generateNormalDistribution(100000, 50, 5, 40));
        returnsTheExpectedBins(func, generateBins(30, 69, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }

    void testPoissonDistribution()
    {
        std::cout << "Testing generatePoissonDistribution\n";
        auto func = CS3460_CASE(generatePoissonDistribution(100000, 6, 40));
        returnsTheExpectedBins(func, generateBins(0, 39, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }
} // namespace testing::detail

void test()
{
    using namespace testing::detail;

    testUniformDistribution();
    testNormalDistribution();
    testPoissonDistribution();

    std::cout << "\n\n";
}