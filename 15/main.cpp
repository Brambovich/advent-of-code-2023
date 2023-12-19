#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>


std::string retrieveInput(std::string fileName)
{
    std::ifstream t(fileName);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

std::vector<std::string> parseInput(std::string input)
{
    auto result = std::vector<std::string>{};
    auto ss = std::stringstream{input};

    for (std::string line; std::getline(ss, line, ',');)
    {
        result.push_back(line);
    }
    return result;
}

int decodeHash(std::string input)
{
    int currentValue = 0;
    for (char letter : input)
    {
        currentValue += int(letter);
        currentValue = currentValue * 17;
        currentValue = currentValue % 256;
    }
    return currentValue;
}

void printBoxes(std::array<std::vector<std::pair<std::string, int>>, 256> boxes)
{
    std::cout << "--------------------------" << std::endl;
    for (int i = 0; i < 256; i++)
    {
        if (!boxes[i].empty())
        {
            std::cout << "BOX:" << i << " --> ";
            for (std::pair<std::string, int> lens : boxes[i])
            {
                std::cout << "[" << lens.first << " : " << lens.second << "] ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "--------------------------" << std::endl;
}

int focusBoxPower(std::array<std::vector<std::pair<std::string, int>>, 256> boxes)
{
    int totalValue = 0;
    for (int boxIt = 0; boxIt < 256; boxIt++)
    {
        for (int lensIt = 0; lensIt < boxes[boxIt].size(); lensIt++)
        {
            totalValue += (boxIt+1) * (lensIt+1) * boxes[boxIt][lensIt].second;
        }
    }
    return totalValue;
}


int main()
{
    std::string input = retrieveInput("input.txt");
    std::array<std::vector<std::pair<std::string, int>>, 256> boxes;
    std::vector<std::string> parsedInput = parseInput(input);


    int totalValue = 0;
    for (auto hash : parsedInput)
    {
        if (int pos = hash.find('-'); pos != std::string::npos)
        {
            std::string label = hash.substr(0,pos);
            int boxNumber = decodeHash(label);
            if (!boxes[boxNumber].empty())
            {
                auto iterator = std::find_if(boxes[boxNumber].begin(), boxes[boxNumber].end(), [label](auto input){return input.first == label;});
                if (iterator != std::end(boxes[boxNumber]))
                {
                    boxes[boxNumber].erase(iterator);
                }
            }            
        }
        if (int pos = hash.find('='); pos != std::string::npos)
        {
            std::string label = hash.substr(0,pos);
            int focalLength = std::stoi(hash.substr(pos+1));
            int boxNumber = decodeHash(label);
            bool lensReplaced = false;
            for (std::pair<std::string, int>& lens : boxes[boxNumber])
            {
                if (lens.first == label)
                {
                    lens.second = focalLength;
                    lensReplaced = true;
                    break;
                }
            }
            if (!lensReplaced || boxes[boxNumber].empty())
            {
                boxes[boxNumber].push_back({label, focalLength});
            }
        }
    }
    printBoxes(boxes);
    int output = focusBoxPower(boxes);
    std::cout << "output power: " << output;
}
