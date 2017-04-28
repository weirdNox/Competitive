#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    std::ifstream in("in");
    std::ofstream out("out");

    int T;
    in >> T;

    int r, c, w;

    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        std::cout << "Case #" << caseNum << std::endl;
        out << "Case #" << caseNum << ": ";

        in >> r >> c >> w;

        int answer = 0;
        answer += (c / w) * r;
        if(c % w)
        {
            answer += 1;
        }
        answer += w - 1;

        out << answer << '\n';
    }

    return 0;
}


