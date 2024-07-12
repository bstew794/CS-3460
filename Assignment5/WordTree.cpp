#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

// Local Imports
#include "WordTree.hpp"

WordTree::WordTree()
{
    root = std::make_shared<TreeNode>();
    numOfWords = 0;

    std::array<char, 26> myAlphabet = { 'a', 'b', 'c', 'd', 'e', 'f',
                                        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                        's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

    alphabet = std::make_unique<std::array<char, 26>>(myAlphabet);
    root->myC = '!';
}
void WordTree::add(std::string word)
{
    auto parent = root;

    for (size_t i = 0; i < word.size(); i++)
    {
        auto c = word[i];
        auto childPos = c - 'a';

        if (parent->children[childPos] == nullptr)
        {
            parent->children[childPos] = std::make_shared<TreeNode>();
            parent->children[childPos]->myC = c;

            if (i == word.size() - 1)
            {
                parent->children[childPos]->endOfWord = true;
                numOfWords++;
            }
        }
        auto newParent = parent->children[childPos];
        parent = newParent;
    }
}

bool WordTree::find(std::string word)
{
    auto parent = root;

    for (size_t i = 0; i < word.size(); i++)
    {
        auto c = word[i];
        auto childPos = c - 'a';

        if (parent->children[childPos] == nullptr)
        {
            return false;
        }
        else if (parent->children[childPos]->endOfWord && i == word.size() - 1)
        {
            return true;
        }
        auto newParent = parent->children[childPos];
        parent = newParent;
    }
    return false;
}

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::vector<std::string> predictions;

    auto treeSize = size();

    if (treeSize == 0 || partial == "")
    {
        return predictions;
    }
    auto parent = root;

    for (char const& c : partial)
    {
        auto childPos = c - 'a';

        if (parent->children[childPos] == nullptr)
        {
            return predictions;
        }
        auto newParent = parent->children[childPos];
        parent = newParent;
    }
    auto traverOrder = std::make_unique<std::queue<std::shared_ptr<std::pair<std::shared_ptr<TreeNode>, std::string>>>>();
    auto parentPair = std::make_shared<std::pair<std::shared_ptr<TreeNode>, std::string>>(parent, partial);

    traverOrder->push(parentPair);

    while (traverOrder->empty() != true)
    {
        auto currNodePair = traverOrder->front();
        traverOrder->pop();

        for (size_t i = 0; i < currNodePair->first->children.size(); i++)
        {
            auto child = currNodePair->first->children[i];

            if (child != nullptr)
            {
                std::string childStr = currNodePair->second + alphabet->at(i);

                if (child->endOfWord)
                {
                    predictions.push_back(childStr);

                    if (predictions.size() >= howMany)
                    {
                        return predictions;
                    }
                }
                auto childPair =
                    std::make_shared<std::pair<std::shared_ptr<TreeNode>, std::string>>(child, childStr);

                traverOrder->push(childPair);
            }
        }
    }
    return predictions;
}

std::size_t WordTree::size()
{
    return std::size_t(numOfWords);
}
