#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

// Local Imports
#include "WordTree.hpp"
#include "rlutil.h"

std::shared_ptr<WordTree> readDictionary(std::string filename);

//
// This is the main entry point of a C++ program.
//
int main()
{
    auto myTree = readDictionary("dictionary.txt");

    rlutil::saveDefaultColor();
    rlutil::hidecursor();
    rlutil::cls();

    bool done = false;
    int x = 1;
    int y = 1;
    std::string myStr = "";
    std::string prevPredStr = "";
    std::string predStr = "";

    rlutil::locate(x, y);

    while (done != true)
    {
        if (kbhit())
        {
            prevPredStr = predStr;
            predStr = "";
            auto input = rlutil::getkey();
            char myChar = char(input);

            if (input == rlutil::KEY_ESCAPE)
            {
                done = true;
            }
            else if (input == rlutil::KEY_BACKSPACE)
            {
                if (!myStr.empty() && x > 1)
                {
                    myStr.erase(myStr.end() - 1);
                    x--;
                    rlutil::locate(x, y);
                    rlutil::setChar(' ');
                }
            }
            else
            {
                myStr += myChar;
                rlutil::setChar(myChar);
                x++;
            }
            rlutil::locate(1, 4);
            std::cout << "--- Predictions ---";

            std::vector<std::string> predictions;

            auto lastSpaceIndex = myStr.find_last_of(" ");
            std::string partial = myStr;

            if (lastSpaceIndex != -1)
            {
                partial = myStr.substr(lastSpaceIndex + 1);
            }
            // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
            // it will throw exception on negative values; e.g., characters with accent marks.
            if (std::all_of(partial.begin(), partial.end(), [](unsigned char c)
                            { return std::isalpha(c); }))
            {
                std::transform(partial.begin(), partial.end(), partial.begin(), [](char c)
                               { return static_cast<char>(std::tolower(c)); });

                std::uint8_t numOfRows = static_cast<std::uint8_t>(rlutil::trows()) - 4;

                predictions = myTree->predict(partial, numOfRows);
            }
            rlutil::locate(1, 5);

            //fine to this point

            if (!predictions.empty())
            {
                for (auto prediction : predictions)
                {
                    predStr += prediction + "\n";
                }
            }
            if (predStr.size() < prevPredStr.size())
            {
                rlutil::cls();
                std::cout << myStr;
                rlutil::locate(1, 4);
                std::cout << "--- Predictions ---";
                rlutil::locate(1, 5);
            }
            std::cout << predStr;

            rlutil::locate(x, y);
        }
    }
    rlutil::cls();
    rlutil::resetColor();
    rlutil::showcursor();

    return 0;
}

/*
* code geneoursly provided by professor Dean Mathias (CS 3460) for this assignment @
* https://usu.instructure.com/courses/676471/assignments/3380016
*/
std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c)
                        { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c)
                           { return static_cast<char>(std::tolower(c)); });

            wordTree->add(word);
        }
    }
    return wordTree;
}