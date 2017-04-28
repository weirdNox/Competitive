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

    int n, k, b, t;
    for(int caseNum = 1; caseNum <= T; ++caseNum)
    {
        std::cout << "Case #" << caseNum << std::endl;
        out << "Case #" << caseNum << ": ";

        in >> n >> k >> b >> t;

        std::vector<double> positions(n);
        std::vector<double> velocities(n);
        for(int i = 0; i < n; ++i)
        {
            in >> positions[i];
        }
        for(int i = 0; i < n; ++i)
        {
            in >> velocities[i];
        }

        long long answer = 0;
        int chickensLeft = k;
        for(int i = n-1; i >= 0 && chickensLeft; --i)
        {
            double timeUntilB = (b - positions[i]) / velocities[i];
            if(timeUntilB <= t)
            {
                --chickensLeft;

                for(int j = i+1; j < n; ++j)
                {
                    double tempTimeUntilB = (b - positions[j]) / velocities[j];
                    if(tempTimeUntilB > t && timeUntilB < tempTimeUntilB && velocities[i] > velocities[j])
                    {
                        ++answer;
                    }
                }
            }
        }

        if(chickensLeft) out << "IMPOSSIBLE" << '\n';
        else out << answer << '\n';
    }

    return 0;
}


