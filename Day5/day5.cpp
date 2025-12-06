#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct range
{
    long long start;
    long long end;

    range() : start(0), end(0) {};
    range(long long x, long long y) : start(x), end(y) {}

    bool operator<(const range& other) const {
        return start < other.start;
    }
};


int main()
{
    std::ifstream rangeFile("range.txt");
    std::vector<range> rangeVec;

    std::string str;
    while(std::getline(rangeFile, str, '-'))
    {
        long long start = std::stoll(str);

        std::getline(rangeFile, str);
        long long end = std::stoll(str);
        
        rangeVec.push_back(range{start, end});
    }

    //load ids 
    std::ifstream idFile("id.txt");
    int total_fresh_id = 0;
    while(std::getline(idFile, str))
    {
        long long id = std::stoll(str);

        int index = id % 10;
        for(range r : rangeVec)
        {
            if(id >= r.start && id <= r.end)
            {
                total_fresh_id++;
                break;
            }
        }
    }

    std::cout << "total fresh from id: " << total_fresh_id << std::endl;

    std::sort(rangeVec.begin(), rangeVec.end());
    long long total_fresh = 0;

    std::vector<range> mergedRange;

    mergedRange.push_back(rangeVec[0]);
    for(int i = 1; i < rangeVec.size(); i++)
    {
        range &check = mergedRange.back();
        range &current = rangeVec[i];

        if(check.end >= current.start)
        {
            mergedRange.pop_back();
            mergedRange.push_back(range(check.start, std::max(check.end, current.end)));
        }
        else
        {
            mergedRange.push_back(current);
        }
    }

    for(range r : mergedRange)
    {
        total_fresh = total_fresh + (r.end - r.start) + 1;
    }

    std::cout << "Total Fresh: " << total_fresh << std::endl;
}   
