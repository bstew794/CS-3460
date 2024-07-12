#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>

//local imports
#include "sortutils.hpp"

void initializeRawArrayFromStdArray(const SourceArray& source, int dest[])
{
    for (size_t i = 0; i < source.size(); i++)
    {
        dest[i] = source.at(i);
    }
}

void fillVectorFromStdArray(const SourceArray& source, std::vector<int>& dest)
{
    for (auto x : source)
    {
        dest.push_back(x);
    }
}

void organPipeStdArray(SourceArray& data)
{
    auto dataSize = data.size();
    auto iStart = dataSize / 2;
    auto j = iStart - 1;

    if (dataSize % 2 != 0)
    {
        iStart += 1;
    }

    for (size_t i = iStart; i < dataSize; i++)
    {
        data.at(i) = data.at(j);

        j -= 1;
    }
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted,
                      const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    using namespace std::chrono;

    std::cout << "--- Raw Array Performance ---" << std::endl;
    auto indentWidth = 8;
    auto titleWidth = 16;
    std::cout << std::endl;

    std::cout << "Sequential:" << std::endl;
    long long totalCount = 0;
    int raw[HOW_MANY_ELEMENTS];

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(random, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Random Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(sorted, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Sorted Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(reversed, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Reversed Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(organPipe, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Organ Pipe Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(rotated, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Rotated Time";
    std::cout << ": " << totalCount << " ms" << std::endl;
    std::cout << std::endl;

    std::cout << "Parallel:" << std::endl;
    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(random, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Random Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(sorted, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Sorted Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(reversed, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Reversed Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(organPipe, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Organ Pipe Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        initializeRawArrayFromStdArray(rotated, raw);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, std::begin(raw), std::end(raw));
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Rotated Time";
    std::cout << ": " << totalCount << " ms" << std::endl;
    std::cout << std::endl;
}
void evaluateStdArray(const SourceArray& random, const SourceArray& sorted,
                      const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    using namespace std::chrono;

    std::cout << "--- std::array Performance ---" << std::endl;
    auto indentWidth = 8;
    auto titleWidth = 16;
    std::cout << std::endl;

    std::cout << "Sequential:" << std::endl;
    long long totalCount = 0;

    SourceArray standard;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = random;

        auto start = steady_clock::now();
        std::sort(std::execution::seq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Random Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = sorted;

        auto start = steady_clock::now();
        std::sort(std::execution::seq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Sorted Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = reversed;

        auto start = steady_clock::now();
        std::sort(std::execution::seq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Reversed Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = organPipe;

        auto start = steady_clock::now();
        std::sort(std::execution::seq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Organ Pipe Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = rotated;

        auto start = steady_clock::now();
        std::sort(std::execution::seq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Rotated Time";
    std::cout << ": " << totalCount << " ms" << std::endl;
    std::cout << std::endl;

    std::cout << "Parallel:" << std::endl;
    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = random;

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Random Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = sorted;

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Sorted Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = reversed;

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Reversed Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = organPipe;

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Organ Pipe Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        standard = rotated;

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, standard.begin(), standard.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Rotated Time";
    std::cout << ": " << totalCount << " ms" << std::endl;
    std::cout << std::endl;
}
void evaluateStdVector(const SourceArray& random, const SourceArray& sorted,
                       const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    using namespace std::chrono;

    std::cout << "--- std::vector Performance ---" << std::endl;
    auto indentWidth = 8;
    auto titleWidth = 16;
    std::cout << std::endl;

    std::cout << "Sequential:" << std::endl;
    long long totalCount = 0;

    std::vector<int> myVector;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(random, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Random Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(sorted, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Sorted Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(reversed, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Reversed Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(organPipe, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Organ Pipe Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(rotated, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::seq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Rotated Time";
    std::cout << ": " << totalCount << " ms" << std::endl;
    std::cout << std::endl;

    std::cout << "Parallel:" << std::endl;
    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(random, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Random Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(sorted, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Sorted Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(reversed, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Reversed Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(organPipe, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Organ Pipe Time";
    std::cout << ": " << totalCount << " ms" << std::endl;

    totalCount = 0;

    for (size_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        fillVectorFromStdArray(rotated, myVector);

        auto start = steady_clock::now();
        std::sort(std::execution::par_unseq, myVector.begin(), myVector.end());
        auto end = steady_clock::now();
        auto diff = end - start;

        totalCount += duration_cast<milliseconds>(diff).count();
        myVector.clear();
    }
    std::cout << std::setw(indentWidth) << ' ' << std::left << std::setw(titleWidth) << "Rotated Time";
    std::cout << ": " << totalCount << " ms" << std::endl;
    std::cout << std::endl;
}