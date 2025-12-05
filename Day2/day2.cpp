#include <fstream>
#include <string>
#include <iostream>

bool isValid(long long);
bool isValid2(long long);

int main()
{
    std::ifstream inputFile("input.txt");
    long long sum = 0;
    std::string id;

    while(std::getline(inputFile, id, ','))
    {
        int pos = id.find('-');

        long long start = std::stoll(id.substr(0 ,pos));
        long long end = std::stoll(id.substr(pos + 1, id.size()));

        while(start <= end)
        {
            if(!isValid2(start))
            {
                std::cout << start << " is invalid." << std::endl;
                sum += start;
            }
            start++;
        }
    }

    std::cout << "Total sum of all invalid: " << sum;
}

bool isValid(long long num)
{
    std::string s_num = std::to_string(num); 
    if(s_num.size() % 2 == 0)
    {
        std::string left = s_num.substr(0, s_num.size() / 2);
        std::string right = s_num.substr(s_num.size() / 2, s_num.size());
        
        //invalid if equal.
        return !(left == right);
    }
    else
    {
        return true;
    }
}

bool isValid2(long long num)
{
    std::string s_num = std::to_string(num); 

    for(int i = 1; i <= s_num.size() / 2; i++)
    {
        std::string substr = s_num.substr(0, i);

        if(s_num.size() % substr.size() != 0)
            continue;
        else
        {
            int j = substr.size();
            while(j + substr.size() <= s_num.size())
            {
                std::string sub_check =  s_num.substr(j, substr.size());

                if(substr != sub_check)
                {
                    break;
                }
                j += substr.size();
                if(j == s_num.size())
                {
                    return false;
                }
            }
        }
    }

    return true;
}