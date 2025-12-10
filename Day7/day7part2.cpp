#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <array>

long long movedown(std::vector<std::string>& grid, int beam_position, int nextLineNumber, std::vector<std::vector<long long>>& memo);

int main()
{
    std::ifstream inputFile("input.txt");

    std::string line;
    std::string nextLine;
    std::vector<std::string> grid;
    int start_beam_position;
    long long timeline = 0;

    while(std::getline(inputFile, line))
    {
        grid.push_back(line);
    }

    for(int i = 0; i < grid.at(0).size(); i++)
    {
        if(grid.at(0).at(i) == 'S')
        {
            start_beam_position = i;
        }
    }

    std::vector<std::vector<long long>> memory_table(grid.size(), std::vector<long long>(grid.at(0).size(), -1));
    timeline = movedown(grid, start_beam_position, 1, memory_table);
    

    std::cout << "number of timelines is: " << timeline << std::endl;
}

long long movedown(std::vector<std::string>& grid, int beam_position, int nextLineNumber, std::vector<std::vector<long long>>& memo)
{
    long long totalTimeline = 0;
    if(nextLineNumber == grid.size())
    {
        return totalTimeline + 1;
    }
    if(memo[nextLineNumber][beam_position] != -1)
    {
        return memo[nextLineNumber][beam_position];
    }
    std::string& line = grid.at(nextLineNumber);


    if(line.at(beam_position) == '^')
    {
        std::cout << "Line number: " << beam_position << std::endl;
        if(beam_position == 0)
        {
            if(line.at(beam_position + 1) == '.')
            {
                //line.at(beam_position + 1) = '|';
                totalTimeline += movedown(grid, beam_position + 1, nextLineNumber + 1, memo);
            }
                
        }
        else if(beam_position == line.size() - 1)
        {
            if(line.at(beam_position - 1) == '.')
            {
                //line.at(beam_position - 1) = '|';
                totalTimeline += movedown(grid, beam_position -  1, nextLineNumber + 1, memo);
            }
        }
        else
        {
            if(line.at(beam_position + 1) == '.')
            {
                //line.at(beam_position + 1) = '|';
                totalTimeline += movedown(grid, beam_position + 1, nextLineNumber + 1, memo);
            }
            if(line.at(beam_position - 1) == '.')
            {
                //line.at(beam_position - 1) = '|';
                totalTimeline += movedown(grid, beam_position - 1, nextLineNumber + 1, memo);
            }            
        }
    }
    else
    {
        //line.at(beam_position) = '|';
        totalTimeline += movedown(grid, beam_position, nextLineNumber + 1, memo);
    }

    memo[nextLineNumber][beam_position] = totalTimeline;
    return totalTimeline;
}