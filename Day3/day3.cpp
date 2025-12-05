#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
    std::string line;
    long sum = 0;
    while(std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
        int largest_digit = 0;
        int pos_largest_digit = 0;

        for(int i = 0; i < line.size() - 1; i++)
        {
            if(line.at(i) - '0' > largest_digit)
            {
                largest_digit = line.at(i) - '0';
                pos_largest_digit = i;
            }
        }

        int second_largest_digit = 0;
        for(int i = pos_largest_digit + 1; i < line.size(); i++)
        {
            if(line.at(i) - '0' > second_largest_digit)
            {
                second_largest_digit = line.at(i) - '0';
            }
        }

        long largest_num = largest_digit * 10 + second_largest_digit;
        
        std::cout << "Largest num: " << largest_num << std::endl;
        sum += largest_num;
    }

    std::cout << "Sum is: " << sum;
}