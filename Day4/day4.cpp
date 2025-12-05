#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

//remember to pass by reference!
bool isAccessible(int row, int col, const std::vector<std::vector<int>>& arr);

struct pos
{
    int row;
    int col;

    pos(int x, int y) : row(x), col(y) {}
};

int main()
{
    std::ifstream inputFile("input.txt");
    
    int total_sum_of_accessible = 0;
    std::string line;
    std::vector<std::vector<int>> arr;

    while(std::getline(inputFile, line))
    {
        std::vector<int> row;
        std::stringstream ss_line(line);
        
        char c;
        while(ss_line >> c)
        {
            if(c == '.')
                row.push_back(0);
            else
                row.push_back(1);
        }
        arr.push_back(row);
    }

    for(std::vector<int> row : arr)
    {
        for(int i : row)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    int sum_of_accessible;
    do
    {
        std::vector<pos> position_vector;
        sum_of_accessible = 0;
        for(int i = 0; i < arr.size(); i++)
        {
            for(int j = 0; j < arr.at(0).size(); j++)
            {
                if(arr.at(i).at(j) == 1 && isAccessible(i, j, arr))
                {
                    position_vector.push_back(pos(i, j));
                    sum_of_accessible += 1;
                    std::cout << "row: " << i << " col: " << j << " is accessible. " << std::endl;
                }
            }
        }

        for(pos position : position_vector)
        {
            arr.at(position.row).at(position.col) = 0;
        }

        total_sum_of_accessible += sum_of_accessible;
    } while (sum_of_accessible != 0);
    

    
    std::cout << "Sum of accessible: " << total_sum_of_accessible;
}

bool isAccessible(int row, int col, const std::vector<std::vector<int>>& arr)
{
    int around = 0;
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            int check_row = row + i;
            int check_col = col + j;

            if(check_row > 0 && check_col > 0 && check_row < arr.size() && check_col < arr.size())
            {
                around += arr.at(check_row).at(check_col);
            }
        }
    }

    return around < 5; //fewer than 4 including itself
}