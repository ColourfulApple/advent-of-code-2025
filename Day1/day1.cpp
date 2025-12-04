#include <iostream>
#include <fstream>
#include <string>

int main()
{
    //dials starts at 50,
    //sum the number of times dials reach 0
    //dial is a circle, 0 - 99

    std::ifstream inputFile("input.txt");

    std::string str;

    int pointing = 50;

    int zero_count = 0;
    while(std::getline(inputFile, str))
    {
        int zero_inbetween_moves = 0;

        char direction = str.at(0);

        std::string s_moves = str.substr(1);
        int moves = std::stoi(s_moves);

        // divide any number of moves by 100
        // 851 moves / 100 = 8, eight zeros is guaranteed.
        // Check whether pointing gets negative or gets further than 100
        // (indicates that it went through 0 once)

        if(direction == 'L')
        {
            zero_inbetween_moves += moves / 100;
            
            pointing = pointing - (moves % 100); 
            
            if(pointing < 0)
            {
                if(pointing + (moves % 100) != 0)
                    zero_inbetween_moves++;
                
                pointing += 100;
            }
        }
        else
        {
            zero_inbetween_moves += moves / 100;

            pointing = pointing + (moves % 100);
            if(pointing > 99)
            {
                if(pointing > 100)
                {
                    zero_inbetween_moves++;   
                }
                pointing %= 100;
            }
        }
        if(pointing == 0)
            zero_count++;
        zero_count += zero_inbetween_moves; 
    }

    std::cout << zero_count;
}