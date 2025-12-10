#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <array>

int main()
{
    std::ifstream inputFile("input.txt");

    std::string line;
    std::string nextLine;
    std::vector<std::string> grid;
    std::vector<int> beam_position;
    unsigned long long timeline = 0;

    std::getline(inputFile, line); //get first line, insert to grid vector
    
    grid.push_back(line);
    

    for(auto i = 0; i < line.size(); i++)
    {
        if(line.at(i) == 'S')
        {
            beam_position.push_back(i);
        }
    }

    while(std::getline(inputFile, nextLine))
    {
        for(int index : beam_position) //the beam position of the previous line
        {
            switch(nextLine.at(index))
            {
                case '.':
                   nextLine.at(index) = '|'; 
                break;
                case '^':
                    if(index == 0)
                    {
                        nextLine.at(index + 1) = '|';
                        timeline = timeline + 1;
                    }
                    else if(index == nextLine.size() - 1)
                    {
                        nextLine.at(index - 1) = '|';
                        timeline = timeline + 1;
                    }
                    else {
                        nextLine.at(index + 1) = '|';
                        nextLine.at(index - 1) = '|';
                        timeline = timeline + 2;
                    }
                    std::cout << "number of timelines now is: " << timeline << std::endl;
                break;
            }
        }

        line = nextLine;
        beam_position.clear();

        for(auto i = 0; i < line.size(); i++)
        {
            if(line.at(i) == '|')
            {
                beam_position.push_back(i);
            }
        }
    }

    std::cout << "number of timelines is: " << timeline << std::endl;
}