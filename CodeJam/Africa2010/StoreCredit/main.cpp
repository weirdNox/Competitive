#include <algorithm>
#include <array>
#include <chrono>
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

    int c, n;
    std::vector<short> list;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        out << "Case #" << caseNum << ": ";

        in >> c >> n;
        list.resize(n);
        for(int i = 0; i < n; ++i)
        {
            in >> list[i];
        }

        std::pair<int, int> pair;
        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                if(list[i] + list[j] == c)
                {
                    pair = std::make_pair(i+1, j+1);
                    goto stop;
                }
            }
        }
        stop:
        out << pair.first << ' '  << pair.second << '\n';
    }

    return 0;
}

