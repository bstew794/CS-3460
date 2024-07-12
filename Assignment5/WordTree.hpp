#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

struct TreeNode
{
    bool endOfWord;
    std::array<std::shared_ptr<TreeNode>, 26> children;
    char myC;
};

class WordTree
{
  private:
    std::shared_ptr<TreeNode> root;
    std::unique_ptr<std::array<char, 26>> alphabet;

    size_t numOfWords;

  public:
    WordTree();
    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size();
};