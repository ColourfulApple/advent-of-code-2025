#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include <vector>
#include <stack>

int main()
{
    std::ifstream inputFile("input.txt");

    std::stack<std::string> lineStack;
    
    std::string str;
    while(std::getline(inputFile, str))
    {
        lineStack.push(str);
    }

    std::vector<char> operators;
    std::vector<long long> numVector;
    std::stringstream ss(lineStack.top());

    //put in operators
    char op;
    while(ss >> op)
    {
        operators.push_back(op);
    }
    lineStack.pop();
    //
    ss.str("");
    ss.clear();

    ss << lineStack.top();
    lineStack.pop();
    //initialize first now
    long long num;
    while(ss >> num)
    {
        numVector.push_back(num);
    }

    while(!lineStack.empty())
    {
        ss.str("");ss.clear();

        ss << lineStack.top();
        lineStack.pop();
        long long i = 0;
        while(ss >> num)
        {
            switch(operators.at(i))
            {
                case '+':
                    numVector.at(i) = numVector.at(i) + num;
                    break;
                case '*':
                    numVector.at(i) = numVector.at(i) * num;
                    break;
            }
            i++;
        }
    }
    long long sum = 0;
    //calculate sum
    long long i = 0;
    for(long long num : numVector)
    {
        std::cout << "answer " << i << " is: " << num << std::endl;
        sum += num;
        i++;
    }
    
    std::cout << "Summation is: " << sum;
}