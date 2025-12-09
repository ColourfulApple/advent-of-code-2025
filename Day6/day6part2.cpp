#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include <vector>
#include <stack>

int main()
{
    std::string line;
    std::vector<std::string> lineVector;
    std::vector<char> opVector;
    std::vector<long long> sum;

    std::ifstream inputFile("input.txt");
    while(std::getline(inputFile, line))
    {
        if(line.at(0) == '*' || line.at(0) == '+')
        {
            std::stringstream ss;
            ss << line;
            char c;
            while(ss >> c)
            {
                opVector.push_back(c);
            }
        }
        else
        {
            lineVector.push_back(line);
        }
    }

    long long i = 0;
    auto op_iterator = opVector.cbegin();
    std::vector<long long> numbers;
    while(i < lineVector.at(0).size())
    {
        if(!(lineVector.at(0).at(i) == ' ' && lineVector.at(1).at(i) == ' ' && lineVector.at(2).at(i) == ' ' && lineVector.at(3).at(i) == ' '))
        {
            long long num = 0;
            for(auto line : lineVector)
            {
                if(line.at(i) != ' ')
                {
                    num = num * 10 + (line.at(i) - '0');
                }
            }
            numbers.push_back(num);
            i++;
        }
        else
        {
            if(!numbers.empty())
            {
                long long first = numbers.at(0);
                std::cout << "at line " << i << ": " << first;
                for(auto j = 1; j < numbers.size(); j++)
                {
                    switch(*op_iterator)
                    {
                        case '+':
                            first += numbers.at(j);
                            std::cout << " + " << numbers.at(j) << " ";
                            break;
                        case '*':
                            first *= numbers.at(j);
                            std::cout << " * " << numbers.at(j) << " ";
                            break;
                    }
                }
                std::cout << std::endl;
                op_iterator++;
                sum.push_back(first);
                numbers.clear();
            }
            i++;
        }
    }
    if(!numbers.empty())
    {
        long long first = numbers.at(0);
        std::cout << "at line " << i << ": " << first;
        for(auto j = 1; j < numbers.size(); j++)
        {
            switch(*op_iterator)
            {
                case '+':
                    first += numbers.at(j);
                    std::cout << " + " << numbers.at(j) << " ";
                    break;
                case '*':
                    first *= numbers.at(j);
                    std::cout << " * " << numbers.at(j) << " ";
                    break;
            }
        }
        std::cout << std::endl;
        op_iterator++;
        sum.push_back(first);
        numbers.clear();
    }

    
    long long final_sum = 0;
    for(long long num : sum)
    {
        final_sum += num;
    }

    std::cout << "Final sum: " << final_sum << std::endl;
}
