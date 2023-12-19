#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::string retrieveInput(std::string fileName)
{
    std::ifstream t(fileName);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void printMatrix(std::vector<std::vector<char>> input)
{
    std::cout << "----------------" << std::endl;
    for (int i = 0; i < input.size(); i++)
    {
        std::vector<char> tmpVector{};
        for (int j = 0; j < input[i].size(); j++) 
        {
            std::cout << input[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "----------------" << std::endl;
}


std::vector<std::vector<char>> parseInput(std::string input, std::string direction)
{

    auto result = std::vector<std::vector<char>>{};
    auto ss = std::stringstream{input};

    for (std::string line; std::getline(ss, line, '\n');)
    {
        std::vector<char> tmpVector{};
        for (int i = 0; i < line.size(); i++)
        {   
            tmpVector.push_back(line[i]);
        } 
        result.push_back(tmpVector);
    }
    return result;
}

void rollStonesNorth(std::vector<std::vector<char>>& input)
{
    for (int y = 0; y < input.size(); y++)
    {
        int latestSolidPosition = -1;
        for (int x = 0; x < input[y].size(); x++) 
        {
            if (input[x][y] == '#')
            {
                latestSolidPosition = x;
            }
            if (input[x][y] == 'O' && latestSolidPosition == x-1)
            {
                latestSolidPosition = x;
            }
            else if (input[x][y] == 'O')
            {
                input[x][y] = '.';
                input[latestSolidPosition+1][y] = 'O';
                latestSolidPosition += 1;
            }
        }
    }
}

void rollStonesSouth(std::vector<std::vector<char>>& input)
{
    for (int y = 0; y < input.size(); y++)
    {
        int latestSolidPosition = input[y].size();
        for (int x = input[y].size()-1; x >= 0; x--) 
        {

            if (input[x][y] == '#')
            {
                latestSolidPosition = x;
            }
            if (input[x][y] == 'O' && latestSolidPosition == x+1)
            {
                latestSolidPosition = x;
            }
            else if (input[x][y] == 'O')
            {
                input[x][y] = '.';
                input[latestSolidPosition-1][y] = 'O';
                latestSolidPosition -= 1;
            }
        }
    }
}

void rollStonesWest(std::vector<std::vector<char>>& input)
{
    for (int y = 0; y < input.size(); y++)
    {
        int latestSolidPosition = -1;
        for (int x = 0; x < input[y].size(); x++) 
        {
            if (input[y][x] == '#')
            {
                latestSolidPosition = x;
            }
            if (input[y][x] == 'O' && latestSolidPosition == x-1)
            {
                latestSolidPosition = x;
            }
            else if (input[y][x] == 'O')
            {
                input[y][x] = '.';
                input[y][latestSolidPosition+1] = 'O';
                latestSolidPosition += 1;
            }
            // std::cout << x << ", " << y << " :" << input[y][x] << std::endl;
            // if (y == latestSolidPosition)
            // {
            //     std::cout << "solid position: " << x << y << std::endl;
            // }
        }
    }
}

void rollStonesEast(std::vector<std::vector<char>>& input)
{
    for (int y = 0; y < input.size(); y++)
    {
        int latestSolidPosition = input[y].size();
        for (int x = input[y].size()-1; x >= 0 ; x--) 
        {
            if (input[y][x] == '#')
            {
                latestSolidPosition = x;
            }
            if (input[y][x] == 'O' && latestSolidPosition == x+1)
            {
                latestSolidPosition = x;
            }
            else if (input[y][x] == 'O')
            {
                input[y][x] = '.';
                input[y][latestSolidPosition-1] = 'O';
                latestSolidPosition -= 1;
            }
            // std::cout << x << ", " << y << " :" << input[y][x] << std::endl;
            // if (y == latestSolidPosition)
            // {
            //     std::cout << "solid position: " << x << y << std::endl;
            // }
        }
    }
}

int countWeight(std::vector<std::vector<char>> input)
{
    int output = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++) 
        {
            if (input[i][j] == 'O')
            {
                output += (input.size()-i);
            }
        }
    }
    return output;
}


int main()
{
    std::string output = retrieveInput("input.txt");
    std::vector<std::vector<char>> parsedOutput = parseInput(output, "");
    for (int i = 0; i < 1000000; i++)
    {
        rollStonesNorth(parsedOutput);
        rollStonesWest(parsedOutput);
        rollStonesSouth(parsedOutput);
        rollStonesEast(parsedOutput);
        // printMatrix(parsedOutput);
        if (i % 10000 == 0)
        {
            std::cout << "iteration: " << i << std::endl;
        }
    }

    int weight = countWeight(parsedOutput);
    std::cout << "weight: " << weight << std::endl;
}