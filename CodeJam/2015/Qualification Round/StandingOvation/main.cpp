#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    short sMax;
    std::string number;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        in >> sMax >> number;
        int standingPeople = 0;
        int neededPeople = 0;
        for(short i = 0; i < sMax+1; ++i)
        {
            short digit;
            digit = std::stoi(number[i]);
            if(standingPeople < i)
            {
                neededPeople += i - standingPeople;
                standingPeople = i;
            }
            standingPeople += digit;
        }

        out << neededPeople << '\n';
    }

    return 0;
}

