#include <algorithm>
#include <execution>
#include <iostream>
#include <random>

// Local Imports
#include "sortutils.hpp"

//
// This is the main entry point of a C++ program.
//
int main()
{
    //random number range
    int min = -10000000;
    int max = 10000000;

    SourceArray random;
    SourceArray sorted;

    //init random generator and distribution
    std::random_device randDevice;
    std::mt19937 generator(randDevice());
    std::uniform_int_distribution<int> distribution(min, max);

    // init sorted and random arrays
    for (size_t i = 0; i < HOW_MANY_ELEMENTS; i++)
    {
        auto randNumber = distribution(generator);

        random.at(i) = randNumber;
        sorted.at(i) = randNumber;
    }
    // sort 'sorted' array
    std::sort(sorted.begin(), sorted.end());

    SourceArray reversed;
    SourceArray organPipe;
    SourceArray rotated;

    // init reversed, organPipe, and rotated
    for (size_t i = 0; i < HOW_MANY_ELEMENTS; i++)
    {
        reversed.at(i) = sorted.at(i);
        organPipe.at(i) = sorted.at(i);
        rotated.at(i) = sorted.at(i);
    }
    //reverse 'reversed' array
    std::reverse(reversed.begin(), reversed.end());

    //assemble the organ pipes
    organPipeStdArray(organPipe);

    //rotate 'rotated' array
    std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());

    evaluateRawArray(random, sorted, reversed, organPipe, rotated);
    evaluateStdArray(random, sorted, reversed, organPipe, rotated);
    evaluateStdVector(random, sorted, reversed, organPipe, rotated);

    return 0;
}