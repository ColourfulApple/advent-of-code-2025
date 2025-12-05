#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
    std::string line;
    long long sum = 0;
    while(std::getline(inputFile, line))
    {
        int digits_left = 12;
        long long max_num = 0;
        // 12 digits to form a number. So we cannot choose any of the last 11 numbers. 
        // Last number we can choose is the 12th number from the back
        std::cout << "Number: " << line << std::endl;
        
        int i = 0;
        while(digits_left > 0)
        {
            int max = 0;
            int pos_max = 0;
            for(; i < line.size() - digits_left + 1; i++)
            {
            
            if(line.at(i) - '0' > max)
                {
                    max = line.at(i) - '0';
                    pos_max = i;
                }
            }
            digits_left--;
            max_num = max_num * 10 + max;
            i = pos_max;
            line.erase(pos_max, 1);
        }

        std::cout << "Max num is: " << max_num << std::endl;
        sum += max_num;
    }

    std::cout << "Sum is: " << sum;
}