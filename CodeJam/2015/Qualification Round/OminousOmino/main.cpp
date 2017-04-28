#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    short x, r, c;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        in >> x >> r >> c;

        if(c*r % x != 0)
        {
            out << "RICHARD\n";
            continue;
        }

        if(x == 3)
        {
            if((c >= 2 && r >= 3) || (c >= 3 && r >= 2))
            {
                out << "GABRIEL\n";
                continue;
            }
            else
            {
                out << "RICHARD\n";
                continue;
            }
        }

        if(x == 4)
        {
            if((c >= 3 && r >= 4) || (c >= 4 && r >= 3))
            {
                out << "GABRIEL\n";
                continue;
            }
            else
            {
                out << "RICHARD\n";
                continue;
            }
        }

        if(x == 5)
        {
            if((c >= 4 && r >= 5) || (c >= 5 && r >= 4))
            {
                out << "GABRIEL\n";
                continue;
            }
            else
            {
                out << "RICHARD\n";
                continue;
            }
        }

        if(x == 6)
        {
            if((c >= 5 && r >= 6) || (c >= 6 && r >= 5))
            {
                out << "GABRIEL\n";
                continue;
            }
            else
            {
                out << "RICHARD\n";
                continue;
            }
        }

        if(x >= 7)
        {
            out << "RICHARD\n";
            continue;
        }

        out << "GABRIEL\n";
    }

    return 0;
}
