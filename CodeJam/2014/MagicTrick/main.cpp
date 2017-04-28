#include <fstream>
#include <iostream>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int t;
    in >> t;

    bool possible[17];
    for(int caseNum = 1; caseNum <= t; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        for(short i = 0; i < 17; ++i)
        {
            possible[i] = true;
        }

        for(short question = 0; question < 2; ++question)
        {
            short row;
            in >> row;
            for(int i = 0; i < 4; ++i)
            {
                for(int j = 0; j < 4; ++j)
                {
                    short num;
                    in >> num;
                    if(i + 1 != row) possible[num] = false;
                }
            }
        }

        int answer = 0;
        for(int i = 0; i < 17; ++i)
        {
            if(possible[i] == true)
            {
                if(answer == 0) answer = i;
                else answer = -1;
            }
        }

        if(answer == -1) out << "Bad magician!\n";
        else if(answer == 0) out << "Volunteer cheated!\n";
        else out << answer << "\n";
    }

    return 0;
}
